#include "MemorySnapshot.h"

#include <stdio.h>

#include "tpl_app_define.h"

#include "StackMonitor.h"
#include "ProcessMemoryMonitor.h"

int Phase9_MemorySnapshot_WriteJson(
    const char *path)
{
    FILE *fp;
    Phase9_ProcessMemoryUsage process_usage;
    unsigned int task_id;

    if (path == NULL)
    {
        return -1;
    }

    if (Phase9_ProcessMemory_GetUsage(
            &process_usage) != 0)
    {
        return -1;
    }

    fp = fopen(path, "w");

    if (fp == NULL)
    {
        return -1;
    }

    fprintf(fp,
        "{\n"
        "  \"schema\": \"phase9-memory-v1\",\n"
        "  \"task_stack\": [\n");

    for (task_id = 0U;
         task_id < (unsigned int)TASK_COUNT;
         ++task_id)
    {
        Phase9_StackUsage stack_usage;

        if (Phase9_StackMonitor_GetUsage(
                task_id,
                &stack_usage) != 0)
        {
            fclose(fp);
            return -1;
        }

        fprintf(fp,
            "    {\n"
            "      \"task_id\": %u,\n"
            "      \"allocated_bytes\": %zu,\n"
            "      \"used_high_water_bytes\": %zu,\n"
            "      \"free_high_water_bytes\": %zu\n"
            "    }%s\n",
            task_id,
            stack_usage.allocated_bytes,
            stack_usage.used_high_water_bytes,
            stack_usage.free_high_water_bytes,
            (task_id + 1U < (unsigned int)TASK_COUNT)
                ? "," : "");
    }

    fprintf(fp,
        "  ],\n"
        "  \"process\": {\n"
        "    \"vm_rss_kb\": %zu,\n"
        "    \"vm_hwm_kb\": %zu,\n"
        "    \"vm_size_kb\": %zu,\n"
        "    \"vm_data_kb\": %zu\n"
        "  },\n"
        "  \"glibc\": {\n"
        "    \"arena_bytes\": %zu,\n"
        "    \"used_bytes\": %zu,\n"
        "    \"free_bytes\": %zu,\n"
        "    \"mmap_bytes\": %zu\n"
        "  }\n"
        "}\n",
        process_usage.vm_rss_kb,
        process_usage.vm_hwm_kb,
        process_usage.vm_size_kb,
        process_usage.vm_data_kb,
        process_usage.glibc_arena_bytes,
        process_usage.glibc_used_bytes,
        process_usage.glibc_free_bytes,
        process_usage.glibc_mmap_bytes);

    if (fclose(fp) != 0)
    {
        return -1;
    }

    return 0;
}
