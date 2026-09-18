#include <string.h>

#include "tpl_os.h"
#include "Rte_DdsCddType.h"

extern void TcpIp_Log(const char *msg);

/*
 * Minimal Virtual RTE data storage.
 *
 * No application simulation is implemented yet.
 * Cabin_Door remains zero-initialized until an application writer is added.
 * GCS_LEFT stores the latest value written by DdsCdd.
 */
static Cabin_Door_PDIO_FL_t g_cabin_door_pdio_fl;
static GCS_LEFT_2_PDIO_FL_t g_gcs_left_2_pdio_fl;

Std_ReturnType
Rte_Read_R_Cabin_Door_PDIO_FL_Cabin_Door_PDIO_FL_t(
        Cabin_Door_PDIO_FL_t *data)
{
    if (data == NULL)
    {
        return E_NOT_OK;
    }

    memcpy(data, &g_cabin_door_pdio_fl, sizeof(*data));

    return E_OK;
}

Std_ReturnType
Rte_Write_S_GCS_LEFT_2_PDIO_FL_GCS_LEFT_2_PDIO_FL_t(
        const GCS_LEFT_2_PDIO_FL_t *data)
{
    if (data == NULL)
    {
        return E_NOT_OK;
    }

    memcpy(&g_gcs_left_2_pdio_fl, data, sizeof(*data));

    return E_OK;
}

/*
 * DdsCddTimerTick() contains this InternalTrigger.
 *
 * For this PoC the actual DdsCddTimerUpdate runnable is intentionally
 * scheduled by DdsCdd100ms_Task, so this trigger does not execute the
 * runnable directly.
 */
void Rte_IrTrigger_TimerTick_ITP_TimerUpdate(void)
{
}

/*
 * DDS RX callback context -> RTE InternalTrigger -> Extended Task event.
 */
void Rte_IrTrigger_DdsCdd_RxIndication_ITP_DdsCdd_RxIndication(void)
{
    (void)SetEvent(DdsCddProcessData_Task, DdsCddProcessDataEvent);
}
