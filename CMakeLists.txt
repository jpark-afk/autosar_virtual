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
    ${CMAKE_SOURCE_DIR}/config/os/stub.c

    # DDS files
    ${CMAKE_SOURCE_DIR}/platform/rti/RtiPslConfig.c
)

target_compile_definitions(autosar_virtual PRIVATE
    OSPSL_OS_DEF_H=rti_me_psl/ospsl/ospsl_os_autosar.h
    RTIME_INCLUDE_AUTOSAR
    RTIME_AUTOSAR_WINCORE
)

target_include_directories(autosar_virtual PRIVATE

    ${RTIMEHOME}/include/rti_me
    ${RTIMEHOME}/include/rti_me/autosar
    ${RTIMEHOME}/src/rti_me_psl

    ${TRAMPOLINE_HOME}/autosar
    ${CMAKE_SOURCE_DIR}/autosar_virtual

    ${TRAMPOLINE_HOME}/os
    ${TRAMPOLINE_HOME}/machines/posix
    ${TRAMPOLINE_HOME}/viper

    ${CMAKE_SOURCE_DIR}/platform/autosar
    ${TRAMPOLINE_HOME}/debug

    ${CMAKE_SOURCE_DIR}/platform/rti

)

target_compile_options(autosar_virtual PRIVATE
    ${RTI_PSL_CFLAGS}
    "SHELL:-include limits.h"
)

target_link_libraries(autosar_virtual PRIVATE
    ${RTI_PIL_LIB_DIR}/librti_mezd.a
    rt
    pthread
)

