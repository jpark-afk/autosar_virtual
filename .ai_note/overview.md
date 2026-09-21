# Virtual AUTOSAR Linux PoC - Project Overview

This document is the authoritative high-level roadmap for the project.
Individual phase notes preserve the engineering state recorded when they were
written. If an older phase note uses a different roadmap or phase title, the
numbering and status in this overview take precedence.

## Project Goal

Build an Ubuntu-native Virtual AUTOSAR ECU that runs the existing DDS CDD,
RTI Connext DDS Micro PIL, and AUTOSAR PSL on Trampoline POSIX while providing
real DDS communication, generated minimal RTE integration, observability, and
ECU-like robustness testing.

This is an integration and test PoC, not a general AUTOSAR Classic platform or
toolchain.

## Fixed Architecture

```text
Windows DDS Host (192.168.56.1)
        <-> UDP / RTPS
Ubuntu VM enp0s8 (192.168.56.105/24)
        <-> Linux-backed Virtual AUTOSAR TcpIp
        <-> Trampoline POSIX AUTOSAR OS
        <-> RTI AUTOSAR PSL
        <-> RTI DDS Micro PIL
        <-> DDS CDD
        <-> Generated Minimal RTE
        <-> Application / Mock ASWC
```

The Phase 3 communication path is the frozen Golden Baseline. Later phases
must preserve bidirectional DDS behavior.

Do not introduce QEMU, FreeRTOS, lwIP, ARM, 32-bit builds, or RTI POSIX PSL.
RTI proprietary source and libraries remain external to the repository.

## Official Roadmap

| Phase | Scope | Status |
|---|---|---|
| 0 | Environment / x86_64 ABI / PIL compatibility | PASS |
| 1 | Trampoline POSIX AUTOSAR OS | PASS |
| 2 | RTI AUTOSAR PSL / PIL integration | PASS |
| 3 | Real DDS over Virtual AUTOSAR TcpIp | GOLDEN BASELINE |
| 4 | DdsCdd RTE Auto Generator | PASS |
| 5 | OS Robustness / Error / Resource | PASS |
| 6 | AUTOSAR Trace / Runtime Monitor | PASS |
| 7 | Stack / Heap / Memory Monitoring | NEXT |
| 8 | Stress / Fault Injection | PLANNED |
| 9 | Integrated DdsCdd / DDS Validation | PLANNED |
| 10 | Final Virtual ECU Test Bench | PLANNED |
| 11 | Documentation / Reproducibility / Release | PLANNED |

Phase 4 absorbed earlier generator/import work that had previously occupied
later roadmap numbers. The table above is the current numbering.

## Completed Baseline

### Phase 0 - Environment and ABI

- Ubuntu Server 26.04.1 LTS, x86_64
- GCC 13.4.0, GNU binutils 2.46
- RTI Connext DDS Micro 4.3.0 ER738
- `librti_mezd.a`, `x86_64leElfgcc13.3.0`, ELF64 x86-64
- Native whole-archive link validation passed

### Phase 1 - Trampoline POSIX

- Trampoline submodule revision `ff2870232`
- GOIL and ViPER validated
- Basic and Extended Tasks, Events, Resources, Counter, Alarm, and Shutdown
- Project-owned patch supplies the required 1 ms SystemCounter tick

### Phase 2 - RTI AUTOSAR PSL / PIL

- RTI AUTOSAR PSL compiled and linked with PIL
- AUTOSAR Resource synchronization and Linux-backed TcpIp compatibility
- `OSAPI_System_initialize()` and `OSAPI_System_finalize()` passed
- RTI POSIX PSL is intentionally not used

### Phase 3 - DDS Golden Baseline

- Virtual TcpIp binds DDS receive sockets on UDP 8910 and 8911
- RTPS transmit reaches `TcpIp_UdpTransmit()` and Linux `sendto()`
- RTPS receive reaches the DDS CDD/RTE event-driven processing path
- Windows Host and Linux exchanged DDS samples in both directions
- Preserve the existing task priorities, resources, socket configuration, and
  RTI receive configuration

### Phase 4 - Minimal Generated RTE

