/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from dds_system_types.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "dds_system_types.h"
#include "reda/reda_bufferpool.h"
#if DDS_XTYPES_IS_ENABLED
#include "xcdr/xcdr_interpreter.h"
#include "xcdr/xcdr_dds_xcdr_type_plugin.h"
#include "xcdr/xcdr_dds_interpreter.h"
#endif
#include "dds_system_typesPlugin.h"

/*** SOURCE_BEGIN ***/
#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

RTI_UINT32
dds_Cabin_Door_PDIO_FL_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment)
{
    RTI_UINT32 initial_alignment = current_alignment;

    UNUSED_ARG(plugin);

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_float(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_float(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    return  current_alignment - initial_alignment;
}
RTI_BOOL
dds_Cabin_Door_PDIO_FL_t_cdr_serialize(struct DDS_TypePlugin *plugin,
struct CDR_Stream_t *stream,
const void *void_sample,
DDS_InstanceHandle_t *destination)
{
    dds_Cabin_Door_PDIO_FL_t *sample = (dds_Cabin_Door_PDIO_FL_t *)void_sample;

    UNUSED_ARG(plugin);
    UNUSED_ARG(destination);

    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_Driver_Door_Switch_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_Driver_Door_Unlock_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_PwrDrAvailability)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_float(
        stream, &sample->PDIO_FL_PwrDrAngle)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_PwrDrStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_PwrDrSwingActrStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_PwrDrErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_PwrDrAntiPinchStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_float(
        stream, &sample->PDIO_FL_PwrDrAngleSpeed)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_InsdOpnClsSwStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_OtsdOpnClsSwStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_SleepReady)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_WakeupRequest)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_CinchingStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PDIO_FL_ActiveHoldingState)) {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_BOOL
dds_Cabin_Door_PDIO_FL_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source)
{
    dds_Cabin_Door_PDIO_FL_t *sample = (dds_Cabin_Door_PDIO_FL_t*)void_sample;

    UNUSED_ARG(plugin);
    UNUSED_ARG(source);

    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_Driver_Door_Switch_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_Driver_Door_Unlock_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_PwrDrAvailability)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_float(
        stream, &sample->PDIO_FL_PwrDrAngle)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_PwrDrStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_PwrDrSwingActrStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_PwrDrErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_PwrDrAntiPinchStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_float(
        stream, &sample->PDIO_FL_PwrDrAngleSpeed)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_InsdOpnClsSwStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_OtsdOpnClsSwStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_SleepReady)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_WakeupRequest)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_CinchingStatus)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PDIO_FL_ActiveHoldingState)) {
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
dds_Cabin_Door_PDIO_FL_tPlugin_create_sample(
    struct DDS_TypePlugin *plugin,
    void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) dds_Cabin_Door_PDIO_FL_t_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
dds_Cabin_Door_PDIO_FL_tPlugin_delete_sample(
    struct DDS_TypePlugin *plugin,
    void *sample)
{
    UNUSED_ARG(plugin);

    #ifndef RTI_CERT
    /* dds_Cabin_Door_PDIO_FL_t_delete() is a void function
    * which expects (sample != NULL). Since
    * dds_Cabin_Door_PDIO_FL_tPlugin_delete_sample
    * is an internal function, sample is assumed to be a valid pointer
    */
    dds_Cabin_Door_PDIO_FL_t_delete((dds_Cabin_Door_PDIO_FL_t *) sample);
    #endif

    return RTI_TRUE;
}
#endif

RTI_BOOL
dds_Cabin_Door_PDIO_FL_tPlugin_copy_sample(
    struct DDS_TypePlugin *plugin,
    void *dst,
    const void *src)
{
    UNUSED_ARG(plugin);

    return dds_Cabin_Door_PDIO_FL_t_copy(
        (dds_Cabin_Door_PDIO_FL_t*)dst,
        (const dds_Cabin_Door_PDIO_FL_t*)src);
}
/* --------------------------------------------------------------------------
*  Type dds_Cabin_Door_PDIO_FL_t Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation dds_Cabin_Door_PDIO_FL_tEncapsulationKind[] =
{
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_Cabin_Door_PDIO_FL_tTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return dds_Cabin_Door_PDIO_FL_t_initialize((dds_Cabin_Door_PDIO_FL_t*)buffer);
}

RTI_PRIVATE RTI_UINT32
dds_Cabin_Door_PDIO_FL_t_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);
    return sizeof(struct dds_Cabin_Door_PDIO_FL_t);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_Cabin_Door_PDIO_FL_t_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!dds_Cabin_Door_PDIO_FL_tPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

#ifndef RTI_CERT
MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_Cabin_Door_PDIO_FL_t_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!dds_Cabin_Door_PDIO_FL_tPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}
#endif

RTI_PRIVATE RTI_UINT32
dds_Cabin_Door_PDIO_FL_tCdrPlugin_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    struct DDS_TypeEncapsulationPlugin *ep,
    RTI_UINT32 current_alignment)
{
    UNUSED_ARG(ep);

    return dds_Cabin_Door_PDIO_FL_t_get_serialized_sample_size(plugin,
    current_alignment);
}

RTI_PRIVATE struct DDS_TypeEncapsulationPlugin*
dds_Cabin_Door_PDIO_FL_tCdrPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos,
struct DDS_TypeMemoryPlugin *mp)
{
    RTI_UINT32 size =
    dds_Cabin_Door_PDIO_FL_t_get_serialized_sample_size(tp,0);

    return DDS_TypePluginDefaultCdr_create(tp,participant,dp_qos,
    endpoint_mode,endpoint,qos,mp,size);
}

RTI_PRIVATE void
dds_Cabin_Door_PDIO_FL_tCdrPlugin_delete(struct DDS_TypePlugin *p,
struct DDS_TypeEncapsulationPlugin *ep)
{
    UNUSED_ARG(p);
    UNUSED_ARG(ep);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
dds_Cabin_Door_PDIO_FL_tHeapPlugin_create(
    struct DDS_TypePlugin *tp,
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos)
{
    return DDS_TypePluginDefaultHeap_create(tp,participant,dp_qos,
    endpoint_mode,endpoint,qos,
    dds_Cabin_Door_PDIO_FL_t_cdr_initialize,
    #ifndef RTI_CERT
    dds_Cabin_Door_PDIO_FL_t_cdr_finalize);
    #else
    NULL);
    #endif

}

RTI_PRIVATE void
dds_Cabin_Door_PDIO_FL_tHeapPlugin_delete(struct DDS_TypePlugin *p,
struct DDS_TypeMemoryPlugin *mp)
{
    UNUSED_ARG(p);
    UNUSED_ARG(mp);
}

RTI_PRIVATE struct DDS_TypeEncapsulationI dds_Cabin_Door_PDIO_FL_t_fv_CdrPluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    dds_Cabin_Door_PDIO_FL_tEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    DDS_TypePluginDefaultCdr_get_buffer,
    DDS_TypePluginDefaultCdr_return_buffer,
    DDS_TypePluginDefaultCdr_get_sample,
    DDS_TypePluginDefaultCdr_return_sample,
    dds_Cabin_Door_PDIO_FL_t_cdr_serialize,
    dds_Cabin_Door_PDIO_FL_t_cdr_deserialize,
    dds_Cabin_Door_PDIO_FL_tCdrPlugin_get_serialized_sample_size,
    dds_Cabin_Door_PDIO_FL_tCdrPlugin_create,
    dds_Cabin_Door_PDIO_FL_tCdrPlugin_delete
};

RTI_PRIVATE struct DDS_TypeMemoryI dds_Cabin_Door_PDIO_FL_t_fv_HeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    dds_Cabin_Door_PDIO_FL_tPlugin_create_sample,
    #ifndef RTI_CERT
    dds_Cabin_Door_PDIO_FL_tPlugin_delete_sample,
    #else
    NULL,
    #endif
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    dds_Cabin_Door_PDIO_FL_tHeapPlugin_create,
    dds_Cabin_Door_PDIO_FL_tHeapPlugin_delete
};

RTI_PRIVATE DDS_Boolean
dds_Cabin_Door_PDIO_FL_t_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    RTI_UINT32 serialized_size;
    UNUSED_ARG(type_impl);

    serialized_size = dds_Cabin_Door_PDIO_FL_t_get_serialized_sample_size(NULL, 0);
    if (serialized_size == 0)
    {
        return DDS_BOOLEAN_FALSE;
    }

    return DDS_BOOLEAN_TRUE;
}

RTI_PRIVATE struct DDS_TypeEncapsulationI *dds_Cabin_Door_PDIO_FL_t_fv_WirePlugins[] =
{
    &dds_Cabin_Door_PDIO_FL_t_fv_CdrPluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *dds_Cabin_Door_PDIO_FL_t_fv_MemoryPlugins[] =
{
    &dds_Cabin_Door_PDIO_FL_t_fv_HeapPluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
dds_Cabin_Door_PDIO_FL_tTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);

RTI_PRIVATE RTI_BOOL
dds_Cabin_Door_PDIO_FL_tTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI dds_Cabin_Door_PDIO_FL_t_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    dds_Cabin_Door_PDIO_FL_t_get_user_sample_size,
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    dds_Cabin_Door_PDIO_FL_tPlugin_copy_sample,

    dds_Cabin_Door_PDIO_FL_tTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    dds_Cabin_Door_PDIO_FL_t_fv_MemoryPlugins,
    dds_Cabin_Door_PDIO_FL_t_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    NULL, NULL, NULL, NULL,  /* endpoint wrappers not used in C */
    dds_Cabin_Door_PDIO_FL_tTypePlugin_create_plugin,
    dds_Cabin_Door_PDIO_FL_tTypePlugin_delete_plugin,
    dds_Cabin_Door_PDIO_FL_t_on_type_registered,
    NULL
    DDS_TypePluginI_XTYPES_INITIALIZER
};

