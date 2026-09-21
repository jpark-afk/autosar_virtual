

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from dds_system.xml using "rtiddsmag."
The rtiddsmag tool is part of the RTI Connext distribution.
For more information, type 'rtiddsmag -help' at a command shell
or consult the RTI Connext manual.
*/

#include "../dds_gen/dds_system_typesPlugin.h"
#include "app_gen/app_gen.h"
#include "netio/netio_udp.h"
#include "disc_dpde/disc_dpde_discovery_plugin.h"

/* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=560, columnNumber=18 */
extern const char *const RTI_APP_GEN___udpv4__parlib_PDIO_FL_Domain_6_udpv4_allow_interface[1];
extern const struct UDP_InterfaceTableEntry RTI_APP_GEN___udpv4__parlib_PDIO_FL_Domain_6_udpv4_interface_table[1];

#define RTI_APP_GEN___udpv4__parlib_PDIO_FL_Domain_6_udpv4_interface_table1 \
{ \
    UDP_INTERFACE_INTERFACE_UP_FLAG, /* flags */ \
    0xc0a83869, /* address */ \
    0xffffff00, /* netmask */ \
    "enp0s8" /* ifname */ \
}

/**
* NOTE: Do not add a comma (,) after UDP_NAT_INITIALIZER, it is
* part of the definition based on the RTI_CERT definition.
*/
#define RTI_APP_GEN___udpv4__parlib_PDIO_FL_Domain_6_udpv4 \
{ \
    NETIO_InterfaceFactoryProperty_INITIALIZER, \
    REDA_StringSeq_INITIALIZER_W_LOAN(RTI_APP_GEN___udpv4__parlib_PDIO_FL_Domain_6_udpv4_allow_interface, 1, 1), /* allow_interface */ \
    REDA_StringSeq_INITIALIZER, /* deny_interface */ \
    262144, /* max_send_buffer_size */ \
    262144, /* max_receive_buffer_size */ \
    8192, /* max_message_size */ \
    UDP_MAX_SEND_MESSAGE_SIZE_DEFAULT /* max_send_message_size */ \
    1, /* multicast_ttl */ \
    UDP_NAT_INITIALIZER \
    UDP_InterfaceTableEntrySeq_INITIALIZER_W_LOAN(RTI_APP_GEN___udpv4__parlib_PDIO_FL_Domain_6_udpv4_interface_table, 1, 1), /* if_table */ \
    NULL, /* multicast_interface */ \
    DDS_BOOLEAN_TRUE, /* is_default_interface */ \
    DDS_BOOLEAN_FALSE, /* disable_auto_interface_config */ \
    DDS_BOOLEAN_FALSE, /* multicast_loopback_disabled */ \
    UDP_THREAD_PROPERTY_DEFAULT \
    UDP_INTERFACE_BIND_DEFAULT, /* enable_interface_bind */ \
    DDS_BOOLEAN_FALSE, /* disable_multicast_bind */ \
    DDS_BOOLEAN_FALSE, /* disable_multicast_interface_select */ \
    UDP_TRANSFORMS_INITIALIZER \
    UDP_TRANSPORT_PRIORITY_MAPPING_LOW_DEFAULT, /* transport_priority_mapping_low */ \
    UDP_TRANSPORT_PRIORITY_MAPPING_HIGH_DEFAULT, /* transport_priority_mapping_high */ \
    UDP_TRANSPORT_PRIORITY_MASK_DEFAULT, /* transport_priority_mapping_mask */ \
    UDP_MAX_UNICAST_SEND_SOCKETS_DEFAULT /* max_unicast_send_sockets */ \
}

/* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=583, columnNumber=27 */
#define RTI_APP_GEN___dpde__parlib_PDIO_FL_Domain_6_dpde1 \
{ \
    RT_ComponentFactoryProperty_INITIALIZER, /* _parent */ \
    {   /*participant_liveliness_assert_period */ \
        30L, /* sec */ \
        0L /* nanosec */ \
    }, \
    {   /*participant_liveliness_lease_duration */ \
        100L, /* sec */ \
        0L /* nanosec */ \
    }, \
    2, /* initial_participant_announcements */ \
    {   /*initial_participant_announcement_period */ \
        0L, /* sec */ \
        20000000L /* nanosec */ \
    }, \
    DDS_BOOLEAN_FALSE, /* cache_serialized_samples */ \
    DDS_LENGTH_AUTO, /* max_participant_locators */ \
    4, /* max_locators_per_discovered_participant */ \
    8, /* max_samples_per_builtin_endpoint_reader */ \
    DDS_MAX_UNLIMITED, /* max_samples_per_remote_builtin_endpoint_writer */ \
    DDS_LENGTH_UNLIMITED, /* builtin_writer_max_heartbeat_retries */ \
    {   /*builtin_writer_heartbeat_period */ \
        0L, /* sec */ \
        100000000L /* nanosec */ \
    }, \
    -1L, /* builtin_writer_heartbeats_per_max_samples */ \
    {   /* builtin_endpoint_reader_nack_period */ \
        0L, /* sec */ \
        50000000L /* nanosec */ \
    } \
    DDS_PARTICIPANT_MESSAGE_READER_RELIABILITY_KIND_INITIALIZER \
}

/* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=403, columnNumber=32 */
#define RTI_APP_GEN___DPF_QOS_qoslib_Domain_DefaultParticipantFactoryProfile \
{ \
    {   /* entity_factory */ \
        DDS_BOOLEAN_FALSE /* autoenable_created_entities */ \
    }, \
    DDS_SYSTEM_RESOURCE_LIMITS_QOS_POLICY_DEFAULT \
}

/* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=382, columnNumber=77 */

#define RTI_APP_GEN___DW_QOS_parlib_PDIO_FL_Domain_6_P_PDIO_FL_Cabin_Door_PDIO_FL_Writer \
{ \
    {   /* deadline */ \
        { /* period */ \
            0L, /* sec */ \
            10000000L /* nanosec */ \
        } \
    }, \
    DDS_LIVELINESS_QOS_POLICY_DEFAULT, \
    DDS_HISTORY_QOS_POLICY_DEFAULT, \
    DDS_RESOURCE_LIMITS_QOS_POLICY_DEFAULT, \
    DDS_OWNERSHIP_QOS_POLICY_DEFAULT, \
    DDS_OWNERSHIP_STRENGTH_QOS_POLICY_DEFAULT, \
    DDS_LATENCY_BUDGET_QOS_POLICY_DEFAULT, \
    DDS_DATAWRITER_RELIABILITY_QOS_POLICY_DEFAULT, \
    DDS_DURABILITY_QOS_POLICY_DEFAULT, \
    DDS_DESTINATION_ORDER_QOS_POLICY_DEFAULT, \
    DDS_TRANSPORT_ENCAPSULATION_QOS_POLICY_DEFAULT, \
    DDS_DATA_REPRESENTATION_QOS_POLICY_DEFAULT, \
    {   /* protocol */ \
        9151UL, /* rtps_object_id */ \
        DDS_RTPS_RELIABLE_WRITER_PROTOCOL_DEFAULT, \
        DDS_BOOLEAN_TRUE /* serialize_on_write */ \
    }, \
    DDS_TYPESUPPORT_QOS_POLICY_DEFAULT, \
    DDS_TRANSPORT_QOS_POLICY_DEFAULT, \
    RTI_MANAGEMENT_QOS_POLICY_DEFAULT, \
    {   /* writer_resource_limits */ \
        1L, /* max_remote_readers */ \
        4L, /* max_routes_per_reader */ \
        DDS_SIZE_AUTO, /* writer_loaned_sample_allocation */ \
        DDS_BOOLEAN_FALSE, /* initialize_writer_loaned_sample */ \
        DDS_LENGTH_UNLIMITED /* max_remote_reader_filters */ \
    }, \
    DDS_PUBLISH_MODE_QOS_POLICY_DEFAULT, \
    DDS_USER_DATA_QOS_POLICY_DEFAULT, \
    DDS_PROPERTY_QOS_POLICY_DEFAULT, \
    DDS_DATAWRITERQOS_APPGEN_INITIALIZER \
    DDS_DataWriterTransferModeQosPolicy_INITIALIZER, \
    DDS_TRANSPORT_PRIORITY_QOS_POLICY_DEFAULT \
}

/* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=391, columnNumber=77 */

