

/**
* @file dds_cdd_adapter.h
* @brief DDS CDD Adapter Layer Interface (Layer 2)
* 
* This file provides the adapter layer interface between AUTOSAR and RTI DDS Micro.
* It bridges the AUTOSAR SW-C (Layer 1) and pure DDS implementation (Layer 3).
* 
* @details
* **Three-Layer Architecture**:
* - **Layer 1: RTE Template** (DdsCdd.c)
*   - AUTOSAR runnables called by RTE
*   - Partially generated from ARXML (signatures), integrator implements by calling Layer 2
*   - Delegates all work to Layer 2
* 
* - **Layer 2: Adapter** (dds_cdd_adapter.c/h) **[THIS FILE]**
*   - Bridges AUTOSAR and DDS
*   - Type conversion
*   - State machine for initialization sequencing
*   - AUTOSAR callbacks (TcpIp, IP address assignment)
* 
* - **Layer 3: DDS Implementation** (dds_impl.c/h)
*   - Pure DDS operations
*   - Entity creation and management
*   - Read/write operations
*   - No AUTOSAR dependencies
* 
* **State Machine**:
* The adapter manages DDS initialization through these states:
* 1. TCPIP_NOT_READY - Waiting for IP address assignment
* 2. TCPIP_READY - IP assigned, ready to set system properties
* 3. SYSTEM_PROPERTIES_SET - Properties configured, ready to create entities
* 4. ENTITIES_CREATED - DDS entities created but disabled
* 5. ENTITIES_ENABLED - Fully operational, can send/receive data
* 6. ERROR - Initialization failed
* 
* **Configuration Requirements**:
* 
* 1. **TcpIp BSW Configuration**:
*    - Define SocketOwner named \"DdsSocketOwner\" (or customize via macro)
*    - Register callbacks: LocalIpAddrAssignmentChg, RxIndication
*    - Allocate sufficient sockets (2-3 depending on multicast)
* 
* 2. **OS Configuration**:
*    - Define Resources: DDS_Resource001 through DDS_Resource037
*    - Configure Task_DdsCdd with appropriate priority
*    - Timer resolution: 10ms
* 
* 3. **Memory Configuration**:
*    - Default heap: 240KB (configurable via DDSCDD_HEAP_AREA_1_SIZE)
*    - Adjust based on application needs (more topics, larger samples)
* 
* 4. **SocketOwner Name Override**:
*    If your TcpIp BSW uses a different SocketOwner name, define before including:
*    ```c
*    #define DDSCDD_SOCKET_OWNER_NAME YourSocketOwnerName
*    #include "dds_cdd_adapter.h"
*    ```
*    This generates the correct function call: TcpIp_YourSocketOwnerNameGetSocket(...)
* 
* **Usage Example**:
* ```c
* // Called automatically by RTE, application code doesn't call these directly
* 
* // 1. Initialization (once at startup)
* DdsCddStart()  // -> DdsCdd_Adapter_Init()
* 
* // 2. Cyclic execution (every 10ms)
* DdsCddRun()    // -> DdsCdd_Adapter_Run()
* 
* // 3. Receive data (every 100ms or as needed)
* DdsCddRead_GCS_LEFT_2_PDIO_FL()  // -> DdsCdd_Adapter_Read_GCS_LEFT_2_PDIO_FL
* 
* // 4. Transmit data (event-driven when app writes to RTE)
* DdsCddWrite_Cabin_Door_PDIO_FL() // -> DdsCdd_Adapter_Write_Cabin_Door_PDIO_FL()
* ```
* 
* @note This layer has AUTOSAR dependencies and is specific to AUTOSAR integration.
*       For non-AUTOSAR use, only Layer 3 (dds_impl) would be needed.
* 
* @see dds_impl.h for Layer 3 DDS implementation
* @see DdsCdd.c for Layer 1 RTE template
*/

#ifndef DDSCDD_ADAPTER_H
#define DDSCDD_ADAPTER_H

/* AUTOSAR Standard Includes */
/* TODO: Adjust includes based on your BSW configuration */
#include "Std_Types.h"
#include "Os_Cfg.h"
#include "TcpIp.h"
#include "Rte_DdsCddType.h"  /* Provides dds_system type definition and RTE function signatures */

/* workaround#HAE - MICRO-13500 */ 
/* RTI DDS Micro includes are intentionally kept out of this public header.
* Include them in implementation files only to avoid macro conflicts with
* AUTOSAR compiler abstraction (e.g., CONST/VAR macros). */
#ifndef VVIRTUALTARGET
#include "dds_impl.h"
#endif

