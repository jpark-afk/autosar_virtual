#ifndef DDSCDD_IPADDR_H
#define DDSCDD_IPADDR_H

#include "TcpIp.h"
#include "dds_cdd_adapter.h"

void DdsCdd_LocalIpAddrAssignmentChg_Async(
    TcpIp_LocalAddrIdType LocalAddrId,
    TcpIp_IpAddrStateType State);

void DdsCdd_ProcessIpAssignmentQueue(void);

#endif