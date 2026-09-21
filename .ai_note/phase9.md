# Phase 9 - Stack / Heap / Memory Monitoring

## Status

```text
PHASE 8: COMPLETE / PASS / GOLDEN
PHASE 9: START
```

This phase continues from the validated Golden runtime baseline and does not redesign the existing architecture.

## Objective

Establish reliable memory observation for the Linux-hosted Virtual AUTOSAR runtime while preserving the Golden AUTOSAR execution architecture.

The purpose is not to pretend that the Linux POSIX environment is a physical MCU. Instead, Phase 9 must determine which memory properties can be measured reliably and give them explicit semantics.

Candidate observation domains include:

```text
AUTOSAR logical task stack usage
Trampoline POSIX task execution stack behavior
Linux process virtual memory
Linux process resident memory
process heap behavior
DDS / PSL / PIL-related process memory behavior
runtime memory trends
monitoring thresholds
```

Measurements must clearly identify whether they represent:

```text
AUTOSAR logical information
Trampoline runtime information
Linux process information
derived / inferred information
```

Do not mix these categories.

## Non-goals

Phase 9 must not:

```text
replace Trampoline scheduling
replace AUTOSAR task activation
change production task priorities
change DDS transport configuration
change DDS socket architecture
change TcpIp polling architecture
change generated RTE semantics
change generated DDS CDD semantics
introduce artificial MCU memory semantics without evidence
claim Linux process memory equals ECU RAM usage
claim Linux pthread/ucontext stack behavior equals MCU task stack behavior
```

Any approximation must be explicitly labeled as such.

## Golden baseline to preserve

The project remains on the Phase 8 Golden baseline:

```text
Application / Mock ASWC
        |
        v
Generated Minimal RTE
        |
        v
Generated DDS CDD
        |
        v
RTI AUTOSAR PSL
        |
        v
RTI DDS Micro PIL
        |
        v
Virtual AUTOSAR TcpIp
        |
        v
Trampoline POSIX AUTOSAR OS
        |
        v
Linux / ViPER
```

Golden runtime behavior must remain intact:

```text
clean generation PASS
clean build PASS
AUTOSAR runtime PASS
Windows -> Virtual AUTOSAR DDS PASS
Virtual AUTOSAR -> Windows DDS PASS
runtime trace generation PASS
runtime monitor decoding PASS
```

## Phase 9 work breakdown

```text
Phase 9.1  Memory Monitoring Capability Investigation
Phase 9.2  Task Stack Monitoring
Phase 9.3  Process Heap / Memory Monitoring
Phase 9.4  Runtime Monitor Integration
Phase 9.5  Threshold / Warning Model
Phase 9.6  Golden Regression
```

No unnecessary subphases are to be added unless the investigation clearly proves that a different decomposition is required.

## Phase 9.1 - Memory Monitoring Capability Investigation

### Final Status

```text
PHASE 9.1: COMPLETE
STATUS: PASS
```

### Objective

Determine which memory properties can be measured reliably in the Linux AUTOSAR Virtual PoC before implementing memory monitoring.

The investigation focused on:

- AUTOSAR task stack representation
- Trampoline POSIX task context implementation
- OIL `STACKSIZE` runtime meaning
- stack boundaries
- existing Trampoline stack-monitoring capability
- feasibility of task stack high-water measurement
- Linux process memory observability
- heap observability
- DDS-specific memory attribution

No runtime architecture or scheduling behavior was changed.

### Task Stack Investigation

Each generated AUTOSAR task has a dedicated stack memory region.

Example generated structure:

```c
tpl_stack_word RTI_Task_stack_zone[
    32768 / sizeof(tpl_stack_word)
];

struct TPL_STACK RTI_Task_stack = {
    RTI_Task_stack_zone,
    32768
};
```

The POSIX machine stack descriptor is:

```c
struct TPL_STACK {
    tpl_stack_word *stack_zone;
    tpl_stack_size stack_size;
};
```

