

/**********************************************************************************************************************
*  FILE REQUIRES USER MODIFICATIONS
*  Template Scope: sections marked with Start and End comments
*  -------------------------------------------------------------------------------------------------------------------
*  This file includes template code that must be completed and/or adapted during BSW integration.
*  The template code is incomplete and only intended for providing a signature and an empty implementation.
*  It is neither intended nor qualified for use in series production without applying suitable quality measures.
*  The template code must be completed as described in the instructions given within this file and/or in the.
*  Technical Reference.
*  The completed implementation must be tested with diligent care and must comply with all quality requirements which.
*  are necessary according to the state of the art before its use.
*********************************************************************************************************************/
/**********************************************************************************************************************
*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*             File:  DdsCdd.c
*           Config:  ddsref.dpa
*        SW-C Type:  DdsCdd
*
*        Generator:  MICROSAR RTE Generator Version 4.31.0
*                    RTE Core Version 4.31.0
*          License:  CBD2201090
*
*      Description:  C-Code implementation template for SW-C <DdsCddType>
*********************************************************************************************************************/

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

/* PRQA S 0777, 0779 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2 */

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

#include "Rte_DdsCddType.h"

#include "DdsCdd_IpAddr.h" //Workaround#HAE - IpAddr_Async

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

/**
* @file DdsCdd.c
* @brief DDS Complex Device Driver - AUTOSAR Runnable Template
* 
* Provides AUTOSAR runnable implementations for DDS communication. Runnables
* handle RTE interaction and delegate to adapter layer for DDS operations.
* 
* This file is partially generated from ARXML. Only implementation sections
* between Start/End markers should be modified. Keep implementations simple.
* 
*/

#include "../adaptation/dds_cdd_adapter.h"

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

/* workaround#HAE - MAG-461 - section naming rule (mobilgene specific) */
#define DdsCddType_START_SEC_CODE
#include "DdsCddType_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
*
* Runnable Entity Name: ProcessData
*
*---------------------------------------------------------------------------------------------------------------------
*
* Executed if at least one of the following trigger conditions occurred:
*   - triggered by InternalTriggerOccurredEvent for InternalTriggeringPoint <ITP_DdsCdd_RxIndication>
of runnable <RxIndication>
*
*********************************************************************************************************************/
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
* Symbol: ProcessData_doc
*********************************************************************************************************************/

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

FUNC(void, DdsCdd_CODE) DdsCddProcessData(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
    * Symbol: DdsCddProcessData
    *********************************************************************************************************************/
    /* Processing received UDP packet, invoking NETIO_Autosar_udp_receive_callback */
    NETIO_Autosar_udp_receive_callback(); 

    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
    *********************************************************************************************************************/
}

/**********************************************************************************************************************
*
* Runnable Entity Name: Read_GCS_LEFT_2_PDIO_FL
*
*---------------------------------------------------------------------------------------------------------------------
*
* Executed if at least one of the following trigger conditions occurred:
*   - triggered on TimingEvent every 100ms
*
**********************************************************************************************************************
*
* Output Interfaces:
* ==================
*   Explicit S/R API:
*   -----------------
*   Std_ReturnType Rte_Write_S_GCS_LEFT_2_PDIO_FL_GCS_LEFT_2_PDIO_FL_t(const GCS_LEFT_2_PDIO_FL_t *data)
*
*********************************************************************************************************************/
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
* Symbol: Read_GCS_LEFT_2_PDIO_FL_doc
*********************************************************************************************************************/

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

FUNC(void, DdsCdd_CODE) DdsCddRead_GCS_LEFT_2_PDIO_FL(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
    * Symbol: DdsCddRead_GCS_LEFT_2_PDIO_FL
    *********************************************************************************************************************/

    GCS_LEFT_2_PDIO_FL_t rte_data;

    /* Poll from DDS (adapter converts DDS type to RTE type) */
    if (DdsCdd_Adapter_Read_GCS_LEFT_2_PDIO_FL(&rte_data) == 0)
    {
        /* Valid data received, write to RTE for application consumption */
        (void)Rte_Write_S_GCS_LEFT_2_PDIO_FL_GCS_LEFT_2_PDIO_FL_t(&rte_data);
    }

    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
    *********************************************************************************************************************/
}

/**********************************************************************************************************************
*
* Runnable Entity Name: DdsCddTimerTick
*
*---------------------------------------------------------------------------------------------------------------------
*
* Executed if at least one of the following trigger conditions occurred:
*   - triggered on TimingEvent every 10ms
*
*********************************************************************************************************************/
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
* Symbol: DdsCddTimerTick_doc
*********************************************************************************************************************/
/**
* @brief Periodic timer tick runnable for DDS protocols
*/
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

FUNC(void, DdsCdd_CODE) DdsCddTimerTick(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
    * Symbol: DdsCddTimerTick
    *********************************************************************************************************************/
    DdsCdd_Adapter_TimerTick();
    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
    *********************************************************************************************************************/
}

/**********************************************************************************************************************
*
* Runnable Entity Name: DdsCddTimerUpdate
*
*---------------------------------------------------------------------------------------------------------------------
*
* Executed if triggered by InternalTriggerOccurredEvent for InternalTriggeringPoint <ITP_TimerUpdate>
* of runnable <TimerTick>
*
*********************************************************************************************************************/
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
* Symbol: DdsCddTimerUpdate_doc
*********************************************************************************************************************/

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

