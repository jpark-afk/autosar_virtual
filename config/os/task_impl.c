#include <stdio.h>

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

static boolean tcpip_initialized = FALSE;

int main(void)
{
    printf("[Virtual AUTOSAR] Initializing task stack monitor\n");
    Phase9_StackMonitor_Init();

    printf("[Virtual AUTOSAR] Starting Trampoline OS\n");
    StartOS(stdAppmode);

    return 0;
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
    printf("[TcpIp] Init\n");
    TcpIp_LogInit();
}


TASK(TcpIp_Task)
{
    static boolean socket_enabled = FALSE;

    if (!socket_enabled)
    {
        TcpIp_LocalAddrIdType local_addr_id;

        GetResource(OsResource_DdsIpQueue);

        for (local_addr_id = (TcpIp_LocalAddrIdType)0U;
             local_addr_id < TCPIP_LOCAL_ADDR_COUNT;
             local_addr_id++)
        {
            TcpIp_LocalIpAddrAssignmentChg(
                local_addr_id,
                TCPIP_IPADDR_STATE_ASSIGNED);
        }

        SetEvent(DdsCddIpAddr_Task, OsEventDdsIpAssignment);
        ReleaseResource(OsResource_DdsIpQueue);

        printf("[TcpIp_Task] Local IP address assignments changed.\n");

        socket_enabled = TRUE;
    }
    
    if (tcpip_initialized)
    {
    /*
     * 5 ms polling
     */
    TcpIp_PollSocketRx();
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
