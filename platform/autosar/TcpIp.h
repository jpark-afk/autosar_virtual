#ifndef TCPIP_H
#define TCPIP_H

#include "Platform_Types.h"
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "TcpIp_CfgTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16 TcpIp_SocketIdType;
typedef uint8  TcpIp_ProtocolType;
typedef uint8  TcpIp_EventType;
typedef uint8  TcpIp_IpAddrStateType;

#define TCPIP_UDP_CLOSED              ((TcpIp_EventType)0x04U)
#define TCPIP_IPADDR_STATE_ASSIGNED   ((TcpIp_IpAddrStateType)0x01U)

typedef struct
{
    TcpIp_DomainType domain;
} TcpIp_SockAddrType;

#define TCPIP_AF_INET          ((TcpIp_DomainType)2U)
#define TCPIP_IPPROTO_UDP      ((TcpIp_ProtocolType)17U)

#define TCPIP_LOCALADDRID_ANY  ((TcpIp_LocalAddrIdType)0xFFU)
#define TCPIP_PORT_ANY         ((uint16)0U)
#define TCPIP_E_ARP_CACHE_MISS ((Std_ReturnType)0x02U)
#define TCPIP_LOCAL_ADDR_COUNT ((TcpIp_LocalAddrIdType)2U)

#ifndef TCPIP_ENABLE_DIAGNOSTIC_LOG
#define TCPIP_ENABLE_DIAGNOSTIC_LOG 0
#endif

Std_ReturnType TcpIp_GetIpAddr(
    TcpIp_LocalAddrIdType localAddrId,
    TcpIp_SockAddrType *localAddrPtr,
    uint8 *netmaskPtr,
    TcpIp_SockAddrType *defaultRouterPtr);

Std_ReturnType TcpIp_Bind(
    TcpIp_SocketIdType SocketId,
    TcpIp_LocalAddrIdType LocalAddrId,
    uint16 *PortPtr);

Std_ReturnType TcpIp_Close(
    TcpIp_SocketIdType SocketId,
    boolean Abort);

Std_ReturnType TcpIp_TcpIp_DdsCddGetSocket(
    TcpIp_DomainType domain,
    TcpIp_ProtocolType protocol,
    TcpIp_SocketIdType *socket_id);

Std_ReturnType TcpIp_TcpIp_ExtraGetSocket(
    TcpIp_DomainType domain,
    TcpIp_ProtocolType protocol,
    TcpIp_SocketIdType *socket_id);

void TcpIp_LocalIpAddrAssignmentChg(
    TcpIp_LocalAddrIdType LocalAddrId,
    TcpIp_IpAddrStateType State);

void TcpIp_PollSocketRx(void);

Std_ReturnType TcpIp_UdpTransmit(
    TcpIp_SocketIdType SocketId,
    uint8 *DataPtr,
    TcpIp_SockAddrType *RemoteAddrPtr,
    uint16 DataLength);

typedef void (*TcpIp_RxIndicationType)(
    TcpIp_SocketIdType SocketId,
    const TcpIp_SockAddrType *RemoteAddrPtr,
    uint8 *DataPtr,
    uint16 DataLength);    

void TcpIp_RxIndication(
    TcpIp_SocketIdType SocketId,
    const TcpIp_SockAddrType *RemoteAddrPtr,
    uint8 *DataPtr,
    uint16 DataLength);

extern void TcpIp_Log(const char *msg);

#ifdef __cplusplus
}
#endif

#endif
