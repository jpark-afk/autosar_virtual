

/**
* @file dds_cdd_adapter.c
* @brief DDS CDD Adapter Layer Implementation (Layer 2)
* 
* This file implements the adapter layer between AUTOSAR and RTI DDS Micro.
* See dds_cdd_adapter.h for detailed architectural documentation.
* 
* @details
* **Key Responsibilities**:
* - Initialize DDS with AUTOSAR system properties
* - Manage state machine for initialization sequencing
* - Convert types between AUTOSAR (Cabin_Door_PDIO_FL_t) and DDS (dds_Cabin_Door_PDIO_FL_t)
* - Convert types between AUTOSAR (GCS_LEFT_2_PDIO_FL_t) and DDS (dds_GCS_LEFT_2_PDIO_FL_t)
* - Forward TcpIp callbacks to DDS NETIO layer
* - Bridge RTE and DDS data flows
* 
* **Configuration Section** (lines 25-142):
    * All user-configurable parameters are centralized at the top of this file:
    * - Memory heap sizes
    * - Timer resolution
    * - Resource ID ranges
    * - Socket configuration
    * - TcpIp integration settings
    * 
    * Modify these values based on your AUTOSAR BSW configuration and application needs.
    * 
    * @note See dds_cdd_adapter.h for complete architectural documentation and usage examples.
    * 
    * @see dds_cdd_adapter.h
    */

#include "dds_cdd_adapter.h"
#include "../dds_impl/dds_impl.h"

    /* RTI DDS Micro System Includes */
#ifndef osapi_system_h
#include "osapi/osapi_system.h"
#endif

#ifndef netio_common_h
#include "netio/netio_common.h"
#endif

#include "rti_me_psl/ospsl/ospsl_os_autosar_log.h"

    /*==============================================================================
    *                        CONFIGURABLE SETTINGS
    *============================================================================*/

    /**
    * @defgroup ConfigurableSettings DDS CDD Configurable Settings
    * @{
        * 
        * This section contains all user-configurable settings for the DDS CDD module.
        * Modify these values based on your application requirements and BSW configuration.
        * 
        * For detailed configuration guidance, see the Integration Guide (docs/INTEGRATION.md).
        */

        /*------------------------------------------------------------------------------
        *                           Memory Configuration
        *----------------------------------------------------------------------------*/
        /**
        * @brief Number of separate heap areas for DDS memory management
        * 
        * Default is 1. Update heap_area_size and heap_area arrays if increased.
        */
#define DDSCDD_NUMBER_OF_HEAP_AREAS    1

        /**
        * @brief Size of heap areas in bytes
        * 
        * Used for all DDS allocations: entities, protocol buffers, sample storage.
        */
#define DDSCDD_CONNEXTDDSHEAP_SIZE (65536 * 1024) - 0x200

        /**
        * @brief DDS heap area sizes array
        * 
        * Contains size of each heap area. Update if DDSCDD_NUMBER_OF_HEAP_AREAS increased.
        */
        RTI_PRIVATE const uint32 heap_area_size[DDSCDD_NUMBER_OF_HEAP_AREAS] =
        {
            DDSCDD_CONNEXTDDSHEAP_SIZE
    };

    /**
    * @brief Static heap area 1 buffer
    * 
    * Pre-allocated static buffer for DDS memory management.
    */
    RTI_PRIVATE char heap_area1[DDSCDD_CONNEXTDDSHEAP_SIZE];

    /**
    * @brief Array of pointers to DDS heap areas
    * 
    * Update if adding more heap areas.
    */
    RTI_PRIVATE char* const heap_area[DDSCDD_NUMBER_OF_HEAP_AREAS] =
    {
        heap_area1
    };

    /** @} */ // end of ConfigurableSettings

