#include <stdlib.h>
#include <stdint.h>

/*
 * RTI Micro x86_64 PIL ABI:
 * RTI_SIZE_T is defined as RTI_UINT32.
 *
 * Minimal Virtual AUTOSAR compatibility implementation.
 */
typedef uint32_t RTI_SIZE_T;

void *
OSAPI_Heap_realloc(void *ptr, RTI_SIZE_T size)
{
    if (size == 0U)
    {
        return NULL;
    }

    return realloc(ptr, (size_t)size);
}