Each task static descriptor references its own stack.

Therefore:

```text
AUTOSAR Task
    -> tpl_proc_static
    -> TPL_STACK
    -> stack_zone + stack_size
```

### OIL STACKSIZE Runtime Effect

The OIL configuration specifies:

```text
STACKSIZE = 32768
```

GOIL generates a 32768-byte stack zone for each configured task.

The Trampoline POSIX context creation code directly uses the generated stack:

```c
new_stack.ss_sp =
    (tpl_stat_proc_table[proc_id]->stack)->stack_zone;

new_stack.ss_size =
    (tpl_stat_proc_table[proc_id]->stack)->stack_size;

sigaltstack(&new_stack, &old_stack);
```

Therefore the OIL `STACKSIZE` value has a real runtime effect on the POSIX task execution stack.

Result:

```text
OIL STACKSIZE runtime effect: CONFIRMED
```

### POSIX Task Context Model

Trampoline POSIX does not use one pthread per AUTOSAR task.

Task context creation uses:

```text
SIGUSR1
  -> SA_ONSTACK
  -> sigaltstack()
  -> setjmp()
  -> longjmp()
```

Each AUTOSAR task therefore executes using its generated stack region while Trampoline manages execution contexts with `jmp_buf`.

This is a real per-task execution stack in the Virtual AUTOSAR runtime.

It must not, however, be described as a physical MCU stack.

### Existing Trampoline Stack Monitoring

Trampoline contains a generic stack-monitoring framework including:

```c
tpl_check_stack()
tpl_check_stack_pointer()
tpl_check_stack_footprint()
```

The generic OS kernel can invoke stack checking during scheduling/context-switch paths when stack monitoring is enabled.

However, the POSIX implementation is:

```c
tpl_check_stack_pointer(...)
{
    return 1;
}

tpl_check_stack_footprint(...)
{
    return 1;
}
```

Both functions are stubs.

Therefore enabling:

```text
STACKMONITORING = TRUE
```

would not provide meaningful stack checking on the POSIX target.

Result:

```text
Trampoline generic monitoring framework : AVAILABLE
Trampoline POSIX implementation          : STUB
Built-in POSIX stack high-water          : NOT AVAILABLE
```

The Trampoline submodule should not be modified merely to implement Phase 9 monitoring.

### Project-Owned Stack Monitoring Feasibility

The following information is available:

- stack base address
- stack size
- separate stack region for each task
- generated task-to-stack association

Therefore project-owned stack observation is feasible.

A stack painting / footprint technique is a candidate for Phase 9.2.

The implementation must account for stack usage during POSIX context creation before deciding when painting can safely occur.

### Linux Process Memory

The runtime executable is:

```text
build/cmake/autosar_virtual
```

The host uses glibc 2.43.

Linux `/proc/<pid>/status` exposes useful process-level metrics including:

```text
VmPeak
VmSize
VmHWM
VmRSS
RssAnon
RssFile
RssShmem
VmData
VmStk
```

Therefore process-level runtime memory monitoring is feasible without modifying AUTOSAR scheduling.

Candidate Phase 9 metrics include:

```text
VmSize  - Linux virtual address-space size
VmRSS   - current resident memory
VmHWM   - peak resident memory
VmData  - process data mapping metric
```

`VmData` must not be presented as exact heap usage.

### Heap Investigation

The Virtual AUTOSAR adaptation layer contains:

```c
void *
OSAPI_Heap_realloc(void *ptr, RTI_SIZE_T size)
{
    if (size == 0U)
    {
        return NULL;
    }

    return realloc(ptr, (size_t)size);
}
```

This confirms that allocation requests reaching this adapter use the glibc allocator.

However, there is no evidence that every DDS / PSL / PIL allocation passes through this function.

Therefore:

```text
Process heap observation       : POSSIBLE
DDS-specific heap attribution  : LIMITED
```

No claim should be made that process heap usage equals DDS memory usage.

### Measurement Semantics

