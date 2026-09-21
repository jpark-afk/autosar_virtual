# Phase 10 - Stress / Fault Injection

## Final Status

```text
PHASE 9: COMPLETE / PASS / GOLDEN
PHASE 10.1: COMPLETE / PASS
CURRENT NEXT STEP: Phase 10.2 AUTOSAR OS Fault Injection
```

## Objective

Phase 10 validates whether the Linux AUTOSAR Virtual PoC can create
bounded, deterministic, observable, and removable stress/fault conditions
without redesigning the Golden architecture.

Phase 10.1 investigated the existing project and produced the smallest
safe test matrix. No production behavior was modified.

## Golden Baseline Preserved

```text
Application / Mock ASWC
   <-> Generated Minimal RTE
   <-> Generated DDS CDD
   <-> RTI AUTOSAR PSL
   <-> RTI DDS Micro PIL
   <-> Virtual AUTOSAR TcpIp
   <-> Trampoline POSIX AUTOSAR OS
   <-> Linux / ViPER
```

Phase 10.1 changed none of the following:

```text
Trampoline source
generated RTE/CDD artifacts
DDS transport configuration
RTI PSL/PIL
production DDS resources
production task priorities
production alarm periods
```

The existing Trampoline POSIX 1 ms timer dependency remains Golden:

```text
tpl_viper_start_auto_timer(signal_for_counters, 1000);
```

## Existing ErrorHook Capability

The permanent Phase 7 ErrorHook remains bounded:

```c
typedef struct
{
    volatile unsigned long count;
    volatile StatusType error;
    volatile uint8 service_id;
} Phase7_OsErrorRecord;

static Phase7_OsErrorRecord g_phase7_os_error = {
    0UL,
    E_OK,
    0
};

void ErrorHook(StatusType error)
{
    g_phase7_os_error.error = error;
    g_phase7_os_error.service_id = OSErrorGetServiceId();
    g_phase7_os_error.count++;
}
```

It records only error, service ID, and count. It must not gain printf,
file/socket I/O, blocking, dynamic allocation, DDS operations, or heavy
monitoring.

## Preferred Injection Context

The project-owned application task is the preferred injection context:

```c
TASK(App_Task)
{
    VirtualAswc_Run();
    TerminateTask();
}
```

Its OIL configuration is:

```text
PRIORITY   = 2
AUTOSTART  = FALSE
ACTIVATION = 1
SCHEDULE   = FULL
```

`App_Task` is activated by `AppAlarm` at a 1000 ms period. Injection must
not be placed in RTI, TcpIp, DdsCdd, generated CDD/RTE, PSL/PIL, or the
Trampoline kernel unless a later experiment proves it necessary.

## Deterministic OS Fault Capability

Phase 7 established these recoverable fault paths.

### FI-OS-01: E_OS_LIMIT

With `ACTIVATION = 1`, `App_Task` can call `ActivateTask(App_Task)` while
already active. Expected result:

```text
return value       = E_OS_LIMIT = 4
ErrorHook delta    = 1
service ID         = ActivateTask = 12
runtime continues
```

### FI-OS-02: E_OS_ACCESS

Using a dedicated test resource only:

```text
GetResource(TestResource)
GetResource(TestResource)
```

The second acquisition is expected to produce `E_OS_ACCESS` and invoke
ErrorHook. Production DDS resources remain isolated.

### FI-OS-03: E_OS_NOFUNC

Using two dedicated nested test resources:

```text
GetResource(ResourceA)
GetResource(ResourceB)
ReleaseResource(ResourceA)   <- invalid order
```

The invalid release is expected to produce `E_OS_NOFUNC`; valid cleanup
must then complete. No Phase 7 or Phase 10 test resources remain in the
Golden OIL baseline.

## Stress Capabilities

### ST-CPU-01: Bounded Workload

Use a finite project-owned helper called from `App_Task`. Observe changed
execution and scheduling behavior with `trace.json` and the runtime
monitor. Do not alter production priorities or use an infinite loop.

### ST-STK-01: Bounded Stack Pressure

All Golden tasks use `STACKSIZE = 32768`. A bounded local stack consumer
from `App_Task` should produce:

```text
used_high_water_bytes increases
free_high_water_bytes decreases
allocated_bytes remains 32768
allocated = used + free
```

The first experiment must remain below overflow. Uncontrolled recursion
and native stack corruption are excluded.

### ST-MEM-01: Bounded Allocation/Free

Use a bounded project-owned allocation sequence and observe before,
during, and after cleanup with `Phase9_ProcessMemory_GetUsage()`:

```text
VmRSS / VmHWM / VmSize / VmData
glibc arena / used / free / mmap
```

These remain Linux host observations, not physical ECU RAM or exact
AUTOSAR heap measurements.