- CDD ARXML and generated-code scanner
- Semantic endpoint, runnable, event, and datatype model
- Generated `Rte_Type.h`, `Rte_DdsCddType.h`, and `Rte_DdsCddType.c`
- Endpoint-specific Read/Write buffers and DataReceived handling
- InternalTrigger mapping to the fixed OS topology
- Generated CDD task implementation
- Clean generation/build and Golden DDS regression passed

The generator remains deliberately narrow. It does not generate a full RTE,
ECUC, Composition, ECU Mapping, or dynamic OS topology.

### Phase 5 - OS Robustness / Error / Resource

Completed baseline for OS error handling, activation/resource behavior, and
robustness. Preserve Trampoline ownership of scheduler, resource, priority
ceiling, activation-limit, and ErrorHook semantics.

### Phase 6 - AUTOSAR Trace / Runtime Monitor

Completed baseline for AUTOSAR logical tracing and runtime monitoring. Logical
task states come from Trampoline behavior rather than Linux scheduler inference.
Preserve the distinction between AUTOSAR logical timing and Linux host timing.

## Phase 7 - Stack / Heap / Memory Monitoring

Phase 7 is the current next phase.

### Task Stack

Track, where supported:

- configured stack size
- current or estimated usage
- high-water mark
- overflow or stack-fault indication

Use Trampoline stack allocation and monitoring first. Add only missing
observability as project-owned custom code, and do not describe custom metrics
as Trampoline or AUTOSAR OS features.

### Heap

Provide project-owned monitoring for:

- current usage
- peak usage
- configured Virtual ECU limit
- allocation and free counts
- allocation failures
- outstanding allocations
- potential leaks

The configured heap budget must be enforced even when Linux has additional
memory available.

### Phase 7 Exit Criterion

```text
Configured task stack information is visible
+ stack pressure/overflow behavior is characterized
+ heap current/peak/limit/failures/outstanding allocations are visible
+ the memory monitor integrates with the existing runtime monitor
+ clean build and Phase 3 DDS regression remain PASS
```

## Phase 8 - Stress / Fault Injection

Exercise and observe:

- task overload
- activation overflow and `E_OS_LIMIT`
- event burst
- resource contention and nested resources
- stack pressure
- heap exhaustion and allocation failure
- DDS/UDP traffic burst

Each test must isolate one fault, capture monitor/trace evidence, and preserve
safe continued execution where Trampoline semantics permit it.

## Phase 9 - Integrated DdsCdd / DDS Validation

Run the complete application path:

```text
DdsCdd
  -> Generated RTE
  -> Trampoline
  -> RTI AUTOSAR PSL / PIL
  -> Virtual TcpIp
  -> DDS / RTPS
  -> Windows DDS application
```

Validate normal bidirectional DDS operation with trace, runtime monitor, and
memory monitor enabled. Include regression of generated RTE endpoint behavior
and known sample payloads.

## Phase 10 - Final Virtual ECU Test Bench

Package a reusable workflow:

```text
import DdsCdd
  -> generate minimal RTE and CDD task glue
  -> configure/build
  -> run Virtual ECU
  -> execute DDS test
  -> collect trace
  -> inspect runtime and memory monitors
```

The result is a repeatable test bench, not a general AUTOSAR authoring tool.

## Phase 11 - Documentation / Reproducibility / Release

Freeze and document:

- host installation and dependencies
- external RTI setup
- build and run procedures
- DdsCdd replacement/import workflow
- RTE generation
- DDS E2E validation
- trace and monitor usage
- stress/fault tests
- known limitations
- verified Git milestone and release state

## Working Rules

1. Read this overview and the current phase note before changing code.
2. Preserve completed phases and the Phase 3 Golden communication baseline.
3. State one concrete goal and one PASS criterion per step.
4. Inspect the owning code path and make the smallest change.
5. Build and run focused validation immediately after each edit.
6. Diagnose failures before changing architecture.
7. Keep RTI proprietary source/libraries outside Git.
8. Keep Trampoline modifications patch-based.
9. Commit only verified working milestones.
10. Keep generated and temporary build artifacts out of Git.

## Standard Environment and Commands

```bash
cd ~/autosar_virtual
source ./env.sh
./generate.sh
./clean_build.sh
./build.sh
./run.sh
```

Build log:

```text
/tmp/autosar_virtual_build.log
```

Force-stop when required:

```bash
pkill -f autosar_virtual
```
