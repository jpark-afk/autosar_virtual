cmake_minimum_required(VERSION 3.16)

project(autosar_virtual C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(RTIMEHOME "$ENV{RTIMEHOME}")
set(RTI_PIL_LIB_DIR "$ENV{RTI_PIL_LIB_DIR}")
set(TRAMPOLINE_HOME "$ENV{TRAMPOLINE_HOME}")
set(GOIL "$ENV{GOIL}")
set(GOIL_TEMPLATES "$ENV{GOIL_TEMPLATES}")

include(${CMAKE_SOURCE_DIR}/platform/rtipsl.cmake)

message(STATUS "RTIMEHOME      = ${RTIMEHOME}")
message(STATUS "TRAMPOLINE_HOME = ${TRAMPOLINE_HOME}")
message(STATUS "GOIL           = ${GOIL}")

# ---------------------------------------------------------------------------
# DDS CDD application discovery
# ---------------------------------------------------------------------------

file(GLOB DDS_CDD_CANDIDATES
    "${CMAKE_SOURCE_DIR}/dds_example/*/autosar_gen/DdsCdd.c"
)

list(LENGTH DDS_CDD_CANDIDATES DDS_CDD_COUNT)

if(NOT DDS_CDD_COUNT EQUAL 1)
    message(FATAL_ERROR
        "Expected exactly one DDS CDD application under dds_example/, "
        "found ${DDS_CDD_COUNT}: ${DDS_CDD_CANDIDATES}"
    )
endif()

list(GET DDS_CDD_CANDIDATES 0 DDS_CDD_MAIN)

get_filename_component(DDS_CDD_AUTOSAR_GEN_DIR "${DDS_CDD_MAIN}" DIRECTORY)
get_filename_component(DDS_CDD_ROOT "${DDS_CDD_AUTOSAR_GEN_DIR}" DIRECTORY)

message(STATUS "DDS CDD root: ${DDS_CDD_ROOT}")



add_executable(autosar_virtual

    ${RTI_PSL_SRC}

    # Trampoline generated OS
    ${CMAKE_SOURCE_DIR}/autosar_virtual/tpl_os.c
    ${CMAKE_SOURCE_DIR}/autosar_virtual/tpl_app_config.c

    # Trampoline OS kernel
    ${TRAMPOLINE_HOME}/os/tpl_os_kernel.c
    ${TRAMPOLINE_HOME}/os/tpl_os_timeobj_kernel.c
    ${TRAMPOLINE_HOME}/os/tpl_os_action.c
    ${TRAMPOLINE_HOME}/os/tpl_os_error.c
    ${TRAMPOLINE_HOME}/os/tpl_os_os_kernel.c
    ${TRAMPOLINE_HOME}/os/tpl_os_os.c
    ${TRAMPOLINE_HOME}/os/tpl_os_interrupt_kernel.c
    ${TRAMPOLINE_HOME}/os/tpl_os_task_kernel.c
    ${TRAMPOLINE_HOME}/os/tpl_os_resource_kernel.c
    ${TRAMPOLINE_HOME}/os/tpl_os_alarm_kernel.c

    # Trampoline POSIX platform
    ${TRAMPOLINE_HOME}/machines/posix/tpl_machine_posix.c
    ${TRAMPOLINE_HOME}/machines/posix/tpl_viper_interface.c
    ${TRAMPOLINE_HOME}/machines/posix/tpl_posix_autosar.c
    ${TRAMPOLINE_HOME}/machines/posix/tpl_posix_irq.c
    ${TRAMPOLINE_HOME}/machines/posix/tpl_posix_context.c
    ${TRAMPOLINE_HOME}/machines/posix/tpl_posixvp_irq_gen.c

    ${TRAMPOLINE_HOME}/machines/posix/tpl_trace.c
    ${TRAMPOLINE_HOME}/os/tpl_os_event_kernel.c

    # Platform-specific adapters
    ${CMAKE_SOURCE_DIR}/platform/autosar/HeapAdapter.c
    ${CMAKE_SOURCE_DIR}/platform/autosar/Det.c
    ${CMAKE_SOURCE_DIR}/platform/autosar/TcpIp.c
    ${CMAKE_SOURCE_DIR}/config/os/task_impl.c
    ${CMAKE_SOURCE_DIR}/platform/autosar/StackMonitor.c
    ${CMAKE_SOURCE_DIR}/platform/autosar/ProcessMemoryMonitor.c

    # Virtual RTE
    ${CMAKE_SOURCE_DIR}/platform/autosar/Rte_DdsCddType.c

    # Generated CDD task implementation
    ${CMAKE_SOURCE_DIR}/platform/autosar/DdsCdd_Task.c

    # Generated Virtual ASWC test runnable
    ${CMAKE_SOURCE_DIR}/platform/autosar/VirtualAswc.c

    # DDS CDD - AUTOSAR generated runnable
    ${DDS_CDD_ROOT}/autosar_gen/DdsCdd.c

    # DDS CDD - AUTOSAR adaptation
    ${DDS_CDD_ROOT}/adaptation/dds_cdd_adapter.c

    # DDS generated types / conversions
    ${DDS_CDD_ROOT}/dds_gen/dds_system_conversions.c
    ${DDS_CDD_ROOT}/dds_gen/dds_system_types.c
    ${DDS_CDD_ROOT}/dds_gen/dds_system_typesPlugin.c
    ${DDS_CDD_ROOT}/dds_gen/dds_system_typesSupport.c

    # DDS implementation
    ${DDS_CDD_ROOT}/dds_impl/dds_impl.c
    ${DDS_CDD_ROOT}/dds_impl/dds_systemAppgen.c

    # Phase2 RTI PSL configuration - temporary
)

target_compile_definitions(autosar_virtual PRIVATE
    OSPSL_OS_DEF_H=rti_me_psl/ospsl/ospsl_os_autosar.h
    RTIME_INCLUDE_AUTOSAR
    RTIME_AUTOSAR_WINCORE
)

target_include_directories(autosar_virtual PRIVATE

    # Virtual AUTOSAR overrides
    ${CMAKE_SOURCE_DIR}/platform/autosar

    # RTI
    ${RTIMEHOME}/include/rti_me
    ${RTIMEHOME}/include/rti_me/autosar
    ${RTIMEHOME}/src/rti_me_psl

    ${TRAMPOLINE_HOME}/autosar   
    ${TRAMPOLINE_HOME}/os
    ${TRAMPOLINE_HOME}/machines/posix
    ${TRAMPOLINE_HOME}/viper
    ${TRAMPOLINE_HOME}/debug

    ${CMAKE_SOURCE_DIR}/autosar_virtual

    ${CMAKE_SOURCE_DIR}/platform/rti

    # Virtual RTE / DDS CDD
    ${DDS_CDD_ROOT}
    ${DDS_CDD_ROOT}/autosar_gen
    ${DDS_CDD_ROOT}/adaptation
    ${DDS_CDD_ROOT}/dds_gen
    ${DDS_CDD_ROOT}/dds_impl

)

target_compile_options(autosar_virtual PRIVATE
    ${RTI_PSL_CFLAGS}
    "SHELL:-include limits.h"
)

target_link_libraries(autosar_virtual PRIVATE
    "-Wl,--start-group"
    ${RTI_PIL_LIB_DIR}/librti_mezd.a
    ${RTI_PIL_LIB_DIR}/librti_me_appgenzd.a
    ${RTI_PIL_LIB_DIR}/librti_me_discdpdezd.a
    ${RTI_PIL_LIB_DIR}/librti_me_discdpsezd.a
    ${RTI_PIL_LIB_DIR}/librti_me_rhsmzd.a
    ${RTI_PIL_LIB_DIR}/librti_me_whsmzd.a
    "-Wl,--end-group"
    rt
    pthread
)

target_link_options(autosar_virtual PRIVATE -rdynamic)

