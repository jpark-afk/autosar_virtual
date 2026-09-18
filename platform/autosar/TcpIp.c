#include "TcpIp.h"

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

/*
 * Virtual AUTOSAR TcpIp adapter
 *
 * LocalAddrId 0:
 *   IPv4    : 192.168.56.105
 *   Netmask : /24
 *
 * TcpIp_SocketIdType is mapped to a Linux socket file descriptor.
 */

#define VIRTUAL_LOCAL_ADDR_ID   ((TcpIp_LocalAddrIdType)0U)
#define VIRTUAL_LOCAL_IPV4      "192.168.56.105"
#define VIRTUAL_NETMASK_BITS    ((uint8)24U)
#define VIRTUAL_DDS_SOCKET_COUNT 8U

static TcpIp_SocketIdType TcpIp_DdsSockets[VIRTUAL_DDS_SOCKET_COUNT];
static uint8 TcpIp_DdsSocketCount = 0U;

extern void DdsCdd_RxIndication(
    TcpIp_SocketIdType SocketId,
    const TcpIp_SockAddrType *RemoteAddrPtr,
    uint8 *BufPtr,
    uint16 Length);


Std_ReturnType TcpIp_GetIpAddr(
    TcpIp_LocalAddrIdType localAddrId,
    TcpIp_SockAddrType *localAddrPtr,
    uint8 *netmaskPtr,
    TcpIp_SockAddrType *defaultRouterPtr)
{
    TcpIp_SockAddrInetType *local;
    TcpIp_SockAddrInetType *router;
    struct in_addr addr;

    if ((localAddrId != VIRTUAL_LOCAL_ADDR_ID) ||
        (localAddrPtr == NULL) ||
        (netmaskPtr == NULL) ||
        (defaultRouterPtr == NULL))
    {
        TcpIp_Log("[TcpIp] GetIpAddr FAIL");
        return E_NOT_OK;
    }

    if (inet_pton(AF_INET, VIRTUAL_LOCAL_IPV4, &addr) != 1)
    {
        TcpIp_Log("[TcpIp] GetIpAddr inet_pton FAIL");
        return E_NOT_OK;
    }

    local = (TcpIp_SockAddrInetType *)localAddrPtr;
    router = (TcpIp_SockAddrInetType *)defaultRouterPtr;

    memset(local, 0, sizeof(*local));
    memset(router, 0, sizeof(*router));

    local->domain = TCPIP_AF_INET;
    local->addr[0] = addr.s_addr;
    local->port = 0U;

    router->domain = TCPIP_AF_INET;

    *netmaskPtr = VIRTUAL_NETMASK_BITS;

    TcpIp_Log("[TcpIp] GetIpAddr PASS local=0");

    return E_OK;
}


