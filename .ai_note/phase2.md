# Phase 2 — RTI AUTOSAR PSL Integration

## 1. Result

**STATUS: PASS**

Phase 2 successfully integrated RTI Connext DDS Micro AUTOSAR PSL with
Trampoline POSIX AUTOSAR OS on Ubuntu x86_64.

Final verified runtime:

```text
[Virtual AUTOSAR] Starting Trampoline OS
[Virtual AUTOSAR] RTI_Task started
[Virtual AUTOSAR] RTI PSL configuration applied
[Virtual AUTOSAR] OSAPI_System_initialize PASS
[Virtual AUTOSAR] OSAPI_System_finalize PASS
[Virtual AUTOSAR] Phase2 PASS
Exiting virtual platform.
```

The final PASS was reproduced using:

```text
GOIL regeneration
→ clean CMake configure
→ clean build
→ runtime execution
```

RTI proprietary source was restored to its original state before the final
validation.

---

# 2. Architecture

The Virtual AUTOSAR PoC architecture remains:

```text
Application / Runnable
        |
        v
       RTE
        |
        v
     DDS CDD
        |
        v
   RTI DDS PIL
        |
        v
 RTI AUTOSAR PSL
        |
        v
 AUTOSAR OS / TcpIp API
        |
        v
 Trampoline POSIX
        |
        v
 Ubuntu Linux x86_64
```

The important architectural requirement is:

```text
RTI Micro
→ AUTOSAR PSL
→ AUTOSAR APIs
→ Trampoline
→ POSIX/Linux
```

Do NOT replace the AUTOSAR PSL with RTI POSIX PSL.

This project is not intended to implement a general AUTOSAR toolchain.

Out of scope:

```text
Composition tooling
ECU Mapping
Full ECUC
Full RTE Generator
DaVinci-like GUI
QEMU
FreeRTOS
lwIP
ARM target
32-bit target
```

---

# 3. Base Environment

Host:

```text
Ubuntu Server 26.04.1 LTS
Architecture : x86_64
GCC          : 13.4.0
Target       : x86_64-linux-gnu
Binutils     : 2.46
```

RTI:

```text
RTI Connext DDS Micro 4.3.0 ER738
```

Environment:

```bash
RTIMEHOME=$HOME/dds/rti_connext_dds_micro-4.3.0_ER738
RTI_PIL_LIB_DIR=$RTIMEHOME/lib/x86_64leElfgcc13.3.0
RTI_PIL_INCLUDE_DIR=$RTIMEHOME/include
```

PIL library:

```text
librti_mezd.a
```

PIL build combination:

```text
x86_64leElfgcc13.3.0
```

Previously verified:

```text
ELF64
little-endian
x86-64
System V
GCC 13.3.0
static debug library (zd)
```

Host GCC 13.4.0 successfully links and runs with this PIL build.

---

# 4. Environment Setup

Project environment is defined in:

```text
env.sh
```

Important variables:

```bash
export RTIMEHOME="${RTIMEHOME:-$HOME/dds/rti_connext_dds_micro-4.3.0_ER738}"

export RTI_PIL_LIB_DIR="$RTIMEHOME/lib/x86_64leElfgcc13.3.0"
export RTI_PIL_INCLUDE_DIR="$RTIMEHOME/include"

export TRAMPOLINE_HOME="$HOME/autosar_virtual/third_party/trampoline"

export GOIL="$TRAMPOLINE_HOME/goil/makefile-unix/goil"
export GOIL_TEMPLATES="$TRAMPOLINE_HOME/goil/templates"

export VIPER_PATH="$TRAMPOLINE_HOME/viper"
```

Scripts automatically source `env.sh`.

Manual use:

```bash
source ./env.sh
```

---

# 5. Trampoline

Trampoline is maintained as a Git submodule:

```text
third_party/trampoline
```

Validated Phase 1 revision:

```text
ff2870232
```

Correct GOIL target:

```text
posix
```

Do NOT use:

```text
posix/linux
```

GOIL configuration source:

```text
config/os/autosar_virtual.oil
```

---

# 6. Trampoline POSIX 1 ms Patch

