#include "rti_me_psl.h"
#include "RtiPslConfig.h"

#include <sys/socket.h>
#include <netinet/in.h>

#include "tpl_os.h"

#define RTI_PSL_HEAP_SIZE (1024U * 1024U)

static char RtiPslHeap[RTI_PSL_HEAP_SIZE];
static uint32 RtiPslHeapSize[1] = {
    RTI_PSL_HEAP_SIZE
};
static char *RtiPslHeapAreas[1] = {
    RtiPslHeap
};

static Std_ReturnType RtiPsl_get_socket(
    TcpIp_DomainType domain,
    TcpIp_ProtocolType protocol,
    TcpIp_SocketIdType *socket_id)
{
    int fd;

    if (socket_id == NULL_PTR)
    {
        return E_NOT_OK;
    }

    if ((domain != TCPIP_AF_INET) ||
        (protocol != TCPIP_IPPROTO_UDP))
    {
        return E_NOT_OK;
    }

    fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd < 0)
    {
        return E_NOT_OK;
    }

    *socket_id = (TcpIp_SocketIdType)fd;

    return E_OK;
}

void RtiPslConfig_apply(void)
{
    struct OSAPI_SystemAutosar system_property;

    if (!OSPSL_AutosarSystem_get_property(&system_property))
    {
        return;
    }

    system_property._parent.property.max_user_blocking_threads = 0;

    system_property.psl_property.timer_resolution_ms = 10U;

    system_property.psl_property.number_of_heap_areas = 1U;
    system_property.psl_property.heap_area_size = RtiPslHeapSize;
    system_property.psl_property.heap_area = RtiPslHeapAreas;
    system_property.psl_property.enable_thread_safe_heap = TRUE;

    system_property.psl_property.sync_type =
        OSAPI_AUTOSAR_SYNCKIND_RESOURCES;
    system_property.psl_property.mutex_resource_id =
        RTI_GlobalResource;

    system_property.psl_property.semaphore_max_count = 0U;
    system_property.psl_property.first_give_event = 0U;
    system_property.psl_property.first_timeout_event = 0U;
    system_property.psl_property.first_alarm = 0U;

    system_property.psl_property.use_socket_owner = TRUE;
    system_property.psl_property.max_receive_sockets = 1U;
    system_property.psl_property.number_of_rcv_buffers = 0U;
    system_property.psl_property.rcv_buffer_size = 0U;

    system_property.psl_property.get_socket = RtiPsl_get_socket;
    system_property.psl_property.send_data = NULL_PTR;

    system_property.psl_property.max_local_addr_id = 0U;
    system_property.psl_property.send_local_addr_id = 0U;

    system_property.psl_property.use_udp_thread = FALSE;
    system_property.psl_property.dds_rxindication = NULL_PTR;

    if (!OSPSL_AutosarSystem_set_property(&system_property))
    {
        return;
    }
}