/* --------------------------------------------------------------------------
*  Type dds_Cabin_Door_PDIO_FL_t Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
dds_Cabin_Door_PDIO_FL_tTypePlugin_get(void)
{
    return &dds_Cabin_Door_PDIO_FL_t_fv_TypePluginI;
}

RTI_PRIVATE struct DDS_TypePlugin*
dds_Cabin_Door_PDIO_FL_tTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&dds_Cabin_Door_PDIO_FL_t_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
dds_Cabin_Door_PDIO_FL_tTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
dds_Cabin_Door_PDIO_FL_tWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &dds_Cabin_Door_PDIO_FL_t_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
dds_Cabin_Door_PDIO_FL_tReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &dds_Cabin_Door_PDIO_FL_t_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
dds_Cabin_Door_PDIO_FL_tTypePlugin_get_default_type_name(void)
{
    return dds_Cabin_Door_PDIO_FL_tTYPENAME;
}

NDDS_TypePluginKeyKind
dds_Cabin_Door_PDIO_FL_tI_get_key_kind(void)
{
    return dds_Cabin_Door_PDIO_FL_t_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

RTI_UINT32
dds_Cabin_Seat_PSUIO_DRV_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment)
{
    RTI_UINT32 initial_alignment = current_alignment;

    UNUSED_ARG(plugin);

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    return  current_alignment - initial_alignment;
}
RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_t_cdr_serialize(struct DDS_TypePlugin *plugin,
struct CDR_Stream_t *stream,
const void *void_sample,
DDS_InstanceHandle_t *destination)
{
    dds_Cabin_Seat_PSUIO_DRV_t *sample = (dds_Cabin_Seat_PSUIO_DRV_t *)void_sample;

    UNUSED_ARG(plugin);
    UNUSED_ARG(destination);

    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Drive_Slide_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Drive_Recline_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Drive_Height_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Drive_Tilt_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Drive_RelaxTilt_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Drive_Legrest_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Seat_MotorIntegratedMove_FeedbackInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Slide_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Recline_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Tilt_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_RelaxTilt_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Height_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Legrest_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Slide_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Recline_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Tilt_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_RelaxTilt_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Height_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Legrest_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Slide_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Recline_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Tilt_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_RlxTilt_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Height_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Legrest_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_UnitAppliedOption)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_AllSeat_Motor_FailState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Slide_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Recline_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Tilt_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_RelaxTilt_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Height_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Legrest_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Slide_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Recline_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Tilt_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_RelaxTilt_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Height_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Legrest_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Slide_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Recline_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Tilt_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_RelaxTilt_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Height_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Legrest_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Seat_EasyAccess_Option)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Slide_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Slide_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Recline_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Recline_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Tilt_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Tilt_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_RlxTilt_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_RlxTilt_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Height_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Height_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Legrest_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_Legrest_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StSldFwdMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StSldBwdMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StRclFwdMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StRclBwdMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StTltUpMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StTltDnMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StRlxTltUpMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StRlxTltDnMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StHgtUpMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StHgtDnMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StLegUpMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StLegDnMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StRlxModeBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DPSS_StRlxReturnBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_PSU_Slide_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_PSU_Recline_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_PSU_Tilt_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_PSU_RlxTilt_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_PSU_Height_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Drive_PSU_Legrest_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PSUIO_DRV_SleepReady)) {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source)
{
    dds_Cabin_Seat_PSUIO_DRV_t *sample = (dds_Cabin_Seat_PSUIO_DRV_t*)void_sample;

    UNUSED_ARG(plugin);
    UNUSED_ARG(source);

    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Drive_Slide_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Drive_Recline_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Drive_Height_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Drive_Tilt_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Drive_RelaxTilt_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Drive_Legrest_CurrentPosition)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Seat_MotorIntegratedMove_FeedbackInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Slide_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Recline_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Tilt_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_RelaxTilt_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Height_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Legrest_VirtualLimitReach_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Slide_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Recline_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Tilt_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_RelaxTilt_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Height_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Legrest_Sensor_ErrorState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Slide_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Recline_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Tilt_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_RlxTilt_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Height_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Legrest_EndLimit_ReachState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_UnitAppliedOption)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_AllSeat_Motor_FailState)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Slide_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Recline_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Tilt_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_RelaxTilt_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Height_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Legrest_MotorMove_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Slide_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Recline_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Tilt_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_RelaxTilt_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Height_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Legrest_MotorMove_StateInitial)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Slide_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Recline_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Tilt_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_RelaxTilt_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Height_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Legrest_MotorVirtualLimitSet_State)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Seat_EasyAccess_Option)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Slide_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Slide_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Recline_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Recline_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Tilt_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Tilt_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_RlxTilt_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_RlxTilt_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Height_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Height_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Legrest_ForwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_Legrest_BackwardMotor_Output)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StSldFwdMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StSldBwdMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StRclFwdMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StRclBwdMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StTltUpMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StTltDnMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StRlxTltUpMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StRlxTltDnMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StHgtUpMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StHgtDnMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StLegUpMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StLegDnMvBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StRlxModeBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DPSS_StRlxReturnBtn_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_PSU_Slide_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_PSU_Recline_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_PSU_Tilt_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_PSU_RlxTilt_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_PSU_Height_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Drive_PSU_Legrest_Fail_State_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PSUIO_DRV_SleepReady)) {
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_tPlugin_create_sample(
    struct DDS_TypePlugin *plugin,
    void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) dds_Cabin_Seat_PSUIO_DRV_t_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_tPlugin_delete_sample(
    struct DDS_TypePlugin *plugin,
    void *sample)
{
    UNUSED_ARG(plugin);

    #ifndef RTI_CERT
    /* dds_Cabin_Seat_PSUIO_DRV_t_delete() is a void function
    * which expects (sample != NULL). Since
    * dds_Cabin_Seat_PSUIO_DRV_tPlugin_delete_sample
    * is an internal function, sample is assumed to be a valid pointer
    */
    dds_Cabin_Seat_PSUIO_DRV_t_delete((dds_Cabin_Seat_PSUIO_DRV_t *) sample);
    #endif

    return RTI_TRUE;
}
#endif

RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_tPlugin_copy_sample(
    struct DDS_TypePlugin *plugin,
    void *dst,
    const void *src)
{
    UNUSED_ARG(plugin);

    return dds_Cabin_Seat_PSUIO_DRV_t_copy(
        (dds_Cabin_Seat_PSUIO_DRV_t*)dst,
        (const dds_Cabin_Seat_PSUIO_DRV_t*)src);
}
/* --------------------------------------------------------------------------
*  Type dds_Cabin_Seat_PSUIO_DRV_t Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation dds_Cabin_Seat_PSUIO_DRV_tEncapsulationKind[] =
{
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return dds_Cabin_Seat_PSUIO_DRV_t_initialize((dds_Cabin_Seat_PSUIO_DRV_t*)buffer);
}

RTI_PRIVATE RTI_UINT32
dds_Cabin_Seat_PSUIO_DRV_t_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);
    return sizeof(struct dds_Cabin_Seat_PSUIO_DRV_t);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_t_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!dds_Cabin_Seat_PSUIO_DRV_tPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

#ifndef RTI_CERT
MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_t_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!dds_Cabin_Seat_PSUIO_DRV_tPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}
#endif

RTI_PRIVATE RTI_UINT32
dds_Cabin_Seat_PSUIO_DRV_tCdrPlugin_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    struct DDS_TypeEncapsulationPlugin *ep,
    RTI_UINT32 current_alignment)
{
    UNUSED_ARG(ep);

    return dds_Cabin_Seat_PSUIO_DRV_t_get_serialized_sample_size(plugin,
    current_alignment);
}

RTI_PRIVATE struct DDS_TypeEncapsulationPlugin*
dds_Cabin_Seat_PSUIO_DRV_tCdrPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos,
struct DDS_TypeMemoryPlugin *mp)
{
    RTI_UINT32 size =
    dds_Cabin_Seat_PSUIO_DRV_t_get_serialized_sample_size(tp,0);

    return DDS_TypePluginDefaultCdr_create(tp,participant,dp_qos,
    endpoint_mode,endpoint,qos,mp,size);
}

RTI_PRIVATE void
dds_Cabin_Seat_PSUIO_DRV_tCdrPlugin_delete(struct DDS_TypePlugin *p,
struct DDS_TypeEncapsulationPlugin *ep)
{
    UNUSED_ARG(p);
    UNUSED_ARG(ep);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
dds_Cabin_Seat_PSUIO_DRV_tHeapPlugin_create(
    struct DDS_TypePlugin *tp,
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos)
{
    return DDS_TypePluginDefaultHeap_create(tp,participant,dp_qos,
    endpoint_mode,endpoint,qos,
    dds_Cabin_Seat_PSUIO_DRV_t_cdr_initialize,
    #ifndef RTI_CERT
    dds_Cabin_Seat_PSUIO_DRV_t_cdr_finalize);
    #else
    NULL);
    #endif

}

RTI_PRIVATE void
dds_Cabin_Seat_PSUIO_DRV_tHeapPlugin_delete(struct DDS_TypePlugin *p,
struct DDS_TypeMemoryPlugin *mp)
{
    UNUSED_ARG(p);
    UNUSED_ARG(mp);
}

RTI_PRIVATE struct DDS_TypeEncapsulationI dds_Cabin_Seat_PSUIO_DRV_t_fv_CdrPluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    dds_Cabin_Seat_PSUIO_DRV_tEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    DDS_TypePluginDefaultCdr_get_buffer,
    DDS_TypePluginDefaultCdr_return_buffer,
    DDS_TypePluginDefaultCdr_get_sample,
    DDS_TypePluginDefaultCdr_return_sample,
    dds_Cabin_Seat_PSUIO_DRV_t_cdr_serialize,
    dds_Cabin_Seat_PSUIO_DRV_t_cdr_deserialize,
    dds_Cabin_Seat_PSUIO_DRV_tCdrPlugin_get_serialized_sample_size,
    dds_Cabin_Seat_PSUIO_DRV_tCdrPlugin_create,
    dds_Cabin_Seat_PSUIO_DRV_tCdrPlugin_delete
};

RTI_PRIVATE struct DDS_TypeMemoryI dds_Cabin_Seat_PSUIO_DRV_t_fv_HeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    dds_Cabin_Seat_PSUIO_DRV_tPlugin_create_sample,
    #ifndef RTI_CERT
    dds_Cabin_Seat_PSUIO_DRV_tPlugin_delete_sample,
    #else
    NULL,
    #endif
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    dds_Cabin_Seat_PSUIO_DRV_tHeapPlugin_create,
    dds_Cabin_Seat_PSUIO_DRV_tHeapPlugin_delete
};

RTI_PRIVATE DDS_Boolean
dds_Cabin_Seat_PSUIO_DRV_t_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    RTI_UINT32 serialized_size;
    UNUSED_ARG(type_impl);

    serialized_size = dds_Cabin_Seat_PSUIO_DRV_t_get_serialized_sample_size(NULL, 0);
    if (serialized_size == 0)
    {
        return DDS_BOOLEAN_FALSE;
    }

    return DDS_BOOLEAN_TRUE;
}

RTI_PRIVATE struct DDS_TypeEncapsulationI *dds_Cabin_Seat_PSUIO_DRV_t_fv_WirePlugins[] =
{
    &dds_Cabin_Seat_PSUIO_DRV_t_fv_CdrPluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *dds_Cabin_Seat_PSUIO_DRV_t_fv_MemoryPlugins[] =
{
    &dds_Cabin_Seat_PSUIO_DRV_t_fv_HeapPluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);

RTI_PRIVATE RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI dds_Cabin_Seat_PSUIO_DRV_t_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    dds_Cabin_Seat_PSUIO_DRV_t_get_user_sample_size,
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    dds_Cabin_Seat_PSUIO_DRV_tPlugin_copy_sample,

    dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    dds_Cabin_Seat_PSUIO_DRV_t_fv_MemoryPlugins,
    dds_Cabin_Seat_PSUIO_DRV_t_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    NULL, NULL, NULL, NULL,  /* endpoint wrappers not used in C */
    dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_create_plugin,
    dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_delete_plugin,
    dds_Cabin_Seat_PSUIO_DRV_t_on_type_registered,
    NULL
    DDS_TypePluginI_XTYPES_INITIALIZER
};