Stock Trampoline POSIX ViPER automatic timer:

```c
tpl_viper_start_auto_timer(signal_for_counters,10000);  /* 10 ms */
```

The Virtual AUTOSAR configuration requires a 1 ms SystemCounter tick:

```c
tpl_viper_start_auto_timer(signal_for_counters,1000);   /* 1 ms */
```

Project patch:

```text
patches/trampoline-posix-1ms-systemcounter.patch
```

Patch helper:

```text
apply_patches.sh
```

The Trampoline upstream source itself must NOT be committed as modified.

The patch is applied to the local submodule working tree when preparing the
build.

`apply_patches.sh` is idempotent:

```text
not applied → apply patch
already applied → continue
invalid patch state → fail
```

`generate.sh` automatically executes `apply_patches.sh`.

Therefore normal users do not need to manually apply the patch.

---

# 7. RTI AUTOSAR PSL Source Selection

RTI PSL source selection is maintained in:

```text
platform/rtipsl.cmake
```

AUTOSAR OS PSL:

```text
ospsl/autosar/autosarHeap.c
ospsl/autosar/autosarMutex.c
ospsl/autosar/autosarProcess.c
ospsl/autosar/autosarSemaphore.c
ospsl/autosar/autosarSystem.c
ospsl/autosar/autosarThread.c
ospsl/autosar/autosarString.c
ospsl/autosar/autosarLog.c
```

Common:

```text
ospsl/common/LogWrapper.c
```

UDP PSL:

```text
netiopsl/udp/autosar/autosarSocket.c
```

The project intentionally uses:

```text
ospsl/autosar
```

and NOT:

```text
ospsl/posix
```

UDP transformation support is currently disabled.

`UDPTransform.c` is not required unless `UDP_ENABLE_TRANSFORMS` is explicitly
enabled.

---

# 8. UDPInterface Wrapper

RTI `UDPInterface.c` contains a local identifier named `YES`.

Trampoline also defines:

```c
#define YES 1
```

To avoid modifying RTI proprietary source, the project uses:

```text
platform/rti/UDPInterface_wrapper.c
```

Conceptually:

```c
#include <Os.h>

#ifdef YES
#undef YES
#endif

#include "netiopsl/udp/UDPInterface.c"
```

This wrapper is project-owned.

RTI `UDPInterface.c` remains untouched.

---

# 9. AUTOSAR Compatibility Layer

Project AUTOSAR compatibility code:

```text
platform/autosar/
```

Current files:

```text
Compiler_Cfg.h
Os_Types.h
Det.c
HeapAdapter.c
TcpIp.h
TcpIp.c
```

## Det

A minimal `Det_ReportError()` implementation is provided.

Current PoC behavior:

```text
return E_OK
```

## Heap

RTI PIL requires:

```text
OSAPI_Heap_realloc
```

The Linux adapter implements this using standard `realloc()`.

RTI uses a 32-bit `RTI_SIZE_T` for this build.

---

# 10. TcpIp Adapter

RTI AUTOSAR socket PSL expects AUTOSAR TcpIp APIs.

The project currently implements:

```text
TcpIp_GetIpAddr
TcpIp_Bind
TcpIp_Close
TcpIp_UdpTransmit
```

using Linux socket APIs.

Current Phase 2 mapping:

```text
LocalAddrId : 0
IPv4        : 192.168.56.105
Netmask     : /24
```

Current compatibility constants include:

```text
TCPIP_AF_INET          = 2
TCPIP_IPPROTO_UDP      = 17
TCPIP_LOCALADDRID_ANY  = 0xFF
TCPIP_PORT_ANY         = 0
```

RTI's socket-owner callback creates a native Linux UDP socket:

```c
socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
```

The returned Linux file descriptor is used as the current PoC
`TcpIp_SocketIdType`.

The IP/interface mapping is currently hardcoded.

Making it configurable is deferred until needed.

---

# 11. OIL Configuration

Primary configuration:

```text
config/os/autosar_virtual.oil
```

RTI execution task:

```text
RTI_Task
```

`RTI_Task` is AUTOSTART.

