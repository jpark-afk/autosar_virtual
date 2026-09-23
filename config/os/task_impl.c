#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include "tpl_os.h"
#include "rti_me_psl.h"

#include "TcpIp.h"

#include "Rte_DdsCddType.h"
#include "VirtualAswc.h"

#include "StackMonitor.h"

/*
 * Phase 7.2 - Minimal OS error observation.
 *
 * ErrorHook must remain bounded:
 * - no printf
 * - no allocation
 * - no blocking
 * - no socket/file I/O
 */
typedef struct
{
    volatile unsigned long count;
    volatile StatusType error;
    volatile uint8 service_id;
} Phase7_OsErrorRecord;

static Phase7_OsErrorRecord g_phase7_os_error = {
    0UL,
    E_OK,
    0
};

void ErrorHook(StatusType error)
{
    g_phase7_os_error.error = error;
    g_phase7_os_error.service_id = OSErrorGetServiceId();
    g_phase7_os_error.count++;
}

extern void DdsCdd_Init(void);
extern void DdsCddStart(void);
extern void DdsCdd_LocalIpAddrAssignmentChg(
    TcpIp_LocalAddrIdType LocalAddrId,
    TcpIp_IpAddrStateType State);

static int TcpIp_TestSocket = -1;
static boolean tcpip_initialized = FALSE;

int main(void)
{    
    printf("[Virtual AUTOSAR] DdsCdd_Init before StartOS\n");
    DdsCdd_Init();

    printf("[Virtual AUTOSAR] Initializing task stack monitor\n");
    Phase9_StackMonitor_Init();

    printf("[Virtual AUTOSAR] Starting Trampoline OS\n");
    StartOS(stdAppmode);

    return 0;
}

TASK(RTI_Task)
{
    printf("[Virtual AUTOSAR] RTI_Task started\n");    

    DdsCddStart();

    DdsCdd_LocalIpAddrAssignmentChg(
            (TcpIp_LocalAddrIdType)0U,
            TCPIP_IPADDR_STATE_ASSIGNED);
            
    printf("[Bsw_InitTask] DdsCdd_LocalIpAddrAssignmentChg completed\n");

    printf("[Virtual AUTOSAR] DdsCddStart completed\n");

    TerminateTask();
}


static FILE *g_tcpip_log = NULL;

static void TcpIp_LogInit(void)
{
#if TCPIP_ENABLE_DIAGNOSTIC_LOG
    g_tcpip_log = fopen("/tmp/autosar_tcpip.log", "a");

    if (g_tcpip_log != NULL)
    {
        setvbuf(g_tcpip_log, NULL, _IOLBF, 0);
        fprintf(g_tcpip_log, "[TcpIp] logging started\n");
    }
#endif
}

void TcpIp_Log(const char *msg)
{
#if TCPIP_ENABLE_DIAGNOSTIC_LOG
    if (g_tcpip_log != NULL)
    {
        fprintf(g_tcpip_log, "%s\n", msg);
        fflush(g_tcpip_log);
    }
#else
    (void)msg;
#endif
}

static void TcpIp_Init(void)
{
    uint16 local_port = 50001U;

    printf("[TcpIp] Init\n");
    TcpIp_LogInit();

    TcpIp_TestSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (TcpIp_TestSocket < 0)
    {
        printf("[TcpIp] socket FAIL\n");
        return;
    }

    /*
     * Non-blocking socket.
     * TcpIp_Task must never block the AUTOSAR OS.
     */
    int flags = fcntl(TcpIp_TestSocket, F_GETFL, 0);

    if (flags >= 0)
    {
        (void)fcntl(
            TcpIp_TestSocket,
            F_SETFL,
            flags | O_NONBLOCK);
    }

    if (TcpIp_Bind(
            (TcpIp_SocketIdType)TcpIp_TestSocket,
            (TcpIp_LocalAddrIdType)0U,
            &local_port) != E_OK)
    {
        printf("[TcpIp] TcpIp_Bind FAIL\n");
        close(TcpIp_TestSocket);
        TcpIp_TestSocket = -1;
        return;
    }

    printf("[TcpIp] UDP socket ready, port=%u\n", local_port);
}

static void TcpIp_PollRx(void)
{
    uint8 rx_buffer[1500];
    struct sockaddr_in remote;
    socklen_t remote_len = sizeof(remote);

    if (TcpIp_TestSocket < 0)
    {
        return;
    }

    for (;;)
    {
        ssize_t rx_len;

        rx_len = recvfrom(
            TcpIp_TestSocket,
            rx_buffer,
            sizeof(rx_buffer),
            0,
            (struct sockaddr *)&remote,
            &remote_len);

        if (rx_len < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                break;
            }

            printf("[TcpIp] recvfrom FAIL: errno=%d\n", errno);
            break;
        }

        printf("[TcpIp] UDP RX: %ld bytes\n", (long)rx_len);
        
        TcpIp_Log("[TcpIp_PollRx] UDP received.\n");

        /*
         * Actual TcpIp receive indication.
         */
        TcpIp_RxIndication(
            (TcpIp_SocketIdType)TcpIp_TestSocket,
            rx_buffer,
            (uint16)rx_len);
    }
}

static void TcpIp_PollTx(void)
{
    uint8 data[] = "AUTOSAR UDP TEST";
    TcpIp_SockAddrInetType remote;

    if (TcpIp_TestSocket < 0)
    {
        return;
    }

    remote.domain = TCPIP_AF_INET;
    remote.port = 50000U;

    remote.addr[0] =
        htonl((192U << 24) |
              (168U << 16) |
              (56U << 8) |
              1U);

    if (TcpIp_UdpTransmit(
            (TcpIp_SocketIdType)TcpIp_TestSocket,
            data,
            (TcpIp_SockAddrType *)&remote,
            (uint16)(sizeof(data) - 1U)) == E_OK)
    {
        printf("[TcpIp] UDP TX PASS\n");
    }
}


TASK(TcpIp_Task)
{
    if (tcpip_initialized)
    {
    /*
     * 5 ms polling
     */
    TcpIp_PollRx();
    TcpIp_PollDdsRx();

    /*
     * Optional TX test.
     */
    //TcpIp_PollTx();
    }

    TerminateTask();
}

TASK(Bsw_InitTask)
{
    if (!tcpip_initialized)
    {
        TcpIp_Init();
        tcpip_initialized = TRUE;
    }

    TerminateTask();
}

TASK(App_Task)
{
    VirtualAswc_Run();

    TerminateTask();
}
