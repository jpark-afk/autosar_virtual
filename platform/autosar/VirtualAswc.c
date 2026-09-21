#include <string.h>

#include "VirtualAswc.h"
#include "Rte_DdsCddType.h"

void VirtualAswc_Run(void)
{
    static uint8 counter = 0U;

    GCS_LEFT_2_PDIO_FL_t read_data_0;

    (void)Rte_Read_R_GCS_LEFT_2_PDIO_FL_GCS_LEFT_2_PDIO_FL_t(&read_data_0);

    Cabin_Door_PDIO_FL_t write_data_0;

    memset(&write_data_0, 0, sizeof(write_data_0));
    ((uint8 *)&write_data_0)[0] = counter++;
    (void)Rte_Write_S_Cabin_Door_PDIO_FL_Cabin_Door_PDIO_FL_t(&write_data_0);

}