/*------------------------------------------------------------------------------
*                        System Properties Configuration
*----------------------------------------------------------------------------*/
/**
* @brief Configure DDS system properties for AUTOSAR environment
* 
* Sets memory heap configuration, timer resolution, resource IDs, socket limits,
* and TcpIp integration callbacks. These values must match AUTOSAR BSW configuration.
* 
* @return 0 on success, -1 on failure
* 
* @pre OSAPI_System must be initialized
* @post System configured for AUTOSAR operation
* 
* @warning Configuration values must match OS, TcpIp BSW settings.
*/
RTI_PRIVATE int SetSystemProperties(void)
{
    struct OSAPI_SystemAutosar system_property;

    if (!OSPSL_AutosarSystem_get_property(&system_property))
    {
        AUTOSAR_LOG_DDS_SET_SYSTEM_PROPERTIES_FAILED(
                OSAPI_LOGKIND_ERROR)
                return -1;
    }

    /* Task OSAPI_SystemAutosar_timer_task is configured to run every 10 ms */
    system_property.psl_property.timer_resolution_ms = 10;

    /* Configure static memory heap areas */
    system_property.psl_property.number_of_heap_areas = DDSCDD_NUMBER_OF_HEAP_AREAS;
    system_property.psl_property.heap_area_size = heap_area_size;
    system_property.psl_property.heap_area = (const char **)heap_area;
    /* workaround#HAE - MAG-463 -  enable use_udp_thread (mobilgene specific) */
    system_property.psl_property.enable_thread_safe_heap =
    RTI_TRUE; /* TODO: Default is not thread safe, change to true if using multithread */

    /* Connext DDS Micro will use Resources as synchronization method */
    system_property.psl_property.sync_type = OSAPI_AUTOSAR_SYNCKIND_RESOURCES;
    system_property.psl_property.mutex_resource_id = OsResource_DdsMutex;
    system_property.psl_property.timer_resource_id = OsResource_DdsTimer;
    system_property.psl_property.netio_resource_id = OsResource_DdsNetio;

    /* AUTOSAR synchronization configuration - Resources only */
    system_property.psl_property.semaphore_max_count = 0;
    system_property.psl_property.first_give_event = 0;
    system_property.psl_property.first_timeout_event = 0;
    system_property.psl_property.first_alarm = 0;

    /* Enable AUTOSAR TcpIp Socket Owner integration */
    system_property.psl_property.use_socket_owner = TRUE;

    /* Configure socket limits based on multicast support */
#if defined(NETIO_CONFIG_ENABLE_MULTICAST) && (NETIO_CONFIG_ENABLE_MULTICAST)
    system_property.psl_property.max_receive_sockets = 4;  /* With multicast */
#else
    system_property.psl_property.max_receive_sockets = 2;  /* Unicast only */
#endif

    /* Disable internal UDP buffers - use AUTOSAR TcpIp stack buffers */
    system_property.psl_property.number_of_rcv_buffers = 20;
    system_property.psl_property.rcv_buffer_size = 1024;

    /* Set AUTOSAR TcpIp integration callbacks */
    system_property.psl_property.get_socket = DdsCdd_GetSocket;
    system_property.psl_property.send_data = NULL;
    system_property.psl_property.max_local_addr_id = 2;

    system_property.psl_property.send_local_addr_id = 0;

    /* Configure UDP thread handling - use synchronous mode for AUTOSAR */
    system_property.psl_property.use_udp_thread = TRUE;
    system_property.psl_property.dds_rxindication =
    DdsCddRxIndication;  /* TODO: Default name for dds rx indication, change if using custom callback */

    if (!OSPSL_AutosarSystem_set_property(&system_property))
    {
        AUTOSAR_LOG_DDS_SET_SYSTEM_PROPERTIES_FAILED(
                OSAPI_LOGKIND_ERROR)
                return -1;
    }

    return 0;
}

/*==============================================================================
*                            INTERNAL STATE
*============================================================================*/

/**
* @brief Current DDS initialization state (NOT configurable)
*/
RTI_PRIVATE DdsCdd_InitState_t DdsCdd_fv_InitState = DdsCdd_InitState_Uninitialized;

/*==============================================================================
*                     SW-C RUNNABLE IMPLEMENTATIONS
*============================================================================*/