/* workaround#HAE - MAG-460 - add an user_stub header file */
#include "dds_cdd_userstub.h" //SHOULD BE CREATED EXTERNALLY

/*==============================================================================
*                        AUTOSAR MEMORY/CODE SECTIONS
*============================================================================*/

/* Define memory section for DDS CDD code */
#ifndef DDSCDD_CODE
#define DDSCDD_CODE
#endif

/*==============================================================================
*                        CONFIGURABLE SETTINGS
*============================================================================*/
/* Trigger_DdsCdd_RxIndication - TODO: Update if callback for the ITP has different name */
#define Trigger_DdsCdd_RxIndication Rte_IrTrigger_DdsCdd_RxIndication_ITP_DdsCdd_RxIndication

/*==============================================================================
*                                TYPES
*============================================================================*/

/**
* @brief DDS initialization state tracking
*/
typedef enum
{
    /* workaround#COMMON - MAG-438 - Init task overrun issue. */
    //DdsCdd_InitState_TcpIpNotReady = 0,
    //DdsCdd_InitState_TcpIpReady,
    DdsCdd_InitState_Uninitialized = 0,

    DdsCdd_InitState_SystemPropertiesSet,
    DdsCdd_InitState_EntitiesCreated,
    DdsCdd_InitState_EntitiesEnabled,
    DdsCdd_InitState_Error
} DdsCdd_InitState_t;

/*==============================================================================
*                        FUNCTION DECLARATIONS
*============================================================================*/

/**
* @brief Request socket from TcpIp stack
*
* @param[in] domain Protocol domain (IPv4/IPv6)
* @param[in] protocol Protocol type (UDP/TCP)
* @param[out] socket_id Pointer to store allocated socket ID
* @return E_OK if successful, E_NOT_OK otherwise
*
* @note Must be registered in TcpIp BSW config. Update DDSCDD_SOCKET_OWNER_GET_SOCKET
*       macro if SocketOwner name differs from default.
*/
Std_ReturnType DdsCdd_GetSocket(
        TcpIp_DomainType domain,
        TcpIp_ProtocolType protocol,
        P2VAR(TcpIp_SocketIdType, AUTOMATIC, TCPIP_APPL_DATA) socket_id
        );

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
        );

/**
* @brief TcpIp UDP packet reception notification
*
* Callback invoked when UDP data is received. Forwards data for RTPS processing.
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
        );

/**
* @brief TcpIp socket event notification
*
* Callback for TCP/IP events on managed sockets.
*
* @param[in] SocketId Socket identifier
* @param[in] Event Event type
*
* @note Must be registered as SocketOwner TcpIpEvent callback in TcpIp BSW config
*/
void DdsCdd_TcpIpEvent(
        TcpIp_SocketIdType SocketId,
        TcpIp_EventType Event
        );

/*==============================================================================
*                        ADAPTER FUNCTION DECLARATIONS
*============================================================================*/

/**
* @brief Initialize DDS adapter
* 
* Sets system properties and creates DDS entities.
*/
void DdsCdd_Adapter_Init(void);

/* workaround#COMMON - MAG-438 - Init task overrun issue */
/**
* @brief Enable DDS entities
* 
* Enables DDS entities after creation.
*/
void DdsCdd_Adapter_Enable_DDSEntities(void);

/**
* @brief Run DDS adapter periodic tasks
* 
* Enables entities (first call) and maintains DDS timer. Must be called regularly.
*/
void DdsCdd_Adapter_Run(void);

/**
* @brief Convert RTE type to DDS type and write to TopicC DataWriter
*
* @param[in] rte_data Pointer to RTE type structure containing data to transmit
* @return 0 on success, -1 on error
*/
int DdsCdd_Adapter_Write_Cabin_Door_PDIO_FL(const Cabin_Door_PDIO_FL_t* rte_data);
/**
* @brief Read DataReader for TopicC and convert DDS type to RTE type
*
* @param[out] rte_data Pointer to RTE type structure to receive converted data
* @return 0 on success (valid data returned), -1 if no data or error
*/
int DdsCdd_Adapter_Read_GCS_LEFT_2_PDIO_FL(GCS_LEFT_2_PDIO_FL_t* rte_data);

#endif /* DDSCDD_ADAPTER_H */