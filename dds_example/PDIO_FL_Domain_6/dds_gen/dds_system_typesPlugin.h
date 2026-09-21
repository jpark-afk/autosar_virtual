/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from dds_system_types.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef dds_system_typesPlugin_1690667057_h
#define dds_system_typesPlugin_1690667057_h

#include "dds_system_types.h"

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
    #endif

    struct dds_Cabin_Door_PDIO_FL_tTypePlugin;

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Door_PDIO_FL_tTypePlugin_delete(struct DDS_TypePlugin *self);
    #endif

    NDDSUSERDllExport extern struct DDS_TypePlugin*
    dds_Cabin_Door_PDIO_FL_tWriterTypePlugin_create(
        DDS_DomainParticipant *participant,
        struct DDS_DomainParticipantQos *dp_qos,
        DDS_DataWriter *writer,
        struct DDS_DataWriterQos *qos,
        struct DDS_TypePluginProperty *property);

    NDDSUSERDllExport extern struct DDS_TypePlugin*
    dds_Cabin_Door_PDIO_FL_tReaderTypePlugin_create(
        DDS_DomainParticipant *participant,
        struct DDS_DomainParticipantQos *dp_qos,
        DDS_DataReader *reader,
        struct DDS_DataReaderQos *qos,
        struct DDS_TypePluginProperty *property);

    NDDSUSERDllExport extern struct DDS_TypePluginI*
    dds_Cabin_Door_PDIO_FL_tTypePlugin_get(void);
    NDDSUSERDllExport extern const char*
    dds_Cabin_Door_PDIO_FL_tTypePlugin_get_default_type_name(void);
    NDDSUSERDllExport extern NDDS_TypePluginKeyKind
    dds_Cabin_Door_PDIO_FL_tI_get_key_kind(void);
    /* --------------------------------------------------------------------------
    Untyped interfaces to the typed sample management functions
    * -------------------------------------------------------------------------- */
    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Door_PDIO_FL_tPlugin_create_sample(
        struct DDS_TypePlugin *plugin, void **sample);

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Door_PDIO_FL_tPlugin_delete_sample(
        struct DDS_TypePlugin *plugin, void *sample);
    #endif

    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Door_PDIO_FL_tPlugin_copy_sample(
        struct DDS_TypePlugin *plugin, void *dst, const void *src);

    /* --------------------------------------------------------------------------
    (De)Serialize functions:
    * -------------------------------------------------------------------------- */
    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Door_PDIO_FL_t_cdr_serialize(
        struct DDS_TypePlugin *plugin,
        struct CDR_Stream_t *stream,
        const void *void_sample,
        DDS_InstanceHandle_t *destination);

    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Door_PDIO_FL_t_cdr_deserialize(
        struct DDS_TypePlugin *plugin,
        void *void_sample,
        struct CDR_Stream_t *stream,
        DDS_InstanceHandle_t *source);

    NDDSUSERDllExport extern RTI_UINT32
    dds_Cabin_Door_PDIO_FL_t_get_serialized_sample_size(
        struct DDS_TypePlugin *plugin,
        RTI_UINT32 current_alignment);
    /* Unkeyed type key serialization equivalent to sample serialization */
    #define dds_Cabin_Door_PDIO_FL_t_cdr_serialize_key dds_Cabin_Door_PDIO_FL_t_cdr_serialize
    #define dds_Cabin_Door_PDIO_FL_t_cdr_deserialize_key dds_Cabin_Door_PDIO_FL_t_cdr_deserialize
    #define dds_Cabin_Door_PDIO_FL_t_get_serialized_key_size dds_Cabin_Door_PDIO_FL_t_get_serialized_sample_size
    #ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus
extern "C" {
    #endif

    struct dds_Cabin_Seat_PSUIO_DRV_tTypePlugin;

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_delete(struct DDS_TypePlugin *self);
    #endif

    NDDSUSERDllExport extern struct DDS_TypePlugin*
    dds_Cabin_Seat_PSUIO_DRV_tWriterTypePlugin_create(
        DDS_DomainParticipant *participant,
        struct DDS_DomainParticipantQos *dp_qos,
        DDS_DataWriter *writer,
        struct DDS_DataWriterQos *qos,
        struct DDS_TypePluginProperty *property);

    NDDSUSERDllExport extern struct DDS_TypePlugin*
    dds_Cabin_Seat_PSUIO_DRV_tReaderTypePlugin_create(
        DDS_DomainParticipant *participant,
        struct DDS_DomainParticipantQos *dp_qos,
        DDS_DataReader *reader,
        struct DDS_DataReaderQos *qos,
        struct DDS_TypePluginProperty *property);

    NDDSUSERDllExport extern struct DDS_TypePluginI*
    dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_get(void);
    NDDSUSERDllExport extern const char*
    dds_Cabin_Seat_PSUIO_DRV_tTypePlugin_get_default_type_name(void);
    NDDSUSERDllExport extern NDDS_TypePluginKeyKind
    dds_Cabin_Seat_PSUIO_DRV_tI_get_key_kind(void);
    /* --------------------------------------------------------------------------
    Untyped interfaces to the typed sample management functions
    * -------------------------------------------------------------------------- */
    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Seat_PSUIO_DRV_tPlugin_create_sample(
        struct DDS_TypePlugin *plugin, void **sample);

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Seat_PSUIO_DRV_tPlugin_delete_sample(
        struct DDS_TypePlugin *plugin, void *sample);
    #endif

    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Seat_PSUIO_DRV_tPlugin_copy_sample(
        struct DDS_TypePlugin *plugin, void *dst, const void *src);

    /* --------------------------------------------------------------------------
    (De)Serialize functions:
    * -------------------------------------------------------------------------- */
    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Seat_PSUIO_DRV_t_cdr_serialize(
        struct DDS_TypePlugin *plugin,
        struct CDR_Stream_t *stream,
        const void *void_sample,
        DDS_InstanceHandle_t *destination);

    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Seat_PSUIO_DRV_t_cdr_deserialize(
        struct DDS_TypePlugin *plugin,
        void *void_sample,
        struct CDR_Stream_t *stream,
        DDS_InstanceHandle_t *source);

    NDDSUSERDllExport extern RTI_UINT32
    dds_Cabin_Seat_PSUIO_DRV_t_get_serialized_sample_size(
        struct DDS_TypePlugin *plugin,
        RTI_UINT32 current_alignment);
    /* Unkeyed type key serialization equivalent to sample serialization */
    #define dds_Cabin_Seat_PSUIO_DRV_t_cdr_serialize_key dds_Cabin_Seat_PSUIO_DRV_t_cdr_serialize
    #define dds_Cabin_Seat_PSUIO_DRV_t_cdr_deserialize_key dds_Cabin_Seat_PSUIO_DRV_t_cdr_deserialize
    #define dds_Cabin_Seat_PSUIO_DRV_t_get_serialized_key_size dds_Cabin_Seat_PSUIO_DRV_t_get_serialized_sample_size
    #ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus
extern "C" {
    #endif

    struct dds_GCS_LEFT_2_PDIO_FL_tTypePlugin;

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_delete(struct DDS_TypePlugin *self);
    #endif

    NDDSUSERDllExport extern struct DDS_TypePlugin*
    dds_GCS_LEFT_2_PDIO_FL_tWriterTypePlugin_create(
        DDS_DomainParticipant *participant,
        struct DDS_DomainParticipantQos *dp_qos,
        DDS_DataWriter *writer,
        struct DDS_DataWriterQos *qos,
        struct DDS_TypePluginProperty *property);

    NDDSUSERDllExport extern struct DDS_TypePlugin*
    dds_GCS_LEFT_2_PDIO_FL_tReaderTypePlugin_create(
        DDS_DomainParticipant *participant,
        struct DDS_DomainParticipantQos *dp_qos,
        DDS_DataReader *reader,
        struct DDS_DataReaderQos *qos,
        struct DDS_TypePluginProperty *property);

    NDDSUSERDllExport extern struct DDS_TypePluginI*
    dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_get(void);
    NDDSUSERDllExport extern const char*
    dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_get_default_type_name(void);
    NDDSUSERDllExport extern NDDS_TypePluginKeyKind
    dds_GCS_LEFT_2_PDIO_FL_tI_get_key_kind(void);
    /* --------------------------------------------------------------------------
    Untyped interfaces to the typed sample management functions
    * -------------------------------------------------------------------------- */
    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PDIO_FL_tPlugin_create_sample(
        struct DDS_TypePlugin *plugin, void **sample);

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PDIO_FL_tPlugin_delete_sample(
        struct DDS_TypePlugin *plugin, void *sample);
    #endif

    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PDIO_FL_tPlugin_copy_sample(
        struct DDS_TypePlugin *plugin, void *dst, const void *src);

    /* --------------------------------------------------------------------------
    (De)Serialize functions:
    * -------------------------------------------------------------------------- */
    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PDIO_FL_t_cdr_serialize(
        struct DDS_TypePlugin *plugin,
        struct CDR_Stream_t *stream,
        const void *void_sample,
        DDS_InstanceHandle_t *destination);

    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PDIO_FL_t_cdr_deserialize(
        struct DDS_TypePlugin *plugin,
        void *void_sample,
        struct CDR_Stream_t *stream,
        DDS_InstanceHandle_t *source);

    NDDSUSERDllExport extern RTI_UINT32
    dds_GCS_LEFT_2_PDIO_FL_t_get_serialized_sample_size(
        struct DDS_TypePlugin *plugin,
        RTI_UINT32 current_alignment);
    /* Unkeyed type key serialization equivalent to sample serialization */
    #define dds_GCS_LEFT_2_PDIO_FL_t_cdr_serialize_key dds_GCS_LEFT_2_PDIO_FL_t_cdr_serialize
    #define dds_GCS_LEFT_2_PDIO_FL_t_cdr_deserialize_key dds_GCS_LEFT_2_PDIO_FL_t_cdr_deserialize
    #define dds_GCS_LEFT_2_PDIO_FL_t_get_serialized_key_size dds_GCS_LEFT_2_PDIO_FL_t_get_serialized_sample_size
    #ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus
extern "C" {
    #endif

    struct dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin;

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_delete(struct DDS_TypePlugin *self);
    #endif

    NDDSUSERDllExport extern struct DDS_TypePlugin*
    dds_GCS_LEFT_2_PSUIO_DRV_tWriterTypePlugin_create(
        DDS_DomainParticipant *participant,
        struct DDS_DomainParticipantQos *dp_qos,
        DDS_DataWriter *writer,
        struct DDS_DataWriterQos *qos,
        struct DDS_TypePluginProperty *property);

    NDDSUSERDllExport extern struct DDS_TypePlugin*
    dds_GCS_LEFT_2_PSUIO_DRV_tReaderTypePlugin_create(
        DDS_DomainParticipant *participant,
        struct DDS_DomainParticipantQos *dp_qos,
        DDS_DataReader *reader,
        struct DDS_DataReaderQos *qos,
        struct DDS_TypePluginProperty *property);

    NDDSUSERDllExport extern struct DDS_TypePluginI*
    dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_get(void);
    NDDSUSERDllExport extern const char*
    dds_GCS_LEFT_2_PSUIO_DRV_tTypePlugin_get_default_type_name(void);
    NDDSUSERDllExport extern NDDS_TypePluginKeyKind
    dds_GCS_LEFT_2_PSUIO_DRV_tI_get_key_kind(void);
    /* --------------------------------------------------------------------------
    Untyped interfaces to the typed sample management functions
    * -------------------------------------------------------------------------- */
    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_create_sample(
        struct DDS_TypePlugin *plugin, void **sample);

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_delete_sample(
        struct DDS_TypePlugin *plugin, void *sample);
    #endif

    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PSUIO_DRV_tPlugin_copy_sample(
        struct DDS_TypePlugin *plugin, void *dst, const void *src);

    /* --------------------------------------------------------------------------
    (De)Serialize functions:
    * -------------------------------------------------------------------------- */
    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_serialize(
        struct DDS_TypePlugin *plugin,
        struct CDR_Stream_t *stream,
        const void *void_sample,
        DDS_InstanceHandle_t *destination);

    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_deserialize(
        struct DDS_TypePlugin *plugin,
        void *void_sample,
        struct CDR_Stream_t *stream,
        DDS_InstanceHandle_t *source);

    NDDSUSERDllExport extern RTI_UINT32
    dds_GCS_LEFT_2_PSUIO_DRV_t_get_serialized_sample_size(
        struct DDS_TypePlugin *plugin,
        RTI_UINT32 current_alignment);
    /* Unkeyed type key serialization equivalent to sample serialization */
    #define dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_serialize_key dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_serialize
    #define dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_deserialize_key dds_GCS_LEFT_2_PSUIO_DRV_t_cdr_deserialize
    #define dds_GCS_LEFT_2_PSUIO_DRV_t_get_serialized_key_size dds_GCS_LEFT_2_PSUIO_DRV_t_get_serialized_sample_size
    #ifdef __cplusplus
} /* extern "C" */
#endif

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* dds_system_typesPlugin_1690667057_h */

