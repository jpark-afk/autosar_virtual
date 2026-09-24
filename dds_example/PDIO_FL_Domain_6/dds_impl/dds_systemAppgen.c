

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from dds_system.xml using "rtiddsmag."
The rtiddsmag tool is part of the RTI Connext distribution.
For more information, type 'rtiddsmag -help' at a command shell
or consult the RTI Connext manual.
*/

#include "dds_systemAppgen.h"

const char *const parlib_PDIO_FL_Domain_6_initial_peers[1] =
{
    "0@192.168.56.1"
};

const char *const parlib_PDIO_FL_Domain_6_discovery_enabled_transports[1] =
{
    "udpv4://"
};

const char *const parlib_PDIO_FL_Domain_6_transport_enabled_transports[1] =
{
    "udpv4"
};

const char *const parlib_PDIO_FL_Domain_6_user_traffic_enabled_transports[1] =
{
    "udpv4://"
};

const char *const parlib_PSUIO_DRV_Domain_6_initial_peers[1] =
{
    "0@192.168.56.1"
};

const char *const parlib_PSUIO_DRV_Domain_6_discovery_enabled_transports[1] =
{
    "udpv4://"
};

const char *const parlib_PSUIO_DRV_Domain_6_transport_enabled_transports[1] =
{
    "udpv4"
};

const char *const parlib_PSUIO_DRV_Domain_6_user_traffic_enabled_transports[1] =
{
    "udpv4://"
};

const char *const parlib_GCS_LEFT_2_Domain_6_initial_peers[2] =
{
    "0@192.168.56.105",
    "0@192.168.56.106"
};

const char *const parlib_GCS_LEFT_2_Domain_6_discovery_enabled_transports[1] =
{
    "udpv4://"
};

const char *const parlib_GCS_LEFT_2_Domain_6_transport_enabled_transports[1] =
{
    "udpv4"
};

const char *const parlib_GCS_LEFT_2_Domain_6_user_traffic_enabled_transports[1] =
{
    "udpv4://"
};

const char *const RTI_APP_GEN___udpv4__parlib_PDIO_FL_Domain_6_udpv4_allow_interface[1] =
{
    "enp0s8"
};

const struct UDP_InterfaceTableEntry RTI_APP_GEN___udpv4__parlib_PDIO_FL_Domain_6_udpv4_interface_table[1] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=563, columnNumber=24 */
    RTI_APP_GEN___udpv4__parlib_PDIO_FL_Domain_6_udpv4_interface_table1
};

const char *const RTI_APP_GEN___udpv4__parlib_PSUIO_DRV_Domain_6_udpv4_allow_interface[1] =
{
    "enp0s8"
};

const struct UDP_InterfaceTableEntry RTI_APP_GEN___udpv4__parlib_PSUIO_DRV_Domain_6_udpv4_interface_table[1] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=490, columnNumber=24 */
    RTI_APP_GEN___udpv4__parlib_PSUIO_DRV_Domain_6_udpv4_interface_table1
};

const char *const RTI_APP_GEN___udpv4__parlib_GCS_LEFT_2_Domain_6_udpv4_allow_interface[1] =
{
    "Ethernet 2"
};

const struct UDP_InterfaceTableEntry RTI_APP_GEN___udpv4__parlib_GCS_LEFT_2_Domain_6_udpv4_interface_table[1] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=416, columnNumber=24 */
    RTI_APP_GEN___udpv4__parlib_GCS_LEFT_2_Domain_6_udpv4_interface_table1
};

const struct ComponentFactoryUnregisterModel parlib_PDIO_FL_Domain_6_unregister_components[2] =
{
    {
        "_udp", /* NETIO_DEFAULT_UDP_NAME */
        NULL, /* udp struct RT_ComponentFactoryProperty** */
        NULL  /* udp struct RT_ComponentFactoryListener** */
    },
    {
        "_intra", /* NETIO_DEFAULT_INTRA_NAME */
        NULL, /* _intra struct RT_ComponentFactoryProperty** */
        NULL  /* _intra struct RT_ComponentFactoryListener** */
    }
};

const struct DPDE_DiscoveryPluginProperty parlib_PDIO_FL_Domain_6_dpde[1] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=583, columnNumber=27 */
    RTI_APP_GEN___dpde__parlib_PDIO_FL_Domain_6_dpde1
};

const struct UDP_InterfaceFactoryProperty parlib_PDIO_FL_Domain_6_udpv4[1] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=560, columnNumber=18 */
    RTI_APP_GEN___udpv4__parlib_PDIO_FL_Domain_6_udpv4
};