#define RTI_APP_GEN___DR_QOS_parlib_PDIO_FL_Domain_6_S_PDIO_FL_GCS_LEFT_2_PDIO_FL_Reader \
{ \
    {   /* deadline */ \
        { /* period */ \
            0L, /* sec */ \
            12000000L /* nanosec */ \
        } \
    }, \
    DDS_LIVELINESS_QOS_POLICY_DEFAULT, \
    DDS_HISTORY_QOS_POLICY_DEFAULT, \
    DDS_RESOURCE_LIMITS_QOS_POLICY_DEFAULT, \
    DDS_OWNERSHIP_QOS_POLICY_DEFAULT, \
    DDS_LATENCY_BUDGET_QOS_POLICY_DEFAULT, \
    DDS_DATAREADER_RELIABILITY_QOS_POLICY_DEFAULT, \
    DDS_DURABILITY_QOS_POLICY_DEFAULT, \
    DDS_DESTINATION_ORDER_QOS_POLICY_DEFAULT, \
    DDS_TRANSPORT_ENCAPSULATION_QOS_POLICY_DEFAULT, \
    DDS_DATA_REPRESENTATION_QOS_POLICY_DEFAULT, \
    DDS_TYPESUPPORT_QOS_POLICY_DEFAULT, \
    {   /* protocol */ \
        9152UL, /* rtps_object_id */ \
        DDS_RTPS_RELIABLE_READER_PROTOCOL_DEFAULT \
        , \
        DDS_BOOLEAN_TRUE /* propagate_dispose_of_unregistered_instances */\
    }, \
    DDS_TRANSPORT_QOS_POLICY_DEFAULT, \
    DDS_DATAREADERRESOURCE_LIMITS_QOS_POLICY_DEFAULT, \
    RTI_MANAGEMENT_QOS_POLICY_DEFAULT, \
    DDS_USER_DATA_QOS_POLICY_DEFAULT, \
    DDS_PROPERTY_QOS_POLICY_DEFAULT, \
    DDS_CONTENT_FILTER_QOS_POLICY_DEFAULT, \
    DDS_DATAREADERQOS_APPGEN_INITIALIZER \
    NULL, \
    DDS_TRANSPORT_PRIORITY_QOS_POLICY_DEFAULT \
}

/* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=398, columnNumber=80 */
extern const char *const parlib_PDIO_FL_Domain_6_initial_peers[1];
extern const char *const parlib_PDIO_FL_Domain_6_discovery_enabled_transports[1];
extern const char *const parlib_PDIO_FL_Domain_6_transport_enabled_transports[1];
extern const char *const parlib_PDIO_FL_Domain_6_user_traffic_enabled_transports[1];

#define RTI_APP_GEN___DP_QOS_parlib_PDIO_FL_Domain_6 \
{ \
    DDS_ENTITY_FACTORY_QOS_POLICY_DEFAULT, \
    {   /* discovery */ \
        REDA_StringSeq_INITIALIZER_W_LOAN(parlib_PDIO_FL_Domain_6_initial_peers, 1, 1), /* initial_peers */ \
        REDA_StringSeq_INITIALIZER_W_LOAN(parlib_PDIO_FL_Domain_6_discovery_enabled_transports, 1, 1), /* enabled_transports */ \
        { \
            { { "dpde1" } }, /* RT_ComponentFactoryId_INITIALIZER */ \
            NDDS_Discovery_Property_INITIALIZER \
        }, /* discovery_component */ \
        DDS_BOOLEAN_TRUE, /* accept_unknown_peers */ \
        DDS_BOOLEAN_TRUE, /* enable_participant_discovery_by_name */ \
        DDS_BOOLEAN_FALSE, /* enable_endpoint_discovery_queue */ \
        DDS_DISCOVERY_METATRAFFIC_TRANSPORT_PRIORITY_DEFAULT /* metatraffic_transport_priority */ \
    }, \
    {   /* resource_limits  */ \
        1L, /* local_writer_allocation */ \
        1L, /* local_reader_allocation */ \
        1L, /* local_publisher_allocation */ \
        1L, /* local_subscriber_allocation */ \
        2L, /* local_topic_allocation */ \
        2L, /* local_type_allocation */ \
        2L, /* remote_participant_allocation */ \
        3L, /* remote_writer_allocation */ \
        3L, /* remote_reader_allocation */ \
        32L, /* matching_writer_reader_pair_allocation */ \
        32L, /* matching_reader_writer_pair_allocation */ \
        8L, /* max_receive_ports */ \
        8L, /* max_destination_ports */ \
        65536, /* unbound_data_buffer_size */ \
        500UL, /* shmem_ref_transfer_mode_max_segments */ \
        0L, /* participant_user_data_max_length */ \
        DDS_SIZE_AUTO, /* participant_user_data_max_count */ \
        0L, /* topic_data_max_length */ \
        DDS_SIZE_AUTO, /* topic_data_max_count */ \
        0L, /* publisher_group_data_max_length */ \
        DDS_SIZE_AUTO, /* publisher_group_data_max_count */ \
        0L, /* subscriber_group_data_max_length */ \
        DDS_SIZE_AUTO, /* subscriber_group_data_max_count */ \
        0L, /* writer_user_data_max_length */ \
        DDS_SIZE_AUTO, /* writer_user_data_max_count */ \
        0L, /* reader_user_data_max_length */ \
        DDS_SIZE_AUTO, /* reader_user_data_max_count */ \
        64L, /* max_partitions */ \
        256L, /* max_partition_cumulative_characters */ \
        DDS_LENGTH_UNLIMITED, /* max_partition_string_size */ \
        DDS_LENGTH_UNLIMITED, /* max_partition_string_allocation */ \
        1L, /* participant_property_list_max_length */ \
        32L, /* participant_property_string_max_length */ \
        1L, /* writer_property_list_max_length */ \
        32L, /* writer_property_string_max_length */ \
        0L, /* reader_property_list_max_length */ \
        0L /* reader_property_string_max_length */ \
    }, \
    DDS_ENTITY_NAME_QOS_POLICY_DEFAULT, \
    DDS_WIRE_PROTOCOL_QOS_POLICY_DEFAULT, \
    {   /* transports */ \
        REDA_StringSeq_INITIALIZER_W_LOAN(parlib_PDIO_FL_Domain_6_transport_enabled_transports, 1, 1) /* enabled_transports */ \
    }, \
    {   /* user_traffic */ \
        REDA_StringSeq_INITIALIZER_W_LOAN(parlib_PDIO_FL_Domain_6_user_traffic_enabled_transports, 1, 1) /* enabled_transports */ \
    }, \
    DDS_TRUST_QOS_POLICY_DEFAULT, \
    DDS_PROPERTY_QOS_POLICY_DEFAULT, \
    DDS_USER_DATA_QOS_POLICY_DEFAULT \
    ,DDS_FilterQosPolicy_INITIALIZER \
}

