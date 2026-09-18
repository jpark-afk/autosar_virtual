#include <stdio.h>

#include "tpl_os.h"
#include "rti_me_psl.h"
#include "RtiPslConfig.h"

extern RTI_BOOL OSAPI_AutosarSystem_initialize(void);

int main(void)
{
    printf("[Virtual AUTOSAR] Starting Trampoline OS\n");
    StartOS(stdAppmode);
    return 0;
}

TASK(RTI_Task)
{
    RTI_BOOL ok;

    printf("[Virtual AUTOSAR] RTI_Task started\n");

    RtiPslConfig_apply();

    printf("[Virtual AUTOSAR] RTI PSL configuration applied\n");

    ok = OSAPI_System_initialize();

    if (!ok)
    {
        printf("[Virtual AUTOSAR] ERROR: OSAPI_System_initialize failed\n");
        ShutdownOS(E_OK);
    }

    printf("[Virtual AUTOSAR] OSAPI_System_initialize PASS\n");

#ifndef RTI_CERT
    ok = OSAPI_System_finalize();

    if (!ok)
    {
        printf("[Virtual AUTOSAR] ERROR: OSAPI_System_finalize failed\n");
        ShutdownOS(E_OK);
    }

    printf("[Virtual AUTOSAR] OSAPI_System_finalize PASS\n");
#endif

    printf("[Virtual AUTOSAR] Phase2 PASS\n");

    ShutdownOS(E_OK);

    TerminateTask();
}
