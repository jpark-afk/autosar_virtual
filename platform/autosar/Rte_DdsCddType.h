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

/* --------------------------------------------------------------------------
 * RTE Internal Trigger APIs
 * -------------------------------------------------------------------------- */

void Rte_IrTrigger_TimerTick_ITP_TimerUpdate(void);

void Rte_IrTrigger_DdsCdd_RxIndication_ITP_DdsCdd_RxIndication(void);

#endif /* RTE_DDSCDDTYPE_H */

/* DDS CDD runnable callback invoked by RTI AUTOSAR PSL on UDP reception. */
FUNC(void, DdsCdd_CODE) DdsCddRxIndication(void);