const struct ComponentFactoryRegisterModel parlib_PDIO_FL_Domain_6_register_components[2] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=583, columnNumber=27 */
    {
        "dpde1", /* register_name */
        DPDE_DiscoveryFactory_get_interface, /* register_intf */
        &parlib_PDIO_FL_Domain_6_dpde[0]._parent, /* register_property */
        NULL /* register_listener */
    },
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=560, columnNumber=18 */
    {
        "udpv4", /* register_name */
        UDP_InterfaceFactory_get_interface, /* register_intf */
        &parlib_PDIO_FL_Domain_6_udpv4[0]._parent._parent, /* register_property */
        NULL /* register_listener */
    }
};

const struct APPGEN_TypeRegistrationModel parlib_PDIO_FL_Domain_6_type_registrations[2] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=314, columnNumber=84 */
    {
        "Cabin_Door_PDIO_FL_t", /* registered_type_name */
        dds_Cabin_Door_PDIO_FL_tTypePlugin_get /* get_type_plugin */
    },
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=315, columnNumber=84 */
    {
        "GCS_LEFT_2_PDIO_FL_t", /* registered_type_name */
        dds_GCS_LEFT_2_PDIO_FL_tTypePlugin_get /* get_type_plugin */
    }
};

const struct APPGEN_TopicModel parlib_PDIO_FL_Domain_6_topics[2] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=318, columnNumber=83 */
    {
        "Cabin_Door_PDIO_FL", /* topic_name */
        "Cabin_Door_PDIO_FL_t", /* type_name */
        DDS_TopicQos_INITIALIZER /* topic_qos */
    },
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=319, columnNumber=83 */
    {
        "GCS_LEFT_2_PDIO_FL", /* topic_name */
        "GCS_LEFT_2_PDIO_FL_t", /* type_name */
        DDS_TopicQos_INITIALIZER /* topic_qos */
    }
};

const struct APPGEN_DataWriterModel parlib_PDIO_FL_Domain_6_publisher_P_PDIO_FL_data_writers[1] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=381, columnNumber=86 */
    {
        "Cabin_Door_PDIO_FL_Writer", /* name */
        1UL, /* multiplicity */
        "Cabin_Door_PDIO_FL", /* topic_name */
        RTI_APP_GEN___DW_QOS_parlib_PDIO_FL_Domain_6_P_PDIO_FL_Cabin_Door_PDIO_FL_Writer /* writer_qos */
    }
};

const struct APPGEN_PublisherModel parlib_PDIO_FL_Domain_6_publishers[1] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=380, columnNumber=35 */
    {
        "P_PDIO_FL", /* name */
        1UL, /* multiplicity */
        DDS_PublisherQos_INITIALIZER, /* publisher_qos */
        1UL, /* writer_count */
        parlib_PDIO_FL_Domain_6_publisher_P_PDIO_FL_data_writers /* data_writers */
    }
};

const struct APPGEN_DataReaderModel parlib_PDIO_FL_Domain_6_subscriber_S_PDIO_FL_data_readers[1] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=390, columnNumber=86 */
    {
        "GCS_LEFT_2_PDIO_FL_Reader", /* name */
        1UL, /* multiplicity */
        "GCS_LEFT_2_PDIO_FL", /* topic_name */
        RTI_APP_GEN___DR_QOS_parlib_PDIO_FL_Domain_6_S_PDIO_FL_GCS_LEFT_2_PDIO_FL_Reader /* reader_qos */
    }
};

const struct APPGEN_SubscriberModel parlib_PDIO_FL_Domain_6_subscribers[1] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=389, columnNumber=36 */
    {
        "S_PDIO_FL", /* name */
        1UL, /* multiplicity */
        DDS_SubscriberQos_INITIALIZER, /* subscriber_qos */
        1UL, /* reader_count */
        parlib_PDIO_FL_Domain_6_subscriber_S_PDIO_FL_data_readers /* data_readers */
    }
};

const struct APPGEN_DomainParticipantModel parlib_participants[1] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=379, columnNumber=93 */
    RTI_APP_GEN__DP_parlib_PDIO_FL_Domain_6
};

const struct APPGEN_LibraryModel dds_system_libraries[1] =
{
    /* XML Source Location: file=C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml, lineNumber=322, columnNumber=45 */
    RTI_APP_GEN__LIB_parlib
};

const struct APPGEN_LibraryModelSeq dds_system_libraries_sequence =
        REDA_DEFINE_SEQUENCE_INITIALIZER_W_LOAN(
                dds_system_libraries,
                1,
                1,
                struct APPGEN_LibraryModel);

APPGENDllExport const struct APPGEN_LibraryModelSeq*
        APPGEN_get_library_seq(void)
{
    return &dds_system_libraries_sequence;
}
