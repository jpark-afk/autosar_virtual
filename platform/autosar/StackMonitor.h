#ifndef STACK_MONITOR_H
#define STACK_MONITOR_H

#include <stddef.h>

typedef struct
{
    size_t allocated_bytes;
    size_t used_high_water_bytes;
    size_t free_high_water_bytes;
} Phase9_StackUsage;

void Phase9_StackMonitor_Init(void);

int Phase9_StackMonitor_GetUsage(
    unsigned int task_id,
    Phase9_StackUsage *usage);

#endif