/**********************************************************************************************************************
* DdsCdd_Adapter_Init()
*********************************************************************************************************************/
/**
* @brief Initialize DDS adapter and create DDS entities
* 
* Performs initialization based on current state. Sets system properties,
* creates DDS entities when uninitialized. May be called multiple times;
* only executes state transitions when appropriate. Does not block.
* 
* @post DDS entities created but disabled if successful
*/
void DdsCdd_Adapter_Init(void)
{
    sint8 retval;

    if (DdsCdd_fv_InitState != DdsCdd_InitState_Uninitialized)
    {
        return;
    }

    if (0 != SetSystemProperties())
    {
        AUTOSAR_LOG_DDS_SET_SYSTEM_PROPERTIES_FAILED(
                OSAPI_LOGKIND_ERROR)
                DdsCdd_fv_InitState = DdsCdd_InitState_Error;
        return;
    }
    else if(RTI_TRUE != OSAPI_System_initialize())
    {
        AUTOSAR_LOG_DDS_SYSTEM_INITIALIZE_FAILED(
                OSAPI_LOGKIND_ERROR)
                DdsCdd_fv_InitState = DdsCdd_InitState_Error;
        return;
    }
    else
    {
        DdsCdd_fv_InitState = DdsCdd_InitState_SystemPropertiesSet;
    }

    /* Create DDS entities (but do NOT enable them yet) */
    if (DdsCdd_fv_InitState == DdsCdd_InitState_SystemPropertiesSet)
    {
        retval = DdsImpl_CreateEntities();
        if (retval != 0)
        {
            AUTOSAR_LOG_DDS_CREATE_ENTITIES_FAILED(
                    OSAPI_LOGKIND_ERROR)
                    DdsCdd_fv_InitState = DdsCdd_InitState_Error;
            return;
        }
        DdsCdd_fv_InitState = DdsCdd_InitState_EntitiesCreated;
        /* Signal that DDS entities can be enabled */
        Trigger_DdsCdd_EnableEntities();
    }
}

/**********************************************************************************************************************
* DdsCdd_Adapter_Enable_DDSEntities()
*********************************************************************************************************************/
/**
* @brief Enable DDS entities after they have been created
*
* @pre DdsCdd_Adapter_Init() has created the DDS entities
* @post DDS entities are enabled on success
*/
void DdsCdd_Adapter_Enable_DDSEntities(void)
{
    if (DdsCdd_fv_InitState != DdsCdd_InitState_EntitiesCreated)
    {
        return;
    }

    /* Enable preemtion just before enabling DDS entities */
    OSPSL_AutosarSystem_preemption_enabled();
    if (DdsImpl_EnableEntities() == 0)
    {
        DdsCdd_fv_InitState = DdsCdd_InitState_EntitiesEnabled;
    }
    else
    {
        DdsCdd_fv_InitState = DdsCdd_InitState_Error;
    }
}

/**********************************************************************************************************************
* DdsCdd_Adapter_TimerTick()
*********************************************************************************************************************/
/**
* @brief Enable DDS entities and maintain DDS timer
*
* Enables DDS entities after creation. Maintains DDS internal
* timer on every call for protocol operation (reliability, discovery, liveliness).
* 
* @pre DdsCdd_Adapter_Init() must have created the DDS entities
* @post DDS entities enabled after creation
*
* @note Must be called regularly (10ms recommended) for proper DDS operation.
*       Missing calls will cause protocol timeouts and data loss.
*/
void DdsCdd_Adapter_TimerTick(void)
{
    if (!DdsCdd_Adapter_IsEnabled())
    {
        /* DDS entities are not enabled, skip timer tick */
        return;
    }
    /* Always call timer callback for DDS internal timer management */
    OSAPI_SystemAutosar_timer_callback();
    Trigger_DdsCdd_TimerUpdate();
}

/**********************************************************************************************************************
* DdsCdd_Adapter_TimerUpdate()
*********************************************************************************************************************/
/**
* @brief Enable DDS entities and maintain internal DDS timer
* 
* Enables DDS entities on first call after creation. Maintains DDS internal
* timer on every call for protocol operation (reliability, discovery, liveliness).
* 
* @pre DdsCdd_Adapter_Init() must have been called
* @post DDS entities enabled on first call after creation
* 
* @note Must be called regularly (10ms recommended) for proper DDS operation.
*       Missing calls will cause protocol timeouts and data loss.
*/
void DdsCdd_Adapter_TimerUpdate(void)
{
    OSAPI_SystemAutosar_handler_callback();
}