Phase 9 must preserve the following distinction:

```text
AUTOSAR Task Stack
    Trampoline POSIX per-task execution stack

Linux Process Memory
    VmRSS / VmHWM / VmSize and related Linux metrics

Heap
    glibc/process allocator observation

DDS Memory
    included in overall process memory
    exact attribution is limited
```

Linux process memory must not be presented as physical ECU RAM.

Likewise, the Trampoline POSIX task stack must not be presented as the exact stack behavior of a physical MCU target.

### Capability Matrix

```text
Capability                                  Result
Per-task stack allocation                   YES
Per-task stack size                         AVAILABLE
OIL STACKSIZE runtime effect                CONFIRMED
Stack boundaries                            AVAILABLE
Task context implementation                 setjmp / longjmp
POSIX execution stack                      sigaltstack
pthread per AUTOSAR task                   NO
Built-in POSIX stack monitoring            STUB / NOT USABLE
Project-owned stack high-water              POSSIBLE
Linux RSS                                  POSSIBLE
Linux peak RSS                             POSSIBLE
Linux virtual memory                       POSSIBLE
Process heap observation                    POSSIBLE / LIMITED
DDS-specific memory attribution             LIMITED
```

### Architecture Decision

Phase 9 monitoring will follow this rule:

```text
Do not modify Trampoline merely to obtain memory monitoring.

Prefer:
1. existing generated/runtime information
2. project-owned observation
3. Linux process interfaces
4. integration into the existing runtime-monitor architecture
```

Memory measurements must remain semantically separate from scheduler trace data.

### Golden Baseline Impact

Phase 9.1 was investigation only.

No changes were made to:

- AUTOSAR task priorities
- task activation behavior
- resources
- scheduler
- RTE
- generated CDD
- DDS transport
- TcpIp
- PSL/PIL
- runtime trace
- ErrorHook

Therefore the existing Phase 8 Golden runtime architecture remains unchanged.

### PASS Criteria

Phase 9.1 passes when:

- task stack representation is understood
- OIL `STACKSIZE` runtime meaning is established
- stack boundaries are identifiable
- built-in POSIX monitoring capability is determined
- project-owned stack monitoring feasibility is determined
- Linux process memory observability is established
- heap/DDS attribution limitations are explicitly documented

All criteria are satisfied.

### Final Result

```text
PHASE 9.1: PASS

Per-task stack monitoring:
    FEASIBLE through project-owned observation

Linux process memory monitoring:
    FEASIBLE

Heap monitoring:
    FEASIBLE with explicit limitations

DDS-specific memory attribution:
    LIMITED

Trampoline POSIX built-in stack monitoring:
    NOT USABLE because implementation is stubbed
```

### Next Phase

Phase 9.2 - Task Stack Monitoring

The first Phase 9.2 investigation will determine the safe stack-painting point relative to:

```text
stack allocation
context creation
sigaltstack()
setjmp()/longjmp()
first task dispatch
```

The goal is to measure per-task stack high-water usage without corrupting a saved task context or changing AUTOSAR scheduling semantics.

## Phase 9.2 - Task Stack Monitoring

### Final Status

```text
PHASE 9.2: COMPLETE
STATUS: PASS
```

Phase 9.2 established project-owned task stack high-water monitoring for the Linux AUTOSAR Virtual PoC without changing the Golden AUTOSAR task scheduling architecture, generated AUTOSAR sources, or the Trampoline POSIX scheduler implementation.

The measured quantity is explicitly defined as:

> Trampoline POSIX AUTOSAR Task Stack High-Water

It is not a claim of physical MCU stack usage or exact production ECU RAM consumption.

### Objective

Validate that the Trampoline POSIX target provides independently bounded execution stacks for AUTOSAR tasks and implement a low-intrusion mechanism that can:

- initialize a known stack fill pattern before OS startup,
- observe stack high-water usage later,
- preserve existing AUTOSAR task scheduling,
- avoid generated-source modifications,
- avoid Trampoline scheduler modifications,
- remain compatible with the existing DDS/TcpIp runtime and Phase 8 trace monitor.

