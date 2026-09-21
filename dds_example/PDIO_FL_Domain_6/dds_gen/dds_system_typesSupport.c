/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from dds_system_types.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "dds_system_typesSupport.h"

/*** SOURCE_BEGIN ***/

/* =========================================================================== */

/* Requires */
#define TTYPENAME   dds_Cabin_Door_PDIO_FL_tTYPENAME

/* 
dds_Cabin_Door_PDIO_FL_tDataWriter (DDS_DataWriter)   
*/

/* Defines */
#define TDataWriter dds_Cabin_Door_PDIO_FL_tDataWriter
#define TData       dds_Cabin_Door_PDIO_FL_t

#include "dds_c/dds_c_tdatawriter_gen.h"

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
dds_Cabin_Door_PDIO_FL_tDataReader (DDS_DataReader)   
*/

/* Defines */
#define TDataReader dds_Cabin_Door_PDIO_FL_tDataReader
#define TDataSeq    dds_Cabin_Door_PDIO_FL_tSeq
#define TData       dds_Cabin_Door_PDIO_FL_t
#include "dds_c/dds_c_tdatareader_gen.h"
#undef TDataReader
#undef TDataSeq
#undef TData

DDS_ReturnCode_t
dds_Cabin_Door_PDIO_FL_tTypeSupport_register_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL)
    {
        goto done;
    }

    if (type_name == NULL)
    {
        type_name = dds_Cabin_Door_PDIO_FL_tTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    retcode = DDS_DomainParticipant_register_type(
        participant,
        type_name,
        dds_Cabin_Door_PDIO_FL_tTypePlugin_get());

    if (retcode != DDS_RETCODE_OK)
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}

#ifndef RTI_CERT
DDS_ReturnCode_t
dds_Cabin_Door_PDIO_FL_tTypeSupport_unregister_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL)
    {
        goto done;
    }

    if (type_name == NULL)
    {
        type_name = dds_Cabin_Door_PDIO_FL_tTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    if (dds_Cabin_Door_PDIO_FL_tTypePlugin_get() !=
    DDS_DomainParticipant_unregister_type(participant,type_name))
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}
#endif
const char*
dds_Cabin_Door_PDIO_FL_tTypeSupport_get_type_name(void)
{
    return dds_Cabin_Door_PDIO_FL_tTYPENAME;
}
dds_Cabin_Door_PDIO_FL_t *
dds_Cabin_Door_PDIO_FL_tTypeSupport_create_data(void)
{
    dds_Cabin_Door_PDIO_FL_t *data = NULL;

    data = dds_Cabin_Door_PDIO_FL_t_create();

    return data;
}

#ifndef RTI_CERT
DDS_ReturnCode_t
dds_Cabin_Door_PDIO_FL_tTypeSupport_delete_data(
    dds_Cabin_Door_PDIO_FL_t *data)
{
    dds_Cabin_Door_PDIO_FL_t_delete(data);
    return DDS_RETCODE_OK;
}
#endif

DDS_ReturnCode_t
dds_Cabin_Door_PDIO_FL_tTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,
    unsigned int *length,
    const dds_Cabin_Door_PDIO_FL_t *a_data,
    DDS_DataRepresentationId_t representation)
{
    struct CDR_Stream_t stream;
    RTI_UINT32 ser_length;

    if ((representation != DDS_XCDR_DATA_REPRESENTATION) &&
    (representation != DDS_AUTO_DATA_REPRESENTATION))
    {
        return DDS_RETCODE_BAD_PARAMETER;
    }

    if (buffer == NULL)
    {
        ser_length = dds_Cabin_Door_PDIO_FL_t_get_serialized_sample_size(NULL,0) +
        RTI_CDR_ENCAPSULATION_HEADER_SIZE;

        *length = ser_length;
        return DDS_RETCODE_OK;
    }

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,*length))
    {
        return DDS_RETCODE_ERROR;
    }

    /* Serialize the header on the inline Qos stream */
    if (!CDR_Stream_serialize_header(&stream,
    RTI_ENCAPSULATION_ID_CDR_NATIVE,
    RTI_CDR_ENCAPSULATION_OPTIONS_NONE))
    {
        return DDS_RETCODE_ERROR;
    }

    if (!dds_Cabin_Door_PDIO_FL_t_cdr_serialize(NULL,&stream,(const void *)a_data,NULL))
    {
        return DDS_RETCODE_ERROR;
    }

    *length = CDR_Stream_get_current_position_offset(&stream);

    return DDS_RETCODE_OK;
}

