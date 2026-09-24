#include <stdio.h>
#include <string.h>

#include "VirtualAswc.h"
#include "Rte_DdsCddType.h"

void VirtualAswc_Run(void)
{
    static uint8 counter = 0U;

    GCS_LEFT_2_PDIO_FL_t read_data_0;
    Std_ReturnType read_status_0;

    read_status_0 = Rte_Read_R_GCS_LEFT_2_PDIO_FL_GCS_LEFT_2_PDIO_FL_t(&read_data_0);

    if (read_status_0 == E_OK)
    {
        printf("[VirtualAswc] GCS_LEFT_2_PDIO_FL received first=0x%02X\n",
                (unsigned int)((const uint8 *)&read_data_0)[0]);
    }

    Cabin_Door_PDIO_FL_t write_data_0;

    memset(&write_data_0, 0, sizeof(write_data_0));
    ((uint8 *)&write_data_0)[0] = counter++;
    (void)Rte_Write_S_Cabin_Door_PDIO_FL_Cabin_Door_PDIO_FL_t(&write_data_0);

}