### Investigation Findings

#### Per-task stack allocation

The generated Trampoline configuration provides an independent stack region for each AUTOSAR task.

Each configured task has:

```text
stack_zone
stack_size = 32768 bytes
```

The generated process descriptors reference these stack objects through `tpl_proc_static`.

The runtime relationship is:

```text
OIL STACKSIZE
    -> generated stack_zone[]
    -> TPL_STACK
    -> tpl_proc_static.stack
    -> POSIX sigaltstack()
    -> task context creation
```

#### POSIX context implementation

The Trampoline POSIX port creates task contexts using:

- `sigaltstack()`
- a signal handler
- `setjmp()`
- `longjmp()`

No pthread- or ucontext-based task implementation was identified in the investigated execution path.

This means the generated task stack regions are actually used as Trampoline POSIX task execution stacks.

#### Existing Trampoline stack monitoring

Trampoline contains generic stack-monitoring infrastructure, but the POSIX implementations of the stack checking functions are stubs returning success.

Therefore:

```text
Generic Trampoline stack-monitoring framework : AVAILABLE
Functional POSIX stack high-water monitoring  : NOT AVAILABLE
```

Enabling `STACKMONITORING` alone would therefore not provide a valid POSIX high-water measurement.

The generic `PAINT_STACK` concept also exists in Trampoline, but no applicable POSIX stack-paint implementation was found.

### Implementation

Phase 9.2 adds a project-owned monitor:

```text
platform/autosar/StackMonitor.h
platform/autosar/StackMonitor.c
```

The implementation accesses task stack descriptors through:

```text
tpl_stat_proc_table[task_id]
    -> tpl_proc_static
    -> stack
    -> stack_zone / stack_size
```

It does not directly reference generated task-specific stack symbols.

#### Initialization

`Phase9_StackMonitor_Init()` paints configured AUTOSAR task stacks with:

```c
0xA5A5A5A5
```

using `tpl_stack_word`.

Initialization occurs before `StartOS()`:

```text
DdsCdd_Init()
Phase9_StackMonitor_Init()
StartOS(stdAppmode)
```

This ordering is intentional. Painting after Trampoline creates the POSIX contexts could overwrite context/bootstrap data already stored in the stack region.

Only configured AUTOSAR tasks in `TASK_COUNT` are painted. The idle task is not part of the Phase 9.2 monitored task set.

#### High-water calculation

`Phase9_StackMonitor_GetUsage()` reports:

```c
typedef struct
{
    size_t allocated_bytes;
    size_t used_high_water_bytes;
    size_t free_high_water_bytes;
} Phase9_StackUsage;
```

For the current Linux x86_64 POSIX environment, the implementation assumes stack growth from higher addresses toward lower addresses.

The monitor scans the untouched fill pattern from the low-address boundary.

Conceptually:

```text
free_high_water = consecutive untouched pattern bytes
used_high_water = allocated stack - free_high_water
```

### Measurement Semantics

The metric includes memory touched by:

- Trampoline POSIX task context/bootstrap creation,
- task execution,
- function calls executing on the task stack.

Therefore the result must be described as:

```text
Trampoline POSIX AUTOSAR Task Stack High-Water
```

It must not be described as:

```text
pure runnable stack usage
physical MCU task stack usage
production ECU RAM usage
```

The current task should not normally measure its own stack. Cross-task observation avoids contaminating or destabilizing the measurement with the monitor call's own stack activity.

### Experimental Evidence

The high-water mechanism successfully produced differentiated, bounded values for the configured tasks.

Representative observations during validation included:

| Task                   | Allocated | Observed Used | Observed Free |
|------------------------|----------:|--------------:|--------------:|
| DdsCddProcessData_Task |   32768 B |        3576 B |       29192 B |
| DdsCddReadWrite_Task   |   32768 B |        6856 B |       25912 B |
| RTI_Task               |   32768 B |        7080 B |       25688 B |
| DdsCddTimerTick_Task   |   32768 B |        3904 B |       28864 B |
| TcpIp_Task             |   32768 B |  9792-11400 B | 22976-21368 B |
| App_Task               |   32768 B |      1488 B* |     31280 B* |

`*` The App_Task value was an early cross-task snapshot used to prove measurement capability. It is not treated as a representative final workload high-water value.

The differing non-zero/non-full values demonstrated that the stack paint was being consumed according to runtime activity rather than producing a trivial all-unused or all-used result.

### Temporary Validation Instrumentation

During validation, bounded diagnostic probes were temporarily added to existing tasks to demonstrate cross-task stack observation.

These included:

```text
Phase9_PrintStackUsage()
Phase9_PrintAppStackUsage()
TcpIp task entry probe
BEFORE/AFTER App stack measurement probes
```

All temporary task-path probes were removed after validation.

The permanent task implementation retains only:

```text
#include "StackMonitor.h"

Phase9_StackMonitor_Init();
```

before `StartOS()`.

No periodic stack-scanning or diagnostic `printf()` remains in the normal AUTOSAR task scheduling path.

### Golden Regression

#### Generation and build

```text
Clean generation : PASS
Clean build      : PASS
```

Executable linkage confirmed both APIs:

```text
Phase9_StackMonitor_Init
Phase9_StackMonitor_GetUsage
```

#### AUTOSAR runtime

The cleaned implementation successfully ran the existing Virtual AUTOSAR application with:

```text
Trampoline POSIX scheduling
TcpIp / UDP runtime
RTI task startup
DdsCdd startup
DDS runtime activity
```

Result:

```text
AUTOSAR runtime regression : PASS
```

#### Phase 8 trace/runtime monitor

The Phase 8 runtime monitor successfully parsed the new runtime trace using:

```bash
python3 tools/runtime_monitor/runtime_monitor.py \
    trace.json \
    --static-info autosar_virtual/tpl_static_info.json \
    --derived \
    --limit 100
```

Derived events were decoded successfully, including:

```text
ACTIVATE
DISPATCH_NEW
TERMINATE
WAIT
PREEMPT
RESUME
RESOURCE_ACQUIRE
RESOURCE_RELEASE
ALARM_EXPIRE
EVENT_SET
EVENT_RESET
WAKEUP
WAKEUP_DISPATCH
```

Observed summary:

```text
raw_records=32918
derived_records=32918
parser_warnings=1
trace_incomplete=yes
```

The incomplete trace is consistent with terminating the running application with Ctrl+C and the Phase 8 monitor's existing truncated-EOF handling. It is not treated as a Phase 9.2 regression.

Result:

```text
Phase 8 trace generation / derived decoding : PASS
```

### Architecture Impact

Phase 9.2 does not change:

- AUTOSAR task priorities,
- task activation model,
- alarm configuration,
- DDS transport,
- TcpIp polling architecture,
- RTE semantics,
- DDS CDD semantics,
- Trampoline scheduler behavior,
- generated AUTOSAR task sources.

The stack monitor is a project-owned observation facility layered on the existing Golden runtime.

### Limitations

1. The measurement is specific to the Trampoline POSIX execution model.
2. It is not equivalent to physical MCU stack usage.
3. Context/bootstrap overhead is included.
4. Stack growth direction is currently based on the validated x86_64 POSIX environment.
5. The implementation assumes the fill pattern remains suitable for high-water observation.
6. A snapshot is only a high-water observation up to the time it is taken.
7. Measuring the currently executing task from itself is not the preferred observation model.
8. Phase 9.2 provides the measurement primitive; persistent runtime presentation/integration belongs to Phase 9.4.

### Phase 9.2 PASS Criteria