/* --------------------------------------------------------------------------
*  Type dds_Cabin_Seat_PSUIO_DRV_t Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_get(void)
{
    return &dds_Cabin_Seat_PSUIO_DRV_t_fv_TypePluginI;
}

RTI_PRIVATE struct DDS_TypePlugin*
dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&dds_Cabin_Seat_PSUIO_DRV_t_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
dds_Cabin_Seat_PSUIO_DRV_tWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &dds_Cabin_Seat_PSUIO_DRV_t_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
dds_Cabin_Seat_PSUIO_DRV_tReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &dds_Cabin_Seat_PSUIO_DRV_t_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_get_default_type_name(void)
{
    return dds_Cabin_Seat_PSUIO_DRV_tTYPENAME;
}

NDDS_TypePluginKeyKind
dds_Cabin_Seat_PSUIO_DRV_tI_get_key_kind(void)
{
    return dds_Cabin_Seat_PSUIO_DRV_t_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

RTI_UINT32
dds_GCS_LEFT_2_PDIO_FL_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment)
{
    RTI_UINT32 initial_alignment = current_alignment;

    UNUSED_ARG(plugin);

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_float(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_float(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_float(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_float(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    return  current_alignment - initial_alignment;
}
RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_t_cdr_serialize(struct DDS_TypePlugin *plugin,
struct CDR_Stream_t *stream,
const void *void_sample,
DDS_InstanceHandle_t *destination)
{
    dds_GCS_LEFT_2_PDIO_FL_t *sample = (dds_GCS_LEFT_2_PDIO_FL_t *)void_sample;

    UNUSED_ARG(plugin);
    UNUSED_ARG(destination);

    if (!CDR_Stream_serialize_octet(
        stream, &sample->PwrDrOpnClsCmd_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PwrDrSnsrStatus_RODS_FL_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_float(
        stream, &sample->PwrDrSnsrStopAngle_RODS_FL_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PwrDrSnsrStopRequest_RODS_FL_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->ACU_CrshActvSta_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->ACU_CrshTyp_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Door_LockUnlockCmd_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->IMU_LatAccelSigSta_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->IMU_LongAccelSigSta_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_float(
        stream, &sample->IMU_LatAccelVal_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_float(
        stream, &sample->IMU_LongAccelVal_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->VehicleSpeedState_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->VCU_GearPosSta_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_float(
        stream, &sample->PwrDrOpnAngVal_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->SleepRequestTo_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->SleepCommandTo_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->VehiclePowerState_PDIO_FL)) {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source)
{
    dds_GCS_LEFT_2_PDIO_FL_t *sample = (dds_GCS_LEFT_2_PDIO_FL_t*)void_sample;

    UNUSED_ARG(plugin);
    UNUSED_ARG(source);

    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PwrDrOpnClsCmd_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PwrDrSnsrStatus_RODS_FL_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_float(
        stream, &sample->PwrDrSnsrStopAngle_RODS_FL_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PwrDrSnsrStopRequest_RODS_FL_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->ACU_CrshActvSta_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->ACU_CrshTyp_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Door_LockUnlockCmd_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->IMU_LatAccelSigSta_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->IMU_LongAccelSigSta_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_float(
        stream, &sample->IMU_LatAccelVal_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_float(
        stream, &sample->IMU_LongAccelVal_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->VehicleSpeedState_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->VCU_GearPosSta_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_float(
        stream, &sample->PwrDrOpnAngVal_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->SleepRequestTo_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->SleepCommandTo_PDIO_FL)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->VehiclePowerState_PDIO_FL)) {
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_tPlugin_create_sample(
    struct DDS_TypePlugin *plugin,
    void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) dds_GCS_LEFT_2_PDIO_FL_t_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_tPlugin_delete_sample(
    struct DDS_TypePlugin *plugin,
    void *sample)
{
    UNUSED_ARG(plugin);

    #ifndef RTI_CERT
    /* dds_GCS_LEFT_2_PDIO_FL_t_delete() is a void function
    * which expects (sample != NULL). Since
    * dds_GCS_LEFT_2_PDIO_FL_tPlugin_delete_sample
    * is an internal function, sample is assumed to be a valid pointer
    */
    dds_GCS_LEFT_2_PDIO_FL_t_delete((dds_GCS_LEFT_2_PDIO_FL_t *) sample);
    #endif

    return RTI_TRUE;
}
#endif

RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_tPlugin_copy_sample(
    struct DDS_TypePlugin *plugin,
    void *dst,
    const void *src)
{
    UNUSED_ARG(plugin);

    return dds_GCS_LEFT_2_PDIO_FL_t_copy(
        (dds_GCS_LEFT_2_PDIO_FL_t*)dst,
        (const dds_GCS_LEFT_2_PDIO_FL_t*)src);
}
/* --------------------------------------------------------------------------
*  Type dds_GCS_LEFT_2_PDIO_FL_t Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation dds_GCS_LEFT_2_PDIO_FL_tEncapsulationKind[] =
{
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return dds_GCS_LEFT_2_PDIO_FL_t_initialize((dds_GCS_LEFT_2_PDIO_FL_t*)buffer);
}

RTI_PRIVATE RTI_UINT32
dds_GCS_LEFT_2_PDIO_FL_t_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);
    return sizeof(struct dds_GCS_LEFT_2_PDIO_FL_t);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_t_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!dds_GCS_LEFT_2_PDIO_FL_tPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

#ifndef RTI_CERT
MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_t_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!dds_GCS_LEFT_2_PDIO_FL_tPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}
#endif

RTI_PRIVATE RTI_UINT32
dds_GCS_LEFT_2_PDIO_FL_tCdrPlugin_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    struct DDS_TypeEncapsulationPlugin *ep,
    RTI_UINT32 current_alignment)
{
    UNUSED_ARG(ep);

    return dds_GCS_LEFT_2_PDIO_FL_t_get_serialized_sample_size(plugin,
    current_alignment);
}

RTI_PRIVATE struct DDS_TypeEncapsulationPlugin*
dds_GCS_LEFT_2_PDIO_FL_tCdrPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos,
struct DDS_TypeMemoryPlugin *mp)
{
    RTI_UINT32 size =
    dds_GCS_LEFT_2_PDIO_FL_t_get_serialized_sample_size(tp,0);

    return DDS_TypePluginDefaultCdr_create(tp,participant,dp_qos,
    endpoint_mode,endpoint,qos,mp,size);
}

RTI_PRIVATE void
dds_GCS_LEFT_2_PDIO_FL_tCdrPlugin_delete(struct DDS_TypePlugin *p,
struct DDS_TypeEncapsulationPlugin *ep)
{
    UNUSED_ARG(p);
    UNUSED_ARG(ep);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
dds_GCS_LEFT_2_PDIO_FL_tHeapPlugin_create(
    struct DDS_TypePlugin *tp,
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos)
{
    return DDS_TypePluginDefaultHeap_create(tp,participant,dp_qos,
    endpoint_mode,endpoint,qos,
    dds_GCS_LEFT_2_PDIO_FL_t_cdr_initialize,
    #ifndef RTI_CERT
    dds_GCS_LEFT_2_PDIO_FL_t_cdr_finalize);
    #else
    NULL);
    #endif

}

RTI_PRIVATE void
dds_GCS_LEFT_2_PDIO_FL_tHeapPlugin_delete(struct DDS_TypePlugin *p,
struct DDS_TypeMemoryPlugin *mp)
{
    UNUSED_ARG(p);
    UNUSED_ARG(mp);
}

RTI_PRIVATE struct DDS_TypeEncapsulationI dds_GCS_LEFT_2_PDIO_FL_t_fv_CdrPluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    dds_GCS_LEFT_2_PDIO_FL_tEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    DDS_TypePluginDefaultCdr_get_buffer,
    DDS_TypePluginDefaultCdr_return_buffer,
    DDS_TypePluginDefaultCdr_get_sample,
    DDS_TypePluginDefaultCdr_return_sample,
    dds_GCS_LEFT_2_PDIO_FL_t_cdr_serialize,
    dds_GCS_LEFT_2_PDIO_FL_t_cdr_deserialize,
    dds_GCS_LEFT_2_PDIO_FL_tCdrPlugin_get_serialized_sample_size,
    dds_GCS_LEFT_2_PDIO_FL_tCdrPlugin_create,
    dds_GCS_LEFT_2_PDIO_FL_tCdrPlugin_delete
};

RTI_PRIVATE struct DDS_TypeMemoryI dds_GCS_LEFT_2_PDIO_FL_t_fv_HeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    dds_GCS_LEFT_2_PDIO_FL_tPlugin_create_sample,
    #ifndef RTI_CERT
    dds_GCS_LEFT_2_PDIO_FL_tPlugin_delete_sample,
    #else
    NULL,
    #endif
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    dds_GCS_LEFT_2_PDIO_FL_tHeapPlugin_create,
    dds_GCS_LEFT_2_PDIO_FL_tHeapPlugin_delete
};

RTI_PRIVATE DDS_Boolean
dds_GCS_LEFT_2_PDIO_FL_t_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    RTI_UINT32 serialized_size;
    UNUSED_ARG(type_impl);

    serialized_size = dds_GCS_LEFT_2_PDIO_FL_t_get_serialized_sample_size(NULL, 0);
    if (serialized_size == 0)
    {
        return DDS_BOOLEAN_FALSE;
    }

    return DDS_BOOLEAN_TRUE;
}

RTI_PRIVATE struct DDS_TypeEncapsulationI *dds_GCS_LEFT_2_PDIO_FL_t_fv_WirePlugins[] =
{
    &dds_GCS_LEFT_2_PDIO_FL_t_fv_CdrPluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *dds_GCS_LEFT_2_PDIO_FL_t_fv_MemoryPlugins[] =
{
    &dds_GCS_LEFT_2_PDIO_FL_t_fv_HeapPluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);

RTI_PRIVATE RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI dds_GCS_LEFT_2_PDIO_FL_t_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    dds_GCS_LEFT_2_PDIO_FL_t_get_user_sample_size,
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    dds_GCS_LEFT_2_PDIO_FL_tPlugin_copy_sample,

    dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    dds_GCS_LEFT_2_PDIO_FL_t_fv_MemoryPlugins,
    dds_GCS_LEFT_2_PDIO_FL_t_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    NULL, NULL, NULL, NULL,  /* endpoint wrappers not used in C */
    dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_create_plugin,
    dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_delete_plugin,
    dds_GCS_LEFT_2_PDIO_FL_t_on_type_registered,
    NULL
    DDS_TypePluginI_XTYPES_INITIALIZER
};