extern const struct DPDE_DiscoveryPluginProperty parlib_PDIO_FL_Domain_6_dpde[1];
extern const struct UDP_InterfaceFactoryProperty parlib_PDIO_FL_Domain_6_udpv4[1];

extern const struct ComponentFactoryUnregisterModel parlib_PDIO_FL_Domain_6_unregister_components[2];
extern const struct ComponentFactoryRegisterModel parlib_PDIO_FL_Domain_6_register_components[2];

#define RTI_APP_GEN__DPF_parlib_PDIO_FL_Domain_6 \
{ \
    2UL, /* unregister_count */ \
    parlib_PDIO_FL_Domain_6_unregister_components, /* unregister_components */ \
    2UL, /* register_count */ \
    parlib_PDIO_FL_Domain_6_register_components, /* register_components */ \
    RTI_APP_GEN___DPF_QOS_qoslib_Domain_DefaultParticipantFactoryProfile /* factory_qos */ \
}

/* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=379, columnNumber=93 */
extern const struct APPGEN_TypeRegistrationModel parlib_PDIO_FL_Domain_6_type_registrations[2];
extern const struct APPGEN_TopicModel parlib_PDIO_FL_Domain_6_topics[2];
extern const struct APPGEN_PublisherModel parlib_PDIO_FL_Domain_6_publishers[1];
extern const struct APPGEN_SubscriberModel parlib_PDIO_FL_Domain_6_subscribers[1];

#define RTI_APP_GEN__DP_parlib_PDIO_FL_Domain_6 \
{ \
    "PDIO_FL_Domain_6", /* name */ \
    RTI_APP_GEN__DPF_parlib_PDIO_FL_Domain_6, /* domain_participant_factory */ \
    RTI_APP_GEN___DP_QOS_parlib_PDIO_FL_Domain_6, /* participant_qos */ \
    6L, /* domain_id */ \
    2UL, /* type_registration_count */ \
    parlib_PDIO_FL_Domain_6_type_registrations, /* type_registrations */ \
    2UL, /* topic_count */ \
    parlib_PDIO_FL_Domain_6_topics, /* topics */ \
    1UL, /* publisher_count */ \
    parlib_PDIO_FL_Domain_6_publishers, /* publishers */ \
    1UL, /* subscriber_count */ \
    parlib_PDIO_FL_Domain_6_subscribers, /* subscribers */ \
    0UL, /* remote_participant_count */ \
    NULL, /* remote_participants */ \
    0UL, /* custom_flow_controller_count */ \
    NULL, /* custom_flow_controllers */ \
    0UL, /* content_filter_registration_count */ \
    NULL /* content_filter_registrations */ \
}

extern const struct APPGEN_DomainParticipantModel parlib_participants[1];

#define RTI_APP_GEN__LIB_parlib \
{ \
    "parlib", /* library_name */ \
    1UL, /* participant_count */ \
    parlib_participants /* participants */ \
}

extern const struct APPGEN_LibraryModel dds_system_libraries[1];