/**********************************************************************************************************************
* DdsCdd_Adapter_Write_Cabin_Door_PDIO_FL()
*********************************************************************************************************************/
/**
* @brief Convert RTE type to DDS type and publish to Cabin_Door_PDIO_FL DataWriter
* 
* Converts RTE type (Cabin_Door_PDIO_FL_t) to DDS type (dds_Cabin_Door_PDIO_FL_t) and writes
* to DataWriter. May block with RELIABLE QoS if queue full.
* 
* @param[in] rte_data Pointer to RTE type structure containing data to transmit
* @return TRUE on success, FALSE on error
* 
* @pre DDS entities must be enabled, rte_data must point to valid data
* @post Data published to DDS network
*/
boolean DdsCdd_Adapter_Write_Cabin_Door_PDIO_FL(const Cabin_Door_PDIO_FL_t* rte_data)
{
    dds_Cabin_Door_PDIO_FL_t dds_sample;
    int retval;

    /* Validate input parameter */
    if (rte_data == NULL)
    {
        return FALSE;
    }

    /* Check if entities are enabled */
    if (!DdsCdd_Adapter_IsEnabled())
    {
        AUTOSAR_LOG_DDS_INVALID_STATE(
                OSAPI_LOGKIND_ERROR,
                DdsCdd_InitState_EntitiesEnabled,
                DdsCdd_fv_InitState)
                return FALSE;
    }

    /* Convert AUTOSAR type (Cabin_Door_PDIO_FL_t) to DDS type (dds_Cabin_Door_PDIO_FL_t) */
    Cabin_Door_PDIO_FL_t_rte_to_dds(rte_data, &dds_sample);

    /* Write to DDS (DDS-specific operation) */
    retval = DdsImpl_Cabin_Door_PDIO_FL_WriteSample(&dds_sample);
    if (retval != 0)
    {
        AUTOSAR_LOG_DDS_ADAPTER_WRITE_FAILED(
                OSAPI_LOGKIND_ERROR, "Cabin_Door_PDIO_FL")
                return FALSE;
    }
    return TRUE;
}
/**********************************************************************************************************************
* DdsCdd_Adapter_Read_GCS_LEFT_2_PDIO_FL()
*********************************************************************************************************************/
/**
* @brief Read DataReader and convert DDS type to RTE type (Layer 2: Adapter)
* 
* Takes next available sample from GCS_LEFT_2_PDIO_FL DataReader, converts DDS type (dds_GCS_LEFT_2_PDIO_FL_t)

* to RTE type (GCS_LEFT_2_PDIO_FL_t), and returns data via output parameter.
* 
* @param[out] rte_data Pointer to RTE type structure to receive converted data
* @return 0 on success (valid data in rte_data), -1 if no data or error
* 
* @pre DDS entities must be enabled, rte_data must point to valid memory
* @post If successful, rte_data contains converted sample; sample removed from queue
*/
int DdsCdd_Adapter_Read_GCS_LEFT_2_PDIO_FL(GCS_LEFT_2_PDIO_FL_t* rte_data)
{
    dds_GCS_LEFT_2_PDIO_FL_t dds_sample = {0};
    int is_valid;
    int retval;

    /* Validate input parameter */
    if (rte_data == NULL)
    {
        return -1;
    }

    /* Check if entities are enabled */
    if (!DdsCdd_Adapter_IsEnabled())
    {
        AUTOSAR_LOG_DDS_INVALID_STATE(
                OSAPI_LOGKIND_ERROR,
                DdsCdd_InitState_EntitiesEnabled,
                DdsCdd_fv_InitState)
                return -1;
    }

    /* Take the next sample from DDS */
    retval = DdsImpl_GCS_LEFT_2_PDIO_FL_TakeNextSample(&dds_sample, &is_valid);

    if (retval != 0)
    {
        AUTOSAR_LOG_DDS_ADAPTER_READ_FAILED(
                OSAPI_LOGKIND_ERROR, "GCS_LEFT_2_PDIO_FL")
                return -1;
    }

    if (is_valid)
    {
        /* Convert DDS type (dds_GCS_LEFT_2_PDIO_FL_t) to AUTOSAR type (GCS_LEFT_2_PDIO_FL_t) */
        GCS_LEFT_2_PDIO_FL_t_dds_to_rte(&dds_sample, rte_data);
        return 0;
    }
    else
    {
        AUTOSAR_LOG_DDS_NO_VALID_DATA(
                OSAPI_LOGKIND_ERROR, "GCS_LEFT_2_PDIO_FL")
                return -1;
    }
}

/**********************************************************************************************************************
* DdsCdd_Adapter_IsEnabled()
*********************************************************************************************************************/
/**
* @brief Check if DDS adapter and entities are enabled
* @return TRUE if DDS adapter and entities are enabled, FALSE otherwise
*/
boolean DdsCdd_Adapter_IsEnabled(void)
{
    return (DdsCdd_fv_InitState == DdsCdd_InitState_EntitiesEnabled) ? TRUE : FALSE;
}

/*==============================================================================
*                        SOCKET OWNER INTEGRATION
*============================================================================*/

/* TcpIp_[SocketOwnerName]GetSocket - TODO: update if using different SocketOwner name */
/* Workaround#HAE - MAG-459 - mobilgene naming rule, prefix TcpIp_ (mobilgene specific) */
#define DDSCDD_SOCKET_OWNER_GET_SOCKET   TcpIp_TcpIp_DdsCddGetSocket   /* TcpIp_socket_name = TcpIp_DdsCdd */

