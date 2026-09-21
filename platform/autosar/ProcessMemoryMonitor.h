#ifndef PROCESS_MEMORY_MONITOR_H
#define PROCESS_MEMORY_MONITOR_H

#include <stddef.h>

typedef struct
{
    size_t vm_rss_kb;
    size_t vm_hwm_kb;
    size_t vm_size_kb;
    size_t vm_data_kb;

    size_t glibc_arena_bytes;
    size_t glibc_used_bytes;
    size_t glibc_free_bytes;
    size_t glibc_mmap_bytes;
} Phase9_ProcessMemoryUsage;

int Phase9_ProcessMemory_GetUsage(
    Phase9_ProcessMemoryUsage *usage);

#endif
