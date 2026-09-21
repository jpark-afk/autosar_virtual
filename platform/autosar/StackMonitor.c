#include "StackMonitor.h"

#include <stdint.h>
#include <stddef.h>

#include "tpl_app_define.h"
#include "tpl_os_kernel.h"
#include "tpl_machine.h"

#define PHASE9_STACK_PATTERN ((tpl_stack_word)0xA5A5A5A5U)

void Phase9_StackMonitor_Init(void)
{
    unsigned int task_id;

    for (task_id = 0U; task_id < (unsigned int)TASK_COUNT; ++task_id)
    {
        const tpl_proc_static *proc = tpl_stat_proc_table[task_id];
        tpl_stack_word *zone;
        size_t word_count;
        size_t i;

        if ((proc == NULL) || (proc->stack == NULL))
        {
            continue;
        }

        zone = proc->stack->stack_zone;
        word_count =
            (size_t)proc->stack->stack_size / sizeof(tpl_stack_word);

        for (i = 0U; i < word_count; ++i)
        {
            zone[i] = PHASE9_STACK_PATTERN;
        }
    }
}

int Phase9_StackMonitor_GetUsage(
    unsigned int task_id,
    Phase9_StackUsage *usage)
{
    const tpl_proc_static *proc;
    const tpl_stack_word *zone;
    size_t word_count;
    size_t untouched_words = 0U;
    size_t i;

    if ((usage == NULL) ||
        (task_id >= (unsigned int)TASK_COUNT))
    {
        return -1;
    }

    proc = tpl_stat_proc_table[task_id];

    if ((proc == NULL) || (proc->stack == NULL))
    {
        return -1;
    }

    zone = proc->stack->stack_zone;
    word_count =
        (size_t)proc->stack->stack_size / sizeof(tpl_stack_word);

    /*
     * POSIX/x86_64 stack is expected to grow from high addresses
     * toward low addresses.
     *
     * Count untouched words starting at the low-address boundary.
     */
    for (i = 0U; i < word_count; ++i)
    {
        if (zone[i] != PHASE9_STACK_PATTERN)
        {
            break;
        }

        untouched_words++;
    }

    usage->allocated_bytes =
        (size_t)proc->stack->stack_size;

    usage->free_high_water_bytes =
        untouched_words * sizeof(tpl_stack_word);

    usage->used_high_water_bytes =
        usage->allocated_bytes -
        usage->free_high_water_bytes;

    return 0;
}