### ST-NET-01: DDS/Network Burst

Defer bounded traffic stress until OS, CPU, stack, and allocation tests
are stable. Preserve the DDS/TcpIp architecture and Golden alarm periods.
Observe DDS continuity together with Phase 8 trace and Phase 9 memory and
stack measurements.

## Phase 10 Test Matrix

| ID | Category | Injection | Expected effect | Observation | Risk |
| --- | --- | --- | --- | --- | --- |
| FI-OS-01 | AUTOSAR Fault | `App_Task` self-activation | `E_OS_LIMIT` | ErrorHook and API return | Low |
| FI-OS-02 | AUTOSAR Fault | duplicate test-resource acquisition | `E_OS_ACCESS` | ErrorHook and API return | Low |
| FI-OS-03 | AUTOSAR Fault | wrong-order nested release | `E_OS_NOFUNC` | ErrorHook and API return | Low |
| ST-CPU-01 | Scheduling Stress | bounded `App_Task` workload | scheduling pressure | Phase 8 trace | Low |
| ST-STK-01 | Stack Stress | bounded local stack use | higher high-water | Phase 9 stack monitor | Low/Medium |
| ST-MEM-01 | Host Memory Stress | bounded allocation/free | process/allocator change | Phase 9 memory monitor | Low |
| ST-NET-01 | DDS/Network Stress | bounded traffic increase | communication pressure | DDS + Phase 8/9 | Medium |

## Observation Infrastructure

```text
OS errors              Phase 7 ErrorHook
scheduling/resources   trace.json + tools/runtime_monitor/runtime_monitor.py
task stack             Phase9_StackMonitor_GetUsage()
process memory         Phase9_ProcessMemory_GetUsage()
memory snapshot        Phase9_MemorySnapshot_WriteJson()
communication          Windows DDS Host <-> Virtual AUTOSAR DDS
```

## Experiment Evidence Format

Each experiment must record:

```text
Experiment ID
Objective
Baseline
Injection
Expected result
Actual result
Trace evidence
ErrorHook evidence, if applicable
Memory evidence, if applicable
DDS evidence, if applicable
Cleanup
Golden regression
PASS / FAIL
```

Process survival alone is not a PASS condition. PASS requires the
expected effect to be produced and observed through the intended
mechanism.

## Prohibited Techniques

```text
random pointer corruption or memory writes
scheduler or DDS internal corruption
uncontrolled recursion or infinite CPU loops
uncontrolled native stack overflow
production DDS resources for destructive tests
production priority/alarm changes for convenience
manual generated-code edits
heavy ErrorHook work
direct Trampoline changes unless proven unavoidable
host process termination presented as AUTOSAR fault handling
```

## Classification

```text
FAULT           deliberate invalid condition with expected recovery
STRESS          valid operation under bounded increased load
AUTOSAR LOGICAL AUTOSAR OS/API behavior
HOST ARTIFACT   Linux/POSIX-specific observation
DDS/NETWORK     communication-path load or failure behavior
```

Linux/POSIX behavior must not be represented as physical ECU hardware
behavior.

## Phase 10.1 Findings and PASS Criteria

The existing Phase 7/8/9 mechanisms are sufficient; no new fault
handling framework or Golden architecture change is required.

```text
[PASS] bounded ErrorHook verified
[PASS] project-owned App_Task injection context identified
[PASS] E_OS_LIMIT path identified
[PASS] E_OS_ACCESS path identified
[PASS] E_OS_NOFUNC path identified
[PASS] production DDS resources isolated
[PASS] CPU stress location identified
[PASS] stack-pressure mechanism identified
[PASS] process/allocation mechanism identified
[PASS] DDS/network stress boundary identified
[PASS] existing observation mechanisms are sufficient
[PASS] no production behavior modified
```

## Cleanup State

```text
no Phase 10 injection code introduced
no Phase 10 test resources in Golden OIL
no active fault injection
no stress workload
no modified production alarms or priorities
no Trampoline changes for Phase 10
```

## Limitations

Phase 10.1 establishes capability and test design only. It does not yet
provide execution evidence for Phase 10.2 faults or later CPU, stack,
allocation, DDS, and integrated stress experiments.

## Next Step

Proceed to Phase 10.2 with only the minimum test-only control required to
execute `FI-OS-01`, then collect ErrorHook/API evidence, cleanly disable
the injection, and run the Golden regression before selecting the next
fault.

## Final Phase 10 Completion

Phase 10 may close only after selected experiments are reproducible,
bounded, observable, cleaned up, and followed by a passing Golden
regression covering runtime, DDS, Phase 8 trace, and Phase 9 memory
monitoring. The final completion artifact must be an actual Markdown file
named `phase10_<final>.md`.
