set(RTI_PSL_SRC

    # OS PSL
    ${RTIMEHOME}/src/rti_me_psl/ospsl/autosar/autosarHeap.c
    ${RTIMEHOME}/src/rti_me_psl/ospsl/autosar/autosarMutex.c
    ${RTIMEHOME}/src/rti_me_psl/ospsl/autosar/autosarProcess.c
    ${RTIMEHOME}/src/rti_me_psl/ospsl/autosar/autosarSemaphore.c
    ${RTIMEHOME}/src/rti_me_psl/ospsl/autosar/autosarSystem.c
    ${RTIMEHOME}/src/rti_me_psl/ospsl/autosar/autosarThread.c
    ${RTIMEHOME}/src/rti_me_psl/ospsl/autosar/autosarString.c
    ${RTIMEHOME}/src/rti_me_psl/ospsl/autosar/autosarLog.c

    # Common PSL
    ${RTIMEHOME}/src/rti_me_psl/ospsl/common/LogWrapper.c

    # UDP PSL
    #${RTIMEHOME}/src/rti_me_psl/netiopsl/udp/UDPInterface.c
    ${CMAKE_SOURCE_DIR}/platform/rti/UDPInterface_wrapper.c  #wrapper    
    ${RTIMEHOME}/src/rti_me_psl/netiopsl/udp/autosar/autosarSocket.c
)

set(RTI_PSL_CFLAGS
    -DOSPSL_OS_DEF_H=rti_me_psl/ospsl/ospsl_os_autosar.h
    -DRTIME_INCLUDE_AUTOSAR
)

add_compile_options(
    -include ${RTIMEHOME}/include/rti_me/autosar/Compiler_Cfg.h
)