| Criterion                                         | Result |
|---------------------------------------------------|--------|
| Independent per-task stack regions confirmed      | PASS   |
| OIL/generated stack size available                | PASS   |
| POSIX task stack actually used for task contexts  | PASS   |
| Safe pre-StartOS stack painting established       | PASS   |
| Project-owned implementation                      | PASS   |
| No generated-source modification required         | PASS   |
| No new Trampoline scheduler modification required | PASS   |
| Cross-task high-water measurement demonstrated    | PASS   |
| All six configured AUTOSAR tasks measurable       | PASS   |
| Temporary task probes removed                     | PASS   |
| Clean build                                       | PASS   |
| AUTOSAR runtime regression                        | PASS   |
| Phase 8 derived trace decoding regression         | PASS   |

### Final Result

```text
PHASE 9.2: COMPLETE

STATUS: PASS
```

Phase 9.2 provides a bounded and semantically explicit stack high-water measurement primitive suitable for the Linux AUTOSAR Virtual PoC.

The next planned subphase is:

```text
Phase 9.3 - Process Heap / Memory Monitoring
```

## Measurement philosophy

Prefer measurements that are:

```text
bounded
repeatable
low intrusion
read-only where possible
semantically clear
automatable
comparable between runs
```

Avoid measurements that require:

```text
scheduler replacement
continuous printf from task context
heavy periodic file I/O
dynamic allocation from ErrorHook
signal-unsafe operations
large instrumentation inside critical sections
```

A useful measurement with clearly stated limitations is preferable to a misleading MCU-like metric.

## Important constraints

- Do not modify generated files under `autosar_virtual/`.
- Do not modify `third_party/trampoline` without strong evidence that project-owned code cannot satisfy the objective.
- Do not restore the known 10 ms -> 1 ms POSIX timer change during Phase 9.
- Do not treat Linux process memory as ECU RAM usage.
- Keep the existing runtime monitor architecture and trace semantics intact.

## Phase 9.1 PASS criteria

Phase 9.1 is complete only when the investigation produces evidence-backed answers for:

```text
how AUTOSAR task stacks are represented on POSIX
whether OIL STACKSIZE is meaningful at runtime
whether per-task stack boundaries are available
whether a safe high-water mechanism is possible
what can be measured without modifying Trampoline
```

The next implementation phase should only begin after these answers are grounded in evidence.

## Immediate next step

Proceed with the inspection-only Phase 9.1 experiment above and classify the available memory-monitoring capability before implementing any Phase 9 instrumentation.

## Final Phase 9 status

```text
PHASE 9.1: COMPLETE / PASS
PHASE 9.2: COMPLETE / PASS
PHASE 9: IN PROGRESS
```

Prefer measurements that are:

```text
bounded
repeatable
low intrusion
read-only where possible
semantically clear
automatable
comparable between runs
```

Avoid measurements that require:

```text
scheduler replacement
continuous printf from task context
heavy periodic file I/O
dynamic allocation from ErrorHook
signal-unsafe operations
large instrumentation inside critical sections
```

A useful measurement with clearly stated limitations is preferable to a misleading MCU-like metric.

## Important constraints

- Do not modify generated files under `autosar_virtual/`.
- Do not modify `third_party/trampoline` without strong evidence that project-owned code cannot satisfy the objective.
- Do not restore the known 10 ms -> 1 ms POSIX timer change during Phase 9.
- Do not treat Linux process memory as ECU RAM usage.
- Keep the existing runtime monitor architecture and trace semantics intact.

## Phase 9.1 PASS criteria

Phase 9.1 is complete only when the investigation produces evidence-backed answers for:

```text
how AUTOSAR task stacks are represented on POSIX
whether OIL STACKSIZE is meaningful at runtime
whether per-task stack boundaries are available
whether a safe high-water mechanism is possible
what can be measured without modifying Trampoline
```

The next implementation phase should only begin after these answers are grounded in evidence.

## Immediate next step

Proceed with the inspection-only Phase 9.1 experiment above and classify the available memory-monitoring capability before implementing any Phase 9 instrumentation.