DDS_ReturnCode_t
dds_Cabin_Door_PDIO_FL_tTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const dds_Cabin_Door_PDIO_FL_t *a_data)
{
    return dds_Cabin_Door_PDIO_FL_tTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,
        length,
        a_data,
        DDS_AUTO_DATA_REPRESENTATION);
}

DDS_ReturnCode_t
dds_Cabin_Door_PDIO_FL_tTypeSupport_deserialize_data_from_cdr_buffer(
    dds_Cabin_Door_PDIO_FL_t *sample,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    DDS_EncapsulationId_t encapsulation;
    RTI_BOOL big_endian = RTI_FALSE;

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    if (!CDR_Stream_deserialize_header(&stream,&encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    if ((RTI_CDR_ENCAPSULATION_ID_CDR_LE != encapsulation) &&
    (RTI_CDR_ENCAPSULATION_ID_CDR_BE != encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    if (RTI_CDR_ENCAPSULATION_ID_CDR_BE == encapsulation)
    {
        big_endian = RTI_TRUE;
    }

    CDR_Stream_set_endianess(&stream,big_endian);

    if (!dds_Cabin_Door_PDIO_FL_t_cdr_deserialize(
        NULL,sample,&stream,NULL))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#undef TTYPENAME

/* =========================================================================== */

/* Requires */
#define TTYPENAME   dds_Cabin_Seat_PSUIO_DRV_tTYPENAME

/* 
dds_Cabin_Seat_PSUIO_DRV_tDataWriter (DDS_DataWriter)   
*/

/* Defines */
#define TDataWriter dds_Cabin_Seat_PSUIO_DRV_tDataWriter
#define TData       dds_Cabin_Seat_PSUIO_DRV_t

#include "dds_c/dds_c_tdatawriter_gen.h"

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
dds_Cabin_Seat_PSUIO_DRV_tDataReader (DDS_DataReader)   
*/

/* Defines */
#define TDataReader dds_Cabin_Seat_PSUIO_DRV_tDataReader
#define TDataSeq    dds_Cabin_Seat_PSUIO_DRV_tSeq
#define TData       dds_Cabin_Seat_PSUIO_DRV_t
#include "dds_c/dds_c_tdatareader_gen.h"
#undef TDataReader
#undef TDataSeq
#undef TData

DDS_ReturnCode_t
dds_Cabin_Seat_PSUIO_DRV_tTypeSupport_register_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL)
    {
        goto done;
    }

    if (type_name == NULL)
    {
        type_name = dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    retcode = DDS_DomainParticipant_register_type(
        participant,
        type_name,
        dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_get());

    if (retcode != DDS_RETCODE_OK)
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}

#ifndef RTI_CERT
DDS_ReturnCode_t
dds_Cabin_Seat_PSUIO_DRV_tTypeSupport_unregister_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL)
    {
        goto done;
    }

    if (type_name == NULL)
    {
        type_name = dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    if (dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_get() !=
    DDS_DomainParticipant_unregister_type(participant,type_name))
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}
#endif
const char*
dds_Cabin_Seat_PSUIO_DRV_tTypeSupport_get_type_name(void)
{
    return dds_Cabin_Seat_PSUIO_DRV_tTYPENAME;
}
dds_Cabin_Seat_PSUIO_DRV_t *
dds_Cabin_Seat_PSUIO_DRV_tTypeSupport_create_data(void)
{
    dds_Cabin_Seat_PSUIO_DRV_t *data = NULL;

    data = dds_Cabin_Seat_PSUIO_DRV_t_create();

    return data;
}

#ifndef RTI_CERT
DDS_ReturnCode_t
dds_Cabin_Seat_PSUIO_DRV_tTypeSupport_delete_data(
    dds_Cabin_Seat_PSUIO_DRV_t *data)
{
    dds_Cabin_Seat_PSUIO_DRV_t_delete(data);
    return DDS_RETCODE_OK;
}
#endif

DDS_ReturnCode_t
dds_Cabin_Seat_PSUIO_DRV_tTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,
    unsigned int *length,
    const dds_Cabin_Seat_PSUIO_DRV_t *a_data,
    DDS_DataRepresentationId_t representation)
{
    struct CDR_Stream_t stream;
    RTI_UINT32 ser_length;

    if ((representation != DDS_XCDR_DATA_REPRESENTATION) &&
    (representation != DDS_AUTO_DATA_REPRESENTATION))
    {
        return DDS_RETCODE_BAD_PARAMETER;
    }

    if (buffer == NULL)
    {
        ser_length = dds_Cabin_Seat_PSUIO_DRV_t_get_serialized_sample_size(NULL,0) +
        RTI_CDR_ENCAPSULATION_HEADER_SIZE;

        *length = ser_length;
        return DDS_RETCODE_OK;
    }

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,*length))
    {
        return DDS_RETCODE_ERROR;
    }

    /* Serialize the header on the inline Qos stream */
    if (!CDR_Stream_serialize_header(&stream,
    RTI_ENCAPSULATION_ID_CDR_NATIVE,
    RTI_CDR_ENCAPSULATION_OPTIONS_NONE))
    {
        return DDS_RETCODE_ERROR;
    }

    if (!dds_Cabin_Seat_PSUIO_DRV_t_cdr_serialize(NULL,&stream,(const void *)a_data,NULL))
    {
        return DDS_RETCODE_ERROR;
    }

    *length = CDR_Stream_get_current_position_offset(&stream);

    return DDS_RETCODE_OK;
}