/**
* @brief Request socket from TcpIp stack
* 
* Requests UDP socket allocation from TcpIp stack via configured SocketOwner.
* 
* @param[in] domain Protocol domain (IPv4/IPv6)
* @param[in] protocol Protocol type (UDP/TCP)
* @param[out] socket_id Pointer to store allocated socket ID
* @return E_OK if successful, E_NOT_OK otherwise
* 
* @note Update DDSCDD_SOCKET_OWNER_GET_SOCKET macro to match TcpIp BSW SocketOwner name
*/
Std_ReturnType DdsCdd_GetSocket(
        TcpIp_DomainType domain,
        TcpIp_ProtocolType protocol,
        P2VAR(TcpIp_SocketIdType, AUTOMATIC, TCPIP_APPL_DATA) socket_id
        )
{
    /* Call the configured TcpIp SocketOwner function */
    return DDSCDD_SOCKET_OWNER_GET_SOCKET(domain, protocol, socket_id);
}

/**
* @brief TcpIp local IP address assignment change notification
* 
* Callback invoked when local IP address state changes. Monitors LocalAddrId 0
* for ASSIGNED state.
* 
* @param[in] LocalAddrId Local address identifier
* @param[in] State New IP address state
* 
* @note Must be registered as LocalIpAddrAssignmentChg callback in TcpIp BSW config
*/
void DdsCdd_LocalIpAddrAssignmentChg(
        TcpIp_LocalAddrIdType LocalAddrId,
        TcpIp_IpAddrStateType State
        )
{
    NETIO_Autosar_update_ip_assignment_state(LocalAddrId, State);
    if((State == TCPIP_IPADDR_STATE_ASSIGNED))
    {
        NETIO_Autosar_on_ip_assigned(LocalAddrId);
    }
}

/**
* @brief TcpIp UDP packet reception notification
* 
* Callback invoked when UDP data is received. Forwards received data to DDS
* for RTPS protocol processing.
* 
* @param[in] SocketId Socket that received data
* @param[in] RemoteAddrPtr Remote address information
* @param[in] BufPtr Received data buffer
* @param[in] Length Length of received data
* 
* @note Must be registered as SocketOwner RxIndication callback in TcpIp BSW config
*/
void DdsCdd_RxIndication(
        TcpIp_SocketIdType SocketId,
        P2CONST(TcpIp_SockAddrType, AUTOMATIC, TCPIP_APPL_DATA) RemoteAddrPtr,
        P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) BufPtr,
        uint16 Length
        )
{
    if (!DdsCdd_Adapter_IsEnabled())
    {
        return;
    }
    /* Forward received UDP data indication to RTI DDS Micro NETIO layer */
    NETIO_Autosar_TcpIp_udp_rx_indication(SocketId, RemoteAddrPtr, BufPtr, Length);
}

/**
* @brief TcpIp socket event notification
* 
* Callback for TCP/IP events on managed sockets.
* 
* @param[in] SocketId Socket identifier
* @param[in] Event Event type
*/
void DdsCdd_TcpIpEvent(
        TcpIp_SocketIdType SocketId,
        TcpIp_EventType Event)
{
    (void)SocketId;
#if 0
#define TCPIP_TCP_RESET 0x01U                 /* TCP connection was reset, TCP socket and all related resources have been released. */
#define TCPIP_TCP_CLOSED 0x02U                /* TCP connection was closed successfully, TCP socket and all related resources have been released. */
#define TCPIP_TCP_FIN_RECEIVED 0x03U          /* A FIN signal was received on the TCP connection, TCP socket is still valid. */
#define TCPIP_UDP_CLOSED 0x04U                /* UDP socket and all related resources have been released. */
#define TCPIP_TLS_HEARTBEAT_NO_RESPONSE 0x05u /* Vector ext: TLS heartbeat response has not been received in time. */
#define TCPIP_TCP_CONNECTED 0x06U             /* Vector ext: TCP client connection to an external server was established successfully. (only used by TLS) */
#define TCPIP_TCP_ACCEPTED 0x07U              /* Vector ext: TCP server has accepted a connection from an external client. (only used by TLS) */
#endif
    if (Event == TCPIP_UDP_CLOSED)
    {
        NETIO_Autosar_on_socket_event(SocketId, Event);
    }
}