The task is configured to access:

```text
RTI_GlobalResource
```

Resources are intentionally ordered:

```text
DummyResource       ID 0
RTI_GlobalResource  ID 1
```

RTI must not use Resource ID 0.

Alarm ordering:

```text
DummyAlarm          ID 0
RTI_SemaphoreAlarm  ID 1
```

Events:

```text
RTI_GiveEvent       mask 1
RTI_TimeoutEvent    mask 2
```

The event/alarm definitions are retained for future semaphore/thread
configuration even though the current Phase 2 PSL configuration does not use
thread semaphores.

---

# 12. RTI System Property Configuration

RTI AUTOSAR configuration is implemented in:

```text
platform/rti/RtiPslConfig.c
platform/rti/RtiPslConfig.h
```

The correct RTI configuration path is:

```text
OSPSL_AutosarSystem_get_property()
        |
        v
modify system_property
        |
        v
OSPSL_AutosarSystem_set_property()
```

Do NOT directly replace only:

```c
*OSAPI_System_gv_PortProperty
```

The official setter also propagates the parent RTI core system property through:

```c
OSAPI_System_set_property(&property->_parent.property);
```

This keeps RTI core and AUTOSAR PSL properties synchronized.

---

# 13. Final Phase 2 RTI Configuration

Current working configuration:

```text
timer_resolution_ms          = 10

number_of_heap_areas         = 1
heap size                    = 1 MiB
enable_thread_safe_heap      = TRUE

sync_type                    = OSAPI_AUTOSAR_SYNCKIND_RESOURCES
mutex_resource_id            = RTI_GlobalResource

semaphore_max_count          = 0
first_give_event             = 0
first_timeout_event          = 0
first_alarm                  = 0

use_socket_owner             = TRUE
max_receive_sockets          = 1

number_of_rcv_buffers        = 0
rcv_buffer_size              = 0

get_socket                   = RtiPsl_get_socket
send_data                    = NULL

max_local_addr_id            = 0
send_local_addr_id           = 0

use_udp_thread               = FALSE
dds_rxindication             = NULL
```

RTI core property:

```text
max_user_blocking_threads = 0
```

This value is important for the current Phase 2 configuration.

---

# 14. Important Configuration Dependency

RTI documents `max_user_blocking_threads` as the size of the thread semaphore
pool.

One semaphore is required per receive thread.

RTI's generic default is:

```text
max_user_blocking_threads = 32
```

However Phase 2 intentionally uses:

```text
use_udp_thread       = FALSE
semaphore_max_count  = 0
```

Therefore the matching RTI core configuration is:

```text
max_user_blocking_threads = 0
```

Final consistent Phase 2 configuration:

```text
max_user_blocking_threads = 0
semaphore_max_count       = 0
use_udp_thread            = FALSE
```

Without this alignment, RTI core initialization attempts to allocate thread
semaphores that the AUTOSAR PSL configuration does not provide.

The final implementation sets:

```c
system_property._parent.property.max_user_blocking_threads = 0;
```

This configuration was verified by successful:

```text
OSAPI_System_initialize()
OSAPI_System_finalize()
```

When receive threads are enabled later, these properties must be reconsidered
together.

---

# 15. RTI PIL Linking

The project links:

```text
${RTI_PIL_LIB_DIR}/librti_mezd.a
```

plus:

```text
rt
pthread
```

Do NOT blindly link every RTI library.

`librti_mezd.a` resolved the required RTI core dependencies for the Phase 2
executable.

Project adapters provide platform symbols including:

```text
Det_ReportError
OSAPI_Heap_realloc
TcpIp_Bind
TcpIp_Close
TcpIp_GetIpAddr
TcpIp_UdpTransmit
```

---

# 16. Compiler Configuration

Important definitions:

```text
OSPSL_OS_DEF_H=rti_me_psl/ospsl/ospsl_os_autosar.h
RTIME_INCLUDE_AUTOSAR
RTIME_AUTOSAR_WINCORE
```

Current build also uses:

```text
-include limits.h
```

because RTI headers require standard integer limit macros such as:

```text
SCHAR_MAX
SHRT_MAX
INT_MAX
```

