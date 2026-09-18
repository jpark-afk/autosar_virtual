#include "TcpIp.h"

#include <unistd.h>
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
        return E_NOT_OK;
    }

    if (inet_pton(AF_INET, VIRTUAL_LOCAL_IPV4, &addr) != 1)
    {
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
        return E_NOT_OK;
    }

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

    return (sent == (ssize_t)DataLength) ? E_OK : E_NOT_OK;
}