Std_ReturnType TcpIp_Bind(
    TcpIp_SocketIdType SocketId,
    TcpIp_LocalAddrIdType LocalAddrId,
    uint16 *PortPtr)
{
    struct sockaddr_in local;
    socklen_t len;

    if (PortPtr == NULL)
    {
        return E_NOT_OK;
    }

    {
        char log_message[128];

        (void)snprintf(log_message,
                       sizeof(log_message),
                       "[TcpIp] Bind request socket=%d local=%u port=%u",
                       (int)SocketId,
                       (unsigned)LocalAddrId,
                       (unsigned)*PortPtr);
        TcpIp_Log(log_message);
    }

    memset(&local, 0, sizeof(local));

    local.sin_family = AF_INET;
    local.sin_port = htons(*PortPtr);

    if (LocalAddrId == TCPIP_LOCALADDRID_ANY)
    {
        local.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else if (LocalAddrId == VIRTUAL_LOCAL_ADDR_ID)
    {
        if (inet_pton(AF_INET, VIRTUAL_LOCAL_IPV4,
                      &local.sin_addr) != 1)
        {
            return E_NOT_OK;
        }
    }
    else
    {
        return E_NOT_OK;
    }

    if (bind((int)SocketId,
             (struct sockaddr *)&local,
             sizeof(local)) != 0)
    {
        TcpIp_Log("[TcpIp] Bind FAIL");
        return E_NOT_OK;
    }

    TcpIp_Log("[TcpIp] Bind PASS");

    /*
     * AUTOSAR TCP/IP expects the selected port to be returned when
     * TCPIP_PORT_ANY (0) requests an ephemeral port.
     */
    if (*PortPtr == TCPIP_PORT_ANY)
    {
        len = sizeof(local);

        if (getsockname((int)SocketId,
                        (struct sockaddr *)&local,
                        &len) != 0)
        {
            return E_NOT_OK;
        }

        *PortPtr = ntohs(local.sin_port);
    }

    return E_OK;
}


Std_ReturnType TcpIp_Close(
    TcpIp_SocketIdType SocketId,
    boolean Abort)
{
    (void)Abort;

    return (close((int)SocketId) == 0) ? E_OK : E_NOT_OK;
}


Std_ReturnType TcpIp_UdpTransmit(
    TcpIp_SocketIdType SocketId,
    uint8 *DataPtr,
    TcpIp_SockAddrType *RemoteAddrPtr,
    uint16 DataLength)
{
    TcpIp_SockAddrInetType *remote;
    struct sockaddr_in dst;
    ssize_t sent;

    if ((DataPtr == NULL) || (RemoteAddrPtr == NULL))
    {
        return E_NOT_OK;
    }

    remote = (TcpIp_SockAddrInetType *)RemoteAddrPtr;

    if (remote->domain != TCPIP_AF_INET)
    {
        return E_NOT_OK;
    }

    memset(&dst, 0, sizeof(dst));

    dst.sin_family = AF_INET;
    dst.sin_port = htons(remote->port);
    dst.sin_addr.s_addr = remote->addr[0];

    sent = sendto((int)SocketId,
                  DataPtr,
                  (size_t)DataLength,
                  0,
                  (struct sockaddr *)&dst,
                  sizeof(dst));

    {
        char log_message[160];

        (void)snprintf(
            log_message,
            sizeof(log_message),
            "[TcpIp] UdpTransmit socket=%u dst=0x%08x port=%u len=%u sent=%ld",
            (unsigned)SocketId,
            (unsigned)remote->addr[0],
            (unsigned)remote->port,
            (unsigned)DataLength,
            (long)sent);
        TcpIp_Log(log_message);
    }

    return (sent == (ssize_t)DataLength) ? E_OK : E_NOT_OK;
}

Std_ReturnType TcpIp_TcpIp_DdsCddGetSocket(
    TcpIp_DomainType domain,
    TcpIp_ProtocolType protocol,
    TcpIp_SocketIdType *socket_id)
{
    int fd;

    if ((socket_id == NULL) ||
        (domain != TCPIP_AF_INET) ||
        (protocol != TCPIP_IPPROTO_UDP))
    {
        return E_NOT_OK;
    }

    fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd < 0)
    {
        return E_NOT_OK;
    }

    if (fd > UINT16_MAX)
    {
        close(fd);
        return E_NOT_OK;
    }

    *socket_id = (TcpIp_SocketIdType)fd;

    if (TcpIp_DdsSocketCount >= VIRTUAL_DDS_SOCKET_COUNT)
    {
        close(fd);
        return E_NOT_OK;
    }

    {
        int flags = fcntl(fd, F_GETFL, 0);

        if ((flags < 0) ||
            (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0))
        {
            close(fd);
            return E_NOT_OK;
        }
    }

    TcpIp_DdsSockets[TcpIp_DdsSocketCount] = *socket_id;
    TcpIp_DdsSocketCount++;

    TcpIp_Log("[TcpIp] DdsCddGetSocket PASS");

    return E_OK;
}

void TcpIp_PollDdsRx(void)
{
    uint8 rx_buffer[8192];
    struct sockaddr_in remote;

    for (uint8 socket_index = 0U;
         socket_index < TcpIp_DdsSocketCount;
         socket_index++)
    {
        for (;;)
        {
            socklen_t remote_len = sizeof(remote);
            ssize_t rx_len = recvfrom(
                (int)TcpIp_DdsSockets[socket_index],
                rx_buffer,
                sizeof(rx_buffer),
                0,
                (struct sockaddr *)&remote,
                &remote_len);

            if (rx_len < 0)
            {
                if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                {
                    break;
                }

                printf("[TcpIp] DDS recvfrom FAIL");
                break;
            }

            {
                TcpIp_SockAddrInetType remote_addr;

                remote_addr.domain = TCPIP_AF_INET;
                remote_addr.addr[0] = remote.sin_addr.s_addr;
                remote_addr.port = ntohs(remote.sin_port);

                DdsCdd_RxIndication(
                    TcpIp_DdsSockets[socket_index],
                    (const TcpIp_SockAddrType *)&remote_addr,
                    rx_buffer,
                    (uint16)rx_len);
            }

        }
    }
}

void TcpIp_RxIndication(
    TcpIp_SocketIdType SocketId,
    const uint8 *DataPtr,
    uint16 DataLength)
{
    printf("[TcpIp] RxIndication: Socket=%u Length=%u\n",
           SocketId,
           DataLength);

    /*
     * Future:
     *   SoAd_RxIndication(...)
     *   or upper-layer callback
     */

    printf("[TcpIp] RX data: ");
    for (uint16 i = 0U; i < DataLength; i++)
    {
        printf("%02X ", DataPtr[i]);
    }
    printf("\n");
}