Some compiler abstraction macro redefinition warnings remain because both RTI
and Trampoline provide AUTOSAR-style compiler macros.

These warnings do not prevent Phase 2 operation and cleanup is deferred.

---

# 17. Runtime Lifecycle

Current Phase 2 runtime:

```text
main()
 |
 +--> StartOS(stdAppmode)
        |
        +--> AUTOSTART RTI_Task
               |
               +--> RtiPslConfig_apply()
               |
               +--> OSAPI_System_initialize()
               |
               +--> OSAPI_System_finalize()
               |
               +--> ShutdownOS(E_OK)
```

Expected shutdown:

```text
Exiting virtual platform.
```

`ShutdownOS(E_OK)` cleanly terminates the Trampoline POSIX virtual platform.

---

# 18. Convenience Scripts

The project provides four primary convenience scripts plus the patch helper.

## apply_patches.sh

Applies project-required patches to external dependencies.

Currently:

```text
Trampoline POSIX 1 ms SystemCounter patch
```

Normally this does not need to be called manually because `generate.sh`
invokes it.

---

## generate.sh

Purpose:

```text
apply patches
+
GOIL regeneration
```

Usage:

```bash
./generate.sh
```

Internally:

```text
source env.sh
→ apply_patches.sh
→ GOIL --target=posix
```

Use after:

```text
clean checkout
OIL changes
Trampoline configuration changes
```

---

## clean_build.sh

Purpose:

```text
remove build/cmake
→ CMake configure
→ full build
```

Usage:

```bash
./clean_build.sh
```

Use after:

```text
CMakeLists.txt changes
source-list changes
compiler configuration changes
major integration changes
milestone validation
```

The actual compilation is delegated to `build.sh`.

---

## build.sh

Purpose:

```text
incremental CMake build
```

Usage:

```bash
./build.sh
```

Full build output is saved to:

```text
/tmp/autosar_virtual_build.log
```

If the build fails, the script automatically displays:

```text
first compiler error with surrounding lines
undefined reference summary
```

Manual compiler error inspection:

```bash
grep -n -m1 -B5 -A10 \
'error:' \
/tmp/autosar_virtual_build.log
```

Manual linker error inspection:

```bash
grep "undefined reference" /tmp/autosar_virtual_build.log \
  | sed 's/.*undefined reference to //g' \
  | sort -u
```

This log file should be used when sharing long build failures with another
agent.

---

## run.sh

Purpose:

```text
run Virtual AUTOSAR
```

Usage:

```bash
./run.sh
```

Executable:

```text
build/cmake/autosar_virtual
```

If the executable does not exist, the script instructs the user to run:

```bash
./clean_build.sh
```

---

# 19. Standard Workflow

## Normal code change

```bash
./build.sh
./run.sh
```

## OIL/configuration change

```bash
./generate.sh
./build.sh
./run.sh
```

## Clean rebuild

```bash
./generate.sh
./clean_build.sh
./run.sh
```

## Milestone reproduction

Use:

```bash
./generate.sh
./clean_build.sh
./run.sh
```

Expected result:

```text
[Virtual AUTOSAR] Starting Trampoline OS
[Virtual AUTOSAR] RTI_Task started
[Virtual AUTOSAR] RTI PSL configuration applied
[Virtual AUTOSAR] OSAPI_System_initialize PASS
[Virtual AUTOSAR] OSAPI_System_finalize PASS
[Virtual AUTOSAR] Phase2 PASS
Exiting virtual platform.
```

---

# 20. Generated Files

Do NOT commit generated build artifacts.

Current `.gitignore` covers:

```text
/build/
/autosar_virtual/
/os/
/build.py
/make.py
/readTrace.py
/trace.json
/config/os/build/
```

GOIL-generated OS files can always be recreated from:

```text
config/os/autosar_virtual.oil
```

---

# 21. Project-Owned Phase 2 Files

Important Phase 2 project files:

