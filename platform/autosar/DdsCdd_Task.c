#include "tpl_os.h"
#include "Rte_DdsCddType.h"

/* --------------------------------------------------------------------------
 * CDD runnable declarations
 * -------------------------------------------------------------------------- */

extern void DdsCddProcessData(void);
extern void DdsCddRead_GCS_LEFT_2_PDIO_FL(void);
extern void DdsCddTimerTick(void);
extern void DdsCddTimerUpdate(void);
extern void DdsCddWrite_Cabin_Door_PDIO_FL(void);

/* --------------------------------------------------------------------------
 * CDD TimerTick task
 * -------------------------------------------------------------------------- */

TASK(DdsCddTimerTick_Task)
{
    DdsCddTimerTick();

    TerminateTask();
}

/* --------------------------------------------------------------------------
 * CDD Read/Write task
 * -------------------------------------------------------------------------- */

TASK(DdsCddReadWrite_Task)
{
    EventMaskType events;

    for (;;)
    {
        WaitEvent(
            DdsCddTimerUpdateEvent |
            DdsCddPeriodicReadEvent);

        GetEvent(DdsCddReadWrite_Task, &events);

        if ((events & DdsCddTimerUpdateEvent) != 0U)
        {
            ClearEvent(DdsCddTimerUpdateEvent);

            DdsCddTimerUpdate();
        }

        if ((events & DdsCddPeriodicReadEvent) != 0U)
        {
            ClearEvent(DdsCddPeriodicReadEvent);

            if (Rte_ConsumeDataReceived_Cabin_Door_PDIO_FL() != FALSE)
            {
                DdsCddWrite_Cabin_Door_PDIO_FL();
            }

            DdsCddRead_GCS_LEFT_2_PDIO_FL();
        }
    }
}

/* --------------------------------------------------------------------------
 * CDD ProcessData task
 * -------------------------------------------------------------------------- */

TASK(DdsCddProcessData_Task)
{
    EventMaskType events;

    for (;;)
    {
        WaitEvent(DdsCddProcessDataEvent);

        GetEvent(DdsCddProcessData_Task, &events);

        if ((events & DdsCddProcessDataEvent) != 0U)
        {
            ClearEvent(DdsCddProcessDataEvent);

            DdsCddProcessData();
        }
    }
}