/* --------------------------------------------------------------------------
*  Type dds_GCS_LEFT_2_PDIO_FL_t Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_get(void)
{
    return &dds_GCS_LEFT_2_PDIO_FL_t_fv_TypePluginI;
}

RTI_PRIVATE struct DDS_TypePlugin*
dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&dds_GCS_LEFT_2_PDIO_FL_t_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
dds_GCS_LEFT_2_PDIO_FL_tWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &dds_GCS_LEFT_2_PDIO_FL_t_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
dds_GCS_LEFT_2_PDIO_FL_tReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &dds_GCS_LEFT_2_PDIO_FL_t_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_get_default_type_name(void)
{
    return dds_GCS_LEFT_2_PDIO_FL_tTYPENAME;
}

NDDS_TypePluginKeyKind
dds_GCS_LEFT_2_PDIO_FL_tI_get_key_kind(void)
{
    return dds_GCS_LEFT_2_PDIO_FL_t_fv_TypePluginI.key_kind;
}

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

RTI_UINT32
dds_GCS_LEFT_2_PSUIO_DRV_t_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    RTI_UINT32 current_alignment)
{
    RTI_UINT32 initial_alignment = current_alignment;

    UNUSED_ARG(plugin);

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_unsigned_short(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    {
        RTI_UINT32 member_size;
        member_size = CDR_get_max_size_serialized_octet(
            current_alignment);
        /* Check for overflow in member size calculation */
        if (member_size == 0) {
            return 0;
        }
        /* Check for overflow in addition */
        if (current_alignment > (UINT_MAX - member_size)) {
            return 0;
        }
        current_alignment += member_size;
    }

    return  current_alignment - initial_alignment;
}
RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_serialize(struct DDS_TypePlugin *plugin,
struct CDR_Stream_t *stream,
const void *void_sample,
DDS_InstanceHandle_t *destination)
{
    dds_GCS_LEFT_2_PSUIO_DRV_t *sample = (dds_GCS_LEFT_2_PSUIO_DRV_t *)void_sample;

    UNUSED_ARG(plugin);
    UNUSED_ARG(destination);

    if (!CDR_Stream_serialize_octet(
        stream, &sample->PSeat_DrvInitializationPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PSeat_DrvSlideManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PSeat_DrvReclineManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PSeat_DrvTiltManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PSeat_DrvRlxTiltManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PSeat_DrvHeightManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->PSeat_DrvLegrestManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Pseat_DrvAutoCmdTargetPos_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->Pseat_DrvAutoCmdTargetPos_Percentage_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Driver_Recline_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Driver_Slide_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Driver_Tilt_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Driver_RlxTilt_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Driver_Height_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_unsigned_short(
        stream, &sample->Driver_Legrest_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->DriveTypeOption_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->ICU_PowerAutoCutModSta_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->SleepRequestTo_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_serialize_octet(
        stream, &sample->VehicePowerState_PSUIO_DRV)) {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_deserialize(struct DDS_TypePlugin *plugin,
void *void_sample,
struct CDR_Stream_t *stream,
DDS_InstanceHandle_t *source)
{
    dds_GCS_LEFT_2_PSUIO_DRV_t *sample = (dds_GCS_LEFT_2_PSUIO_DRV_t*)void_sample;

    UNUSED_ARG(plugin);
    UNUSED_ARG(source);

    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PSeat_DrvInitializationPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PSeat_DrvSlideManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PSeat_DrvReclineManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PSeat_DrvTiltManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PSeat_DrvRlxTiltManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PSeat_DrvHeightManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->PSeat_DrvLegrestManualPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Pseat_DrvAutoCmdTargetPos_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->Pseat_DrvAutoCmdTargetPos_Percentage_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Driver_Recline_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Driver_Slide_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Driver_Tilt_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Driver_RlxTilt_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Driver_Height_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_unsigned_short(
        stream, &sample->Driver_Legrest_TargetPlayCmd_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->DriveTypeOption_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->ICU_PowerAutoCutModSta_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->SleepRequestTo_PSUIO_DRV)) {
        return RTI_FALSE;
    }
    if (!CDR_Stream_deserialize_octet(
        stream, &sample->VehicePowerState_PSUIO_DRV)) {
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_create_sample(
    struct DDS_TypePlugin *plugin,
    void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) dds_GCS_LEFT_2_PSUIO_DRV_t_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_delete_sample(
    struct DDS_TypePlugin *plugin,
    void *sample)
{
    UNUSED_ARG(plugin);

    #ifndef RTI_CERT
    /* dds_GCS_LEFT_2_PSUIO_DRV_t_delete() is a void function
    * which expects (sample != NULL). Since
    * dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_delete_sample
    * is an internal function, sample is assumed to be a valid pointer
    */
    dds_GCS_LEFT_2_PSUIO_DRV_t_delete((dds_GCS_LEFT_2_PSUIO_DRV_t *) sample);
    #endif

    return RTI_TRUE;
}
#endif

RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_copy_sample(
    struct DDS_TypePlugin *plugin,
    void *dst,
    const void *src)
{
    UNUSED_ARG(plugin);

    return dds_GCS_LEFT_2_PSUIO_DRV_t_copy(
        (dds_GCS_LEFT_2_PSUIO_DRV_t*)dst,
        (const dds_GCS_LEFT_2_PSUIO_DRV_t*)src);
}
/* --------------------------------------------------------------------------
*  Type dds_GCS_LEFT_2_PSUIO_DRV_t Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation dds_GCS_LEFT_2_PSUIO_DRV_tEncapsulationKind[] =
{
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return dds_GCS_LEFT_2_PSUIO_DRV_t_initialize((dds_GCS_LEFT_2_PSUIO_DRV_t*)buffer);
}

RTI_PRIVATE RTI_UINT32
dds_GCS_LEFT_2_PSUIO_DRV_t_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);
    return sizeof(struct dds_GCS_LEFT_2_PSUIO_DRV_t);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

#ifndef RTI_CERT
MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}
#endif

RTI_PRIVATE RTI_UINT32
dds_GCS_LEFT_2_PSUIO_DRV_tCdrPlugin_get_serialized_sample_size(
    struct DDS_TypePlugin *plugin,
    struct DDS_TypeEncapsulationPlugin *ep,
    RTI_UINT32 current_alignment)
{
    UNUSED_ARG(ep);

    return dds_GCS_LEFT_2_PSUIO_DRV_t_get_serialized_sample_size(plugin,
    current_alignment);
}

RTI_PRIVATE struct DDS_TypeEncapsulationPlugin*
dds_GCS_LEFT_2_PSUIO_DRV_tCdrPlugin_create(struct DDS_TypePlugin *tp,
DDS_DomainParticipant *participant,
struct DDS_DomainParticipantQos *dp_qos,
DDS_TypePluginMode_T endpoint_mode,
DDS_TypePluginEndpoint *endpoint,
DDS_TypePluginEndpointQos *qos,
struct DDS_TypeMemoryPlugin *mp)
{
    RTI_UINT32 size =
    dds_GCS_LEFT_2_PSUIO_DRV_t_get_serialized_sample_size(tp,0);

    return DDS_TypePluginDefaultCdr_create(tp,participant,dp_qos,
    endpoint_mode,endpoint,qos,mp,size);
}

RTI_PRIVATE void
dds_GCS_LEFT_2_PSUIO_DRV_tCdrPlugin_delete(struct DDS_TypePlugin *p,
struct DDS_TypeEncapsulationPlugin *ep)
{
    UNUSED_ARG(p);
    UNUSED_ARG(ep);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
dds_GCS_LEFT_2_PSUIO_DRV_tHeapPlugin_create(
    struct DDS_TypePlugin *tp,
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos)
{
    return DDS_TypePluginDefaultHeap_create(tp,participant,dp_qos,
    endpoint_mode,endpoint,qos,
    dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_initialize,
    #ifndef RTI_CERT
    dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_finalize);
    #else
    NULL);
    #endif

}

RTI_PRIVATE void
dds_GCS_LEFT_2_PSUIO_DRV_tHeapPlugin_delete(struct DDS_TypePlugin *p,
struct DDS_TypeMemoryPlugin *mp)
{
    UNUSED_ARG(p);
    UNUSED_ARG(mp);
}

RTI_PRIVATE struct DDS_TypeEncapsulationI dds_GCS_LEFT_2_PSUIO_DRV_t_fv_CdrPluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    dds_GCS_LEFT_2_PSUIO_DRV_tEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    DDS_TypePluginDefaultCdr_get_buffer,
    DDS_TypePluginDefaultCdr_return_buffer,
    DDS_TypePluginDefaultCdr_get_sample,
    DDS_TypePluginDefaultCdr_return_sample,
    dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_serialize,
    dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_deserialize,
    dds_GCS_LEFT_2_PSUIO_DRV_tCdrPlugin_get_serialized_sample_size,
    dds_GCS_LEFT_2_PSUIO_DRV_tCdrPlugin_create,
    dds_GCS_LEFT_2_PSUIO_DRV_tCdrPlugin_delete
};

RTI_PRIVATE struct DDS_TypeMemoryI dds_GCS_LEFT_2_PSUIO_DRV_t_fv_HeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_create_sample,
    #ifndef RTI_CERT
    dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_delete_sample,
    #else
    NULL,
    #endif
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    dds_GCS_LEFT_2_PSUIO_DRV_tHeapPlugin_create,
    dds_GCS_LEFT_2_PSUIO_DRV_tHeapPlugin_delete
};

RTI_PRIVATE DDS_Boolean
dds_GCS_LEFT_2_PSUIO_DRV_t_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    RTI_UINT32 serialized_size;
    UNUSED_ARG(type_impl);

    serialized_size = dds_GCS_LEFT_2_PSUIO_DRV_t_get_serialized_sample_size(NULL, 0);
    if (serialized_size == 0)
    {
        return DDS_BOOLEAN_FALSE;
    }

    return DDS_BOOLEAN_TRUE;
}

RTI_PRIVATE struct DDS_TypeEncapsulationI *dds_GCS_LEFT_2_PSUIO_DRV_t_fv_WirePlugins[] =
{
    &dds_GCS_LEFT_2_PSUIO_DRV_t_fv_CdrPluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *dds_GCS_LEFT_2_PSUIO_DRV_t_fv_MemoryPlugins[] =
{
    &dds_GCS_LEFT_2_PSUIO_DRV_t_fv_HeapPluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypePlugin*
dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);

RTI_PRIVATE RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI dds_GCS_LEFT_2_PSUIO_DRV_t_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    dds_GCS_LEFT_2_PSUIO_DRV_t_get_user_sample_size,
    RTI_MEMORY_TYPE_HEAP,
    NULL,
    dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_copy_sample,

    dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_initialize_sample,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    dds_GCS_LEFT_2_PSUIO_DRV_t_fv_MemoryPlugins,
    dds_GCS_LEFT_2_PSUIO_DRV_t_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    NULL, NULL, NULL, NULL,  /* endpoint wrappers not used in C */
    dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_create_plugin,
    dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_delete_plugin,
    dds_GCS_LEFT_2_PSUIO_DRV_t_on_type_registered,
    NULL
    DDS_TypePluginI_XTYPES_INITIALIZER
};

/* --------------------------------------------------------------------------
*  Type dds_GCS_LEFT_2_PSUIO_DRV_t Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_get(void)
{
    return &dds_GCS_LEFT_2_PSUIO_DRV_t_fv_TypePluginI;
}

RTI_PRIVATE struct DDS_TypePlugin*
dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&dds_GCS_LEFT_2_PSUIO_DRV_t_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
dds_GCS_LEFT_2_PSUIO_DRV_tWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &dds_GCS_LEFT_2_PSUIO_DRV_t_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
dds_GCS_LEFT_2_PSUIO_DRV_tReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &dds_GCS_LEFT_2_PSUIO_DRV_t_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_get_default_type_name(void)
{
    return dds_GCS_LEFT_2_PSUIO_DRV_tTYPENAME;
}

NDDS_TypePluginKeyKind
dds_GCS_LEFT_2_PSUIO_DRV_tI_get_key_kind(void)
{
    return dds_GCS_LEFT_2_PSUIO_DRV_t_fv_TypePluginI.key_kind;
}

