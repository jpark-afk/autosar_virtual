#include <string.h>

#include "tpl_os.h"
#include "Rte_DdsCddType.h"

/* --------------------------------------------------------------------------
 * Virtual RTE data buffers
 * -------------------------------------------------------------------------- */

static Cabin_Door_PDIO_FL_t g_cabin_door_pdio_fl;
static GCS_LEFT_2_PDIO_FL_t g_gcs_left_2_pdio_fl;
static boolean g_cabin_door_pdio_fl_received = FALSE;

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

Std_ReturnType
Rte_Read_R_GCS_LEFT_2_PDIO_FL_GCS_LEFT_2_PDIO_FL_t(
        GCS_LEFT_2_PDIO_FL_t *data)
{
    if (data == NULL)
    {
        return E_NOT_OK;
    }

    memcpy(data, &g_gcs_left_2_pdio_fl, sizeof(*data));

    return E_OK;
}

Std_ReturnType
Rte_Write_S_Cabin_Door_PDIO_FL_Cabin_Door_PDIO_FL_t(
        const Cabin_Door_PDIO_FL_t *data)
{
    if (data == NULL)
    {
        return E_NOT_OK;
    }

    memcpy(&g_cabin_door_pdio_fl, data, sizeof(*data));
    g_cabin_door_pdio_fl_received = TRUE;

    return E_OK;
}

boolean Rte_ConsumeDataReceived_Cabin_Door_PDIO_FL(void)
{
    if (g_cabin_door_pdio_fl_received == FALSE)
    {
        return FALSE;
    }

    g_cabin_door_pdio_fl_received = FALSE;

    return TRUE;
}

void Rte_IrTrigger_DdsCdd_RxIndication_ITP_DdsCdd_RxIndication(void)
{
    (void)SetEvent(
        DdsCddProcessData_Task,
        DdsCddProcessDataEvent);
}

void Rte_IrTrigger_TimerTick_ITP_TimerUpdate(void)
{
    (void)SetEvent(
        DdsCddWrite_Task,
        DdsCddTimerUpdateEvent);
}