```text
CMakeLists.txt
env.sh
.gitignore

apply_patches.sh
generate.sh
clean_build.sh
build.sh
run.sh

config/os/autosar_virtual.oil
config/os/rti_autosar_config.h
config/os/stub.c

patches/trampoline-posix-1ms-systemcounter.patch

platform/rtipsl.cmake

platform/autosar/Compiler_Cfg.h
platform/autosar/Det.c
platform/autosar/HeapAdapter.c
platform/autosar/Os_Types.h
platform/autosar/TcpIp.c
platform/autosar/TcpIp.h

platform/rti/RtiPslConfig.c
platform/rti/RtiPslConfig.h
platform/rti/UDPInterface_wrapper.c
```

---

# 22. External Source Policy

RTI proprietary source and libraries remain external dependencies.

Do NOT copy or commit RTI proprietary source/library files into this repository.

Trampoline remains an upstream Git submodule.

Project-specific Trampoline modifications are stored as patches under:

```text
patches/
```

Do NOT commit modifications directly inside the Trampoline submodule.

---

# 23. Phase 2 PASS Criteria

Verified:

```text
[PASS] Trampoline POSIX AUTOSAR OS execution
[PASS] GOIL generation
[PASS] RTI AUTOSAR PSL compilation
[PASS] RTI AUTOSAR PSL + PIL linking
[PASS] AUTOSAR Resource synchronization
[PASS] Linux-backed TcpIp compatibility layer
[PASS] RTI official System property get/set path
[PASS] OSAPI_System_initialize()
[PASS] OSAPI_System_finalize()
[PASS] ShutdownOS() / clean virtual platform exit
[PASS] clean GOIL regeneration
[PASS] clean CMake build
[PASS] runtime reproduction
[PASS] RTI proprietary source restored before final validation
```

Final status:

```text
PHASE 2 COMPLETE
```

---

# 24. Phase 3 Starting Point

Phase 3 must start from this working baseline.

Primary objective:

```text
DDS CDD / PIL integration above the working AUTOSAR PSL
```

Expected next areas:

```text
DDS initialization
DomainParticipant creation
RTPS UDP path
DDS send path
DDS receive path
DDS Rx indication
receive-thread configuration
actual DDS communication
```

Do NOT redo Phase 0 or Phase 1 validation unless a new integration issue
specifically requires it.

Do NOT switch to:

```text
RTI POSIX PSL
QEMU
FreeRTOS
lwIP
ARM
```

Preserve:

```text
DDS / PIL
    |
AUTOSAR PSL
    |
AUTOSAR OS + TcpIp
    |
Trampoline POSIX
    |
Ubuntu Linux
```

---

# 25. Phase 3 Warning — Receive Thread Configuration

Phase 2 intentionally disables RTI UDP receive threads:

```text
max_user_blocking_threads = 0
semaphore_max_count       = 0
use_udp_thread            = FALSE
```

This configuration must NOT be blindly reused when receive threads are
enabled.

The following settings are coupled and must be configured together:

```text
max_user_blocking_threads
semaphore_max_count
first_give_event
first_timeout_event
first_alarm
max_receive_sockets
number_of_rcv_buffers
rcv_buffer_size
use_udp_thread
dds_rxindication
```

The production RTI AUTOSAR configuration previously used as a reference had
receive-thread-related resources enabled. Phase 3 should use that reference
when implementing the receive path.

---

# 26. Deferred Cleanup

The following are intentionally deferred because they are not required for
Phase 2 correctness:

```text
make TcpIp interface/IP configurable
clean AUTOSAR compiler macro warnings
reduce duplicate compile definitions
clean forced Compiler_Cfg.h inclusion
review E_NOT_OK compatibility semantics
configure RTI receive-thread resources for DDS networking
```

Do not refactor these before Phase 3 requires them.

---

# Final Baseline

The verified Phase 2 baseline is:

```text
Ubuntu x86_64
    |
Trampoline POSIX AUTOSAR OS
    |
AUTOSAR Resource + TcpIp compatibility
    |
RTI AUTOSAR PSL
    |
RTI DDS Micro PIL
```

with:

```text
OSAPI_System_initialize PASS
OSAPI_System_finalize PASS
clean ShutdownOS PASS
```

This is the baseline for Phase 3.