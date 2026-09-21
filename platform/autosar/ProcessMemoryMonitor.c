#include "ProcessMemoryMonitor.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>

static int Phase9_ParseKb(
    const char *line,
    const char *key,
    size_t *value)
{
    unsigned long parsed;

    if (strncmp(line, key, strlen(key)) != 0)
    {
        return 0;
    }

    if (sscanf(line + strlen(key), "%lu", &parsed) != 1)
    {
        return -1;
    }

    *value = (size_t)parsed;

    return 1;
}

int Phase9_ProcessMemory_GetUsage(
    Phase9_ProcessMemoryUsage *usage)
{
    FILE *fp;
    char line[256];
    struct mallinfo2 mi;

    if (usage == NULL)
    {
        return -1;
    }

    memset(usage, 0, sizeof(*usage));

    fp = fopen("/proc/self/status", "r");

    if (fp == NULL)
    {
        return -1;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        Phase9_ParseKb(line, "VmRSS:",  &usage->vm_rss_kb);
        Phase9_ParseKb(line, "VmHWM:",  &usage->vm_hwm_kb);
        Phase9_ParseKb(line, "VmSize:", &usage->vm_size_kb);
        Phase9_ParseKb(line, "VmData:", &usage->vm_data_kb);
    }

    fclose(fp);

    mi = mallinfo2();

    usage->glibc_arena_bytes = (size_t)mi.arena;
    usage->glibc_used_bytes  = (size_t)mi.uordblks;
    usage->glibc_free_bytes  = (size_t)mi.fordblks;
    usage->glibc_mmap_bytes  = (size_t)mi.hblkhd;

    return 0;
}