DDS_ReturnCode_t
dds_Cabin_Seat_PSUIO_DRV_tTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const dds_Cabin_Seat_PSUIO_DRV_t *a_data)
{
    return dds_Cabin_Seat_PSUIO_DRV_tTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,
        length,
        a_data,
        DDS_AUTO_DATA_REPRESENTATION);
}

DDS_ReturnCode_t
dds_Cabin_Seat_PSUIO_DRV_tTypeSupport_deserialize_data_from_cdr_buffer(
    dds_Cabin_Seat_PSUIO_DRV_t *sample,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    DDS_EncapsulationId_t encapsulation;
    RTI_BOOL big_endian = RTI_FALSE;

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    if (!CDR_Stream_deserialize_header(&stream,&encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    if ((RTI_CDR_ENCAPSULATION_ID_CDR_LE != encapsulation) &&
    (RTI_CDR_ENCAPSULATION_ID_CDR_BE != encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    if (RTI_CDR_ENCAPSULATION_ID_CDR_BE == encapsulation)
    {
        big_endian = RTI_TRUE;
    }

    CDR_Stream_set_endianess(&stream,big_endian);

    if (!dds_Cabin_Seat_PSUIO_DRV_t_cdr_deserialize(
        NULL,sample,&stream,NULL))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#undef TTYPENAME

/* =========================================================================== */

/* Requires */
#define TTYPENAME   dds_GCS_LEFT_2_PDIO_FL_tTYPENAME

/* 
dds_GCS_LEFT_2_PDIO_FL_tDataWriter (DDS_DataWriter)   
*/

/* Defines */
#define TDataWriter dds_GCS_LEFT_2_PDIO_FL_tDataWriter
#define TData       dds_GCS_LEFT_2_PDIO_FL_t

#include "dds_c/dds_c_tdatawriter_gen.h"

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
dds_GCS_LEFT_2_PDIO_FL_tDataReader (DDS_DataReader)   
*/

/* Defines */
#define TDataReader dds_GCS_LEFT_2_PDIO_FL_tDataReader
#define TDataSeq    dds_GCS_LEFT_2_PDIO_FL_tSeq
#define TData       dds_GCS_LEFT_2_PDIO_FL_t
#include "dds_c/dds_c_tdatareader_gen.h"
#undef TDataReader
#undef TDataSeq
#undef TData

DDS_ReturnCode_t
dds_GCS_LEFT_2_PDIO_FL_tTypeSupport_register_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL)
    {
        goto done;
    }

    if (type_name == NULL)
    {
        type_name = dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    retcode = DDS_DomainParticipant_register_type(
        participant,
        type_name,
        dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_get());

    if (retcode != DDS_RETCODE_OK)
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}

#ifndef RTI_CERT
DDS_ReturnCode_t
dds_GCS_LEFT_2_PDIO_FL_tTypeSupport_unregister_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL)
    {
        goto done;
    }

    if (type_name == NULL)
    {
        type_name = dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    if (dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_get() !=
    DDS_DomainParticipant_unregister_type(participant,type_name))
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}
#endif
const char*
dds_GCS_LEFT_2_PDIO_FL_tTypeSupport_get_type_name(void)
{
    return dds_GCS_LEFT_2_PDIO_FL_tTYPENAME;
}
dds_GCS_LEFT_2_PDIO_FL_t *
dds_GCS_LEFT_2_PDIO_FL_tTypeSupport_create_data(void)
{
    dds_GCS_LEFT_2_PDIO_FL_t *data = NULL;

    data = dds_GCS_LEFT_2_PDIO_FL_t_create();

    return data;
}

#ifndef RTI_CERT
DDS_ReturnCode_t
dds_GCS_LEFT_2_PDIO_FL_tTypeSupport_delete_data(
    dds_GCS_LEFT_2_PDIO_FL_t *data)
{
    dds_GCS_LEFT_2_PDIO_FL_t_delete(data);
    return DDS_RETCODE_OK;
}
#endif

DDS_ReturnCode_t
dds_GCS_LEFT_2_PDIO_FL_tTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,
    unsigned int *length,
    const dds_GCS_LEFT_2_PDIO_FL_t *a_data,
    DDS_DataRepresentationId_t representation)
{
    struct CDR_Stream_t stream;
    RTI_UINT32 ser_length;

    if ((representation != DDS_XCDR_DATA_REPRESENTATION) &&
    (representation != DDS_AUTO_DATA_REPRESENTATION))
    {
        return DDS_RETCODE_BAD_PARAMETER;
    }

    if (buffer == NULL)
    {
        ser_length = dds_GCS_LEFT_2_PDIO_FL_t_get_serialized_sample_size(NULL,0) +
        RTI_CDR_ENCAPSULATION_HEADER_SIZE;

        *length = ser_length;
        return DDS_RETCODE_OK;
    }

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,*length))
    {
        return DDS_RETCODE_ERROR;
    }

    /* Serialize the header on the inline Qos stream */
    if (!CDR_Stream_serialize_header(&stream,
    RTI_ENCAPSULATION_ID_CDR_NATIVE,
    RTI_CDR_ENCAPSULATION_OPTIONS_NONE))
    {
        return DDS_RETCODE_ERROR;
    }

    if (!dds_GCS_LEFT_2_PDIO_FL_t_cdr_serialize(NULL,&stream,(const void *)a_data,NULL))
    {
        return DDS_RETCODE_ERROR;
    }

    *length = CDR_Stream_get_current_position_offset(&stream);

    return DDS_RETCODE_OK;
}

