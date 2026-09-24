#ifndef RTE_DDSCDDTYPE_H
#define RTE_DDSCDDTYPE_H

#include "Std_Types.h"
#include "Rte_Type.h"

/* --------------------------------------------------------------------------
 * Minimal AUTOSAR RTE compatibility for Virtual AUTOSAR
 * -------------------------------------------------------------------------- */

#ifndef FUNC
#define FUNC(rettype, memclass) rettype
#endif

#ifndef DdsCdd_CODE
#define DdsCdd_CODE
#endif

/* --------------------------------------------------------------------------
 * RTE Sender/Receiver APIs
 * -------------------------------------------------------------------------- */

Std_ReturnType
Rte_Read_R_Cabin_Door_PDIO_FL_Cabin_Door_PDIO_FL_t(
    Cabin_Door_PDIO_FL_t *data);

Std_ReturnType
Rte_Write_S_GCS_LEFT_2_PDIO_FL_GCS_LEFT_2_PDIO_FL_t(
    const GCS_LEFT_2_PDIO_FL_t *data);

Std_ReturnType
Rte_Read_R_GCS_LEFT_2_PDIO_FL_GCS_LEFT_2_PDIO_FL_t(
    GCS_LEFT_2_PDIO_FL_t *data);

Std_ReturnType
Rte_Write_S_Cabin_Door_PDIO_FL_Cabin_Door_PDIO_FL_t(
    const Cabin_Door_PDIO_FL_t *data);

/* --------------------------------------------------------------------------
 * RTE Internal Trigger APIs
 * -------------------------------------------------------------------------- */

void Rte_IrTrigger_DdsCdd_RxIndication_ITP_DdsCdd_RxIndication(void);

void Rte_IrTrigger_TimerTick_ITP_TimerUpdate(void);

void Rte_IrTrigger_DdsCdd_Init_ITP_Start(void);

/* --------------------------------------------------------------------------
 * Virtual DataReceivedEvent state
 * -------------------------------------------------------------------------- */

boolean Rte_ConsumeDataReceived_Cabin_Door_PDIO_FL(void);

/* --------------------------------------------------------------------------
 * RTI AUTOSAR PSL callback
 * -------------------------------------------------------------------------- */

FUNC(void, DdsCdd_CODE) DdsCddRxIndication(void);

#endif /* RTE_DDSCDDTYPE_H */