FUNC(void, DdsCdd_CODE) DdsCddTimerUpdate(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
    * Symbol: DdsCddTimerUpdate
    *********************************************************************************************************************/
    DdsCdd_Adapter_TimerUpdate();
    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
    *********************************************************************************************************************/
}

/**********************************************************************************************************************
*
* Runnable Entity Name: RxIndication
*
*---------------------------------------------------------------------------------------------------------------------
*
* This runnable is never executed by the RTE.
*
**********************************************************************************************************************
*
* Internal Trigger Interfaces:
* ============================
*   Unqueued Internal Triggering:
*   -----------------------------
*   void Rte_IrTrigger_RxIndication_ITP_DdsCdd_RxIndication(void)
*
*********************************************************************************************************************/
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
* Symbol: RxIndication_doc
*********************************************************************************************************************/

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

FUNC(void, DdsCdd_CODE) DdsCddRxIndication(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
    * Symbol: DdsCddRxIndication
    *********************************************************************************************************************/
    /* UDP packet received, triggering DdsCddProcessDdsData */
    Trigger_DdsCdd_RxIndication(); 

    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
    *********************************************************************************************************************/
}

/**********************************************************************************************************************
*
* Runnable Entity Name: Enable
*
*---------------------------------------------------------------------------------------------------------------------
*
* Executed once after the RTE is started
*
*********************************************************************************************************************/
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
* Symbol: Start_doc
*********************************************************************************************************************/
/**
* @brief Initialization runnable triggered at ECU startup
* 
* Initializes DDS adapter on startup.
*/
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

FUNC(void, DdsCdd_CODE) DdsCddEnable(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
    * Symbol: DdsCddEnable
    *********************************************************************************************************************/

    /* Enable DDS Entities */
    DdsCdd_Adapter_Enable_DDSEntities();

    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
    *********************************************************************************************************************/
}

/**********************************************************************************************************************
*
* Runnable Entity Name: Init
*
*---------------------------------------------------------------------------------------------------------------------
*
* Executed once after the RTE is started
*
*********************************************************************************************************************/
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
* Symbol: Start_doc
*********************************************************************************************************************/
/**
* @brief Initialization runnable triggered at ECU startup
* 
* Initializes DDS adapter on startup.
*/
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

FUNC(void, DdsCdd_CODE) DdsCddInit(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
    * Symbol: DdsCddInit
    *********************************************************************************************************************/

    DdsCdd_Adapter_Init();

    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
    *********************************************************************************************************************/
}

//Workaround#HAE - IpAddr_Async
FUNC(void, DdsCdd_CODE) DdsCdd_LocalIpAddrAssignmentChg_Process(void)
{
    DdsCdd_ProcessIpAssignmentQueue();
}
/**********************************************************************************************************************
*
* Runnable Entity Name: Write_Cabin_Door_PDIO_FL
*
*---------------------------------------------------------------------------------------------------------------------
*
* Executed if at least one of the following trigger conditions occurred:
*   - triggered on DataReceivedEvent for DataElementPrototype <Cabin_Door_PDIO_FL_t> of PortPrototype <R_Cabin_Door_PDIO_FL>
*
**********************************************************************************************************************
*
* Input Interfaces:
* =================
*   Explicit S/R API:
*   -----------------
*   Std_ReturnType Rte_Read_R_Cabin_Door_PDIO_FL_Cabin_Door_PDIO_FL_t(Cabin_Door_PDIO_FL_t *data)
*
*********************************************************************************************************************/
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
* Symbol: Write_Cabin_Door_PDIO_FL_doc
*********************************************************************************************************************/

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

FUNC(void, DdsCdd_CODE) DdsCddWrite_Cabin_Door_PDIO_FL(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
    * Symbol: DdsCddWrite_Cabin_Door_PDIO_FL
    *********************************************************************************************************************/

    Cabin_Door_PDIO_FL_t rte_data;

    /* Read from RTE (data written by application SW-C) */
    if (Rte_Read_R_Cabin_Door_PDIO_FL_Cabin_Door_PDIO_FL_t(&rte_data) == E_OK)
    {
        /* Valid data available, convert and write to DDS */
        (void)DdsCdd_Adapter_Write_Cabin_Door_PDIO_FL(&rte_data);
    }

    /**********************************************************************************************************************
    * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
    *********************************************************************************************************************/
}

/* workaround#HAE - MAG-461 - section naming rule (mobilgene specific) */
#define DdsCddType_STOP_SEC_CODE
#include "DdsCddType_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
*********************************************************************************************************************/

/**********************************************************************************************************************
MISRA 2012 violations and justifications
*********************************************************************************************************************/

/* module specific MISRA deviations:
MD_Rte_0624:  MISRA rule: Rule8.3
Reason:     This MISRA violation is a consequence from the RTE requirements [SWS_Rte_01007] [SWS_Rte_01150].
The typedefs are never used in the same context.
Risk:       No functional risk. Only a cast to uint8* is performed.
Prevention: Not required.

MD_Rte_3206:  MISRA rule: Rule2.7
Reason:     The parameter are not used by the code in all possible code variants.
Risk:       No functional risk.
Prevention: Not required.

*/