DDS_ReturnCode_t
dds_GCS_LEFT_2_PDIO_FL_tTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const dds_GCS_LEFT_2_PDIO_FL_t *a_data)
{
    return dds_GCS_LEFT_2_PDIO_FL_tTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,
        length,
        a_data,
        DDS_AUTO_DATA_REPRESENTATION);
}

DDS_ReturnCode_t
dds_GCS_LEFT_2_PDIO_FL_tTypeSupport_deserialize_data_from_cdr_buffer(
    dds_GCS_LEFT_2_PDIO_FL_t *sample,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    DDS_EncapsulationId_t encapsulation;
    RTI_BOOL big_endian = RTI_FALSE;

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    if (!CDR_Stream_deserialize_header(&stream,&encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    if ((RTI_CDR_ENCAPSULATION_ID_CDR_LE != encapsulation) &&
    (RTI_CDR_ENCAPSULATION_ID_CDR_BE != encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    if (RTI_CDR_ENCAPSULATION_ID_CDR_BE == encapsulation)
    {
        big_endian = RTI_TRUE;
    }

    CDR_Stream_set_endianess(&stream,big_endian);

    if (!dds_GCS_LEFT_2_PDIO_FL_t_cdr_deserialize(
        NULL,sample,&stream,NULL))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#undef TTYPENAME

/* =========================================================================== */

/* Requires */
#define TTYPENAME   dds_GCS_LEFT_2_PSUIO_DRV_tTYPENAME

/* 
dds_GCS_LEFT_2_PSUIO_DRV_tDataWriter (DDS_DataWriter)   
*/

/* Defines */
#define TDataWriter dds_GCS_LEFT_2_PSUIO_DRV_tDataWriter
#define TData       dds_GCS_LEFT_2_PSUIO_DRV_t

#include "dds_c/dds_c_tdatawriter_gen.h"

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
dds_GCS_LEFT_2_PSUIO_DRV_tDataReader (DDS_DataReader)   
*/

/* Defines */
#define TDataReader dds_GCS_LEFT_2_PSUIO_DRV_tDataReader
#define TDataSeq    dds_GCS_LEFT_2_PSUIO_DRV_tSeq
#define TData       dds_GCS_LEFT_2_PSUIO_DRV_t
#include "dds_c/dds_c_tdatareader_gen.h"
#undef TDataReader
#undef TDataSeq
#undef TData

DDS_ReturnCode_t
dds_GCS_LEFT_2_PSUIO_DRV_tTypeSupport_register_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL)
    {
        goto done;
    }

    if (type_name == NULL)
    {
        type_name = dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    retcode = DDS_DomainParticipant_register_type(
        participant,
        type_name,
        dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_get());

    if (retcode != DDS_RETCODE_OK)
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}

#ifndef RTI_CERT
DDS_ReturnCode_t
dds_GCS_LEFT_2_PSUIO_DRV_tTypeSupport_unregister_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL)
    {
        goto done;
    }

    if (type_name == NULL)
    {
        type_name = dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    if (dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_get() !=
    DDS_DomainParticipant_unregister_type(participant,type_name))
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}
#endif
const char*
dds_GCS_LEFT_2_PSUIO_DRV_tTypeSupport_get_type_name(void)
{
    return dds_GCS_LEFT_2_PSUIO_DRV_tTYPENAME;
}
dds_GCS_LEFT_2_PSUIO_DRV_t *
dds_GCS_LEFT_2_PSUIO_DRV_tTypeSupport_create_data(void)
{
    dds_GCS_LEFT_2_PSUIO_DRV_t *data = NULL;

    data = dds_GCS_LEFT_2_PSUIO_DRV_t_create();

    return data;
}

#ifndef RTI_CERT
DDS_ReturnCode_t
dds_GCS_LEFT_2_PSUIO_DRV_tTypeSupport_delete_data(
    dds_GCS_LEFT_2_PSUIO_DRV_t *data)
{
    dds_GCS_LEFT_2_PSUIO_DRV_t_delete(data);
    return DDS_RETCODE_OK;
}
#endif

DDS_ReturnCode_t
dds_GCS_LEFT_2_PSUIO_DRV_tTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,
    unsigned int *length,
    const dds_GCS_LEFT_2_PSUIO_DRV_t *a_data,
    DDS_DataRepresentationId_t representation)
{
    struct CDR_Stream_t stream;
    RTI_UINT32 ser_length;

    if ((representation != DDS_XCDR_DATA_REPRESENTATION) &&
    (representation != DDS_AUTO_DATA_REPRESENTATION))
    {
        return DDS_RETCODE_BAD_PARAMETER;
    }

    if (buffer == NULL)
    {
        ser_length = dds_GCS_LEFT_2_PSUIO_DRV_t_get_serialized_sample_size(NULL,0) +
        RTI_CDR_ENCAPSULATION_HEADER_SIZE;

        *length = ser_length;
        return DDS_RETCODE_OK;
    }

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,*length))
    {
        return DDS_RETCODE_ERROR;
    }

    /* Serialize the header on the inline Qos stream */
    if (!CDR_Stream_serialize_header(&stream,
    RTI_ENCAPSULATION_ID_CDR_NATIVE,
    RTI_CDR_ENCAPSULATION_OPTIONS_NONE))
    {
        return DDS_RETCODE_ERROR;
    }

    if (!dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_serialize(NULL,&stream,(const void *)a_data,NULL))
    {
        return DDS_RETCODE_ERROR;
    }

    *length = CDR_Stream_get_current_position_offset(&stream);

    return DDS_RETCODE_OK;
}

DDS_ReturnCode_t
dds_GCS_LEFT_2_PSUIO_DRV_tTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const dds_GCS_LEFT_2_PSUIO_DRV_t *a_data)
{
    return dds_GCS_LEFT_2_PSUIO_DRV_tTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,
        length,
        a_data,
        DDS_AUTO_DATA_REPRESENTATION);
}

DDS_ReturnCode_t
dds_GCS_LEFT_2_PSUIO_DRV_tTypeSupport_deserialize_data_from_cdr_buffer(
    dds_GCS_LEFT_2_PSUIO_DRV_t *sample,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    DDS_EncapsulationId_t encapsulation;
    RTI_BOOL big_endian = RTI_FALSE;

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    if (!CDR_Stream_deserialize_header(&stream,&encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    if ((RTI_CDR_ENCAPSULATION_ID_CDR_LE != encapsulation) &&
    (RTI_CDR_ENCAPSULATION_ID_CDR_BE != encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    if (RTI_CDR_ENCAPSULATION_ID_CDR_BE == encapsulation)
    {
        big_endian = RTI_TRUE;
    }

    CDR_Stream_set_endianess(&stream,big_endian);

    if (!dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_deserialize(
        NULL,sample,&stream,NULL))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#undef TTYPENAME

