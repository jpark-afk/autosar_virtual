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

## Phase 9.3 - Process Heap / Memory Monitoring

### Final Status

```text
PHASE 9.3: COMPLETE
STATUS: PASS
```

Phase 9.3 established project-owned Linux process memory and glibc allocator observation for the Linux AUTOSAR Virtual PoC without adding periodic memory polling to the AUTOSAR task execution path.

The measurements are intentionally separated into two semantic domains:

```text
Linux Process Memory
glibc Allocator Statistics
```

Neither domain is presented as physical ECU RAM or an exact embedded AUTOSAR heap measurement.

### Objective

Provide a low-intrusion memory snapshot API capable of observing:

- current resident process memory,
- peak resident process memory,
- virtual address-space size,
- Linux data mapping size,
- glibc allocator arena statistics,
- allocator used/free block statistics,
- mmap-backed allocator statistics.

The implementation must preserve the existing Golden AUTOSAR scheduling, DDS, TcpIp, RTE, CDD, and Phase 8 trace behavior.

### Capability Investigation

The host environment provides:

```text
glibc 2.43
/proc/self/status
mallinfo2()
malloc_info()
malloc_stats()
```

Relevant `/proc/self/status` fields were confirmed available:

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

Phase 9.3 uses the following process metrics:

| Metric | Meaning |
|--------|---------|
| VmRSS  | Current resident process memory |
| VmHWM  | Peak resident process memory |
| VmSize | Current virtual address-space size |
| VmData | Linux data mapping size; not exact heap usage |

### Heap Adapter Investigation

The existing compatibility adapter is:

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

Project-source inspection found the adapter itself and its build/documentation references, but did not establish that every DDS/PSL/PIL allocation is routed through this function.

Therefore:

```text
HeapAdapter call accounting != complete DDS heap accounting
```

Phase 9.3 does not use HeapAdapter instrumentation as the authoritative process heap measurement.

### glibc Allocator Observation

`mallinfo2()` was confirmed available and functional in the actual Virtual AUTOSAR process.

The monitored allocator fields are:

| Field    | Phase 9.3 interpretation |
|----------|--------------------------|
| arena    | Space obtained for non-mmap allocator arenas |
| uordblks | Space occupied by currently allocated blocks |
| fordblks | Space in free allocator blocks |
| hblkhd   | Space in mmap-backed allocation regions |

These values are labeled:

```text
glibc Allocator Statistics
```

They are not labeled as ECU heap usage.

### Implementation

Phase 9.3 adds:

```text
platform/autosar/ProcessMemoryMonitor.h
platform/autosar/ProcessMemoryMonitor.c
```

and registers the source in `CMakeLists.txt`.

The public snapshot structure is:

```c
typedef struct
{
    size_t vm_rss_kb;
    size_t vm_hwm_kb;
    size_t vm_size_kb;
    size_t vm_data_kb;

    size_t glibc_arena_bytes;
    size_t glibc_used_bytes;
    size_t glibc_free_bytes;
    size_t glibc_mmap_bytes;
} Phase9_ProcessMemoryUsage;
```

The API is:

```c
int Phase9_ProcessMemory_GetUsage(
    Phase9_ProcessMemoryUsage *usage);
```

The implementation reads `/proc/self/status` for Linux process metrics and calls `mallinfo2()` for allocator statistics.

No generated AUTOSAR source or Trampoline source is modified by this component.

### Runtime Validation

#### Initial allocator validation

A direct `mallinfo2()` experiment in the Virtual AUTOSAR process produced:

```text
arena     = 135168 B
uordblks  =   1040 B
fordblks  = 134128 B
hblkhd    =      0 B
```

This established that the allocator interface works in the target Linux runtime.

#### Integrated process-memory snapshot

The project-owned API was then called from a temporary bounded runtime probe.

Observed example:

```text
VmRSS  = 3124 kB
VmHWM  = 3124 kB
VmSize = 70248 kB
VmData = 66012 kB

glibc arena = 135168 B
glibc used  =   8112 B
glibc free  = 127056 B
glibc mmap  =      0 B
```

The large difference between `VmData` and `glibc_used` demonstrates why these values must not be treated as equivalent heap measurements.

#### Time-separated snapshots

Two runtime snapshots were taken at different App_Task activations.

Snapshot #1:

```text
VmRSS       = 3060 kB
VmHWM       = 3060 kB
VmSize      = 70248 kB
VmData      = 66012 kB
glibc_used  = 8112 B
glibc_free  = 127056 B
```

Snapshot #3:

```text
VmRSS       = 3188 kB
VmHWM       = 3188 kB
VmSize      = 70248 kB
VmData      = 66012 kB
glibc_used  = 8112 B
glibc_free  = 127056 B
```

Observed change:

```text
VmRSS  : +128 kB
VmHWM  : +128 kB
VmSize : unchanged
VmData : unchanged
glibc allocator used/free : unchanged
```

This demonstrated that process RSS behavior and glibc allocator statistics are distinct observation domains.

`VmHWM` also behaved as the process resident-memory high-water metric during the experiment.

### Temporary Probe Cleanup

All Phase 9.3 experimental calls were removed from `task_impl.c`.

The final App_Task returned to:

```c
TASK(App_Task)
{
    VirtualAswc_Run();

    TerminateTask();
}
```

The permanent Phase 9.3 implementation consists only of:

```text
platform/autosar/ProcessMemoryMonitor.c
platform/autosar/ProcessMemoryMonitor.h
CMakeLists.txt source registration
```

There is no periodic `/proc` parsing, `mallinfo2()` call, or diagnostic memory `printf()` in the normal AUTOSAR task path.

### Golden Regression

#### Build and linkage

Clean generation/build completed successfully.

Executable linkage confirmed:

```text
Phase9_ProcessMemory_GetUsage
Phase9_StackMonitor_GetUsage
Phase9_StackMonitor_Init
```

Observed symbols:

```text
0000000000055358 T Phase9_ProcessMemory_GetUsage
000000000005518c T Phase9_StackMonitor_GetUsage
00000000000550dd T Phase9_StackMonitor_Init
```

Result:

```text
Build / linkage : PASS
```

#### Runtime

The cleaned build executed normally after removal of all Phase 9.3 probes.

Existing Virtual AUTOSAR scheduling and runtime behavior remained operational.

Result:

```text
AUTOSAR runtime : PASS
```

### Measurement Semantics

The following terminology is authoritative for Phase 9.3:

```text
VmRSS  = Linux process resident memory
VmHWM  = Linux process peak resident memory
VmSize = Linux process virtual address-space size
VmData = Linux data mapping observation
```

and:

```text
arena / uordblks / fordblks / hblkhd
    = glibc allocator statistics
```

Do not describe:

```text
VmData as exact heap usage
glibc statistics as physical ECU heap usage
Linux process memory as ECU RAM
HeapAdapter activity as complete DDS allocation accounting
```

DDS/PSL/PIL memory is included in the overall process where applicable, but component-specific allocation attribution remains limited.

### Architecture Impact

Phase 9.3 does not change:

- AUTOSAR task priorities,
- task activation behavior,
- alarms,
- resources,
- DDS transport,
- TcpIp polling,
- RTE behavior,
- DDS CDD behavior,
- Trampoline scheduling,
- generated AUTOSAR code.

The monitor is a project-owned observation API only.

### Limitations

1. `/proc/self/status` is Linux-specific.
2. `mallinfo2()` reports glibc allocator state, not physical ECU memory.
3. `VmData` is not an exact heap metric.
4. RSS can change without a corresponding change in `mallinfo2()` allocator usage.
5. DDS-specific allocation attribution is not provided.
6. HeapAdapter coverage is not proven to represent all DDS/PSL/PIL allocations.
7. Phase 9.3 provides snapshot primitives; runtime presentation and integration belong to Phase 9.4.
8. Threshold and warning policy belongs to Phase 9.5.

### PASS Criteria

| Criterion | Result |
|-----------|--------|
| Linux process-memory fields available | PASS |
| `mallinfo2()` available | PASS |
| `mallinfo2()` validated in actual runtime | PASS |
| Project-owned process-memory API implemented | PASS |
| VmRSS observation | PASS |
| VmHWM observation | PASS |
| VmSize observation | PASS |
| VmData observation | PASS |
| glibc allocator observation | PASS |
| Time-separated snapshots demonstrated | PASS |
| Process and allocator semantics separated | PASS |
| Temporary task probes removed | PASS |
| No generated-source modification | PASS |
| No new Trampoline modification | PASS |
| Clean build/linkage | PASS |
| Runtime regression | PASS |

### Final Result

```text
PHASE 9.3: COMPLETE

STATUS: PASS
```

Phase 9.3 provides a bounded Linux process-memory and glibc allocator snapshot capability while preserving the Golden Virtual AUTOSAR architecture.

The next planned subphase is:

```text
Phase 9.4 - Runtime Monitor Integration
```

## Phase 9.4 - Runtime Monitor Integration

### Final Status

```text
PHASE 9.4: COMPLETE
STATUS: PASS
```

Phase 9.4 integrated the Phase 9 task-stack and Linux process-memory observations with the existing Phase 8 runtime monitor while preserving the Golden trace format and existing CLI behavior.

### Objective

Integrate the memory-monitoring capabilities established in Phase 9.2 and Phase 9.3 with the existing project-owned runtime monitor.

The integration must:

- preserve `trace.json`,
- preserve existing Phase 8 trace decoding,
- keep memory observations separate from Trampoline trace records,
- resolve task names through generated static metadata rather than hardcoded names,
- make memory input optional,
- validate memory snapshot consistency,
- avoid permanent file I/O in AUTOSAR task execution paths.

### Final Architecture

```text
trace.json ----------------------+
                                 |
tpl_static_info.json ------------+--> runtime_monitor.py
  |                              |       |
  +-- task ID -> task name       |       +-- Scheduling / OS view
                                 |       +-- Memory view
memory_snapshot.json ------------+
  +-- task stack high-water
  +-- Linux process memory
  +-- glibc allocator statistics
```

Memory data is deliberately not embedded into `trace.json`.

### Task Metadata Mapping

Generated static information was confirmed to contain:

```text
id=0 DdsCddProcessData_Task  priority=2 stack=32768
id=1 DdsCddReadWrite_Task    priority=4 stack=32768
id=2 RTI_Task                priority=6 stack=32768
id=3 App_Task                priority=3 stack=32768
id=4 DdsCddTimerTick_Task    priority=5 stack=32768
id=5 TcpIp_Task              priority=8 stack=32768
```

The same task ID indexes the Trampoline process table used by the stack monitor.

Therefore the memory snapshot stores task IDs rather than task names. `runtime_monitor.py` resolves names through the existing `StaticInfo.task_name()` mechanism.

This avoids hardcoding the current application task names into the memory-monitoring format.

### Memory Snapshot Schema

Phase 9.4 defines:

```text
schema = phase9-memory-v1
```

Example structure:

```json
{
  "schema": "phase9-memory-v1",
  "task_stack": [
    {
      "task_id": 0,
      "allocated_bytes": 32768,
      "used_high_water_bytes": 3576,
      "free_high_water_bytes": 29192
    }
  ],
  "process": {
    "vm_rss_kb": 3108,
    "vm_hwm_kb": 3108,
    "vm_size_kb": 70248,
    "vm_data_kb": 66012
  },
  "glibc": {
    "arena_bytes": 135168,
    "used_bytes": 8112,
    "free_bytes": 127056,
    "mmap_bytes": 0
  }
}
```

### Snapshot Exporter

Phase 9.4 adds:

```text
platform/autosar/MemorySnapshot.h
platform/autosar/MemorySnapshot.c
```

Public API:

```c
int Phase9_MemorySnapshot_WriteJson(
    const char *path);
```

The exporter combines:

```text
Phase9_StackMonitor_GetUsage()
Phase9_ProcessMemory_GetUsage()
```

and emits one bounded JSON snapshot.

The exporter does not contain application-specific task names.

### Snapshot Runtime Validation

A temporary one-shot App_Task probe was used only to validate the exporter.

The runtime successfully generated:

```text
memory_snapshot.json
```

with all six configured tasks.

Observed task-stack values:

```text
DdsCddProcessData_Task allocated=32768 used=3576 free=29192
DdsCddReadWrite_Task   allocated=32768 used=6856 free=25912
RTI_Task               allocated=32768 used=7080 free=25688
App_Task               allocated=32768 used=4568 free=28200
DdsCddTimerTick_Task   allocated=32768 used=3904 free=28864
TcpIp_Task             allocated=32768 used=9792 free=22976
```

For all six tasks:

```text
allocated_bytes =
    used_high_water_bytes +
    free_high_water_bytes
```

Observed process snapshot:

```text
VmRSS  = 3108 kB
VmHWM  = 3108 kB
VmSize = 70248 kB
VmData = 66012 kB
```

Observed glibc allocator snapshot:

```text
arena = 135168 bytes
used  =   8112 bytes
free  = 127056 bytes
mmap  =      0 bytes
```

The generated file was successfully parsed with Python `json.load()`.

### Temporary Runtime Probe Cleanup

The one-shot snapshot call was removed after validation.

Final `App_Task` returned to:

```c
TASK(App_Task)
{
    VirtualAswc_Run();

    TerminateTask();
}
```

No permanent Phase 9.4 JSON file I/O remains in App_Task, RTI_Task, ErrorHook, scheduler hooks, or other AUTOSAR task execution paths.

### Runtime Monitor Integration

`tools/runtime_monitor/runtime_monitor.py` now supports an optional argument:

```text
--memory <memory_snapshot.json>
```

Existing usage remains valid:

```bash
python3 tools/runtime_monitor/runtime_monitor.py \
    trace.json \
    --static-info autosar_virtual/tpl_static_info.json \
    --derived \
    --limit 100
```

Memory-enabled usage:

```bash
python3 tools/runtime_monitor/runtime_monitor.py \
    trace.json \
    --static-info autosar_virtual/tpl_static_info.json \
    --memory memory_snapshot.json \
    --derived \
    --limit 100
```

The memory view contains:

```text
MEMORY
  TASK_STACK
  PROCESS
  GLIBC
```

Task names are resolved through generated static metadata.

### Memory Snapshot Validation

The monitor validates the snapshot before displaying it.

Validation includes:

```text
schema == phase9-memory-v1
task_id is within generated task range
allocated_bytes == used_high_water_bytes + free_high_water_bytes
required process-memory fields exist
required glibc allocator fields exist
```

Required process fields:

```text
vm_rss_kb
vm_hwm_kb
vm_size_kb
vm_data_kb
```

Required glibc fields:

```text
arena_bytes
used_bytes
free_bytes
mmap_bytes
```

#### Positive Validation

The real runtime-generated snapshot passed all validation and was displayed successfully.

Result:

```text
PASS
```

#### Negative Validation

A temporary invalid snapshot was generated with:

```text
task_id = 99
```

The runtime monitor rejected it with:

```text
ValueError: invalid memory task_id: 99
```

Result:

```text
INVALID INPUT REJECTION: PASS
```

### Phase 8 Backward Compatibility

The original Phase 8 command was tested without `--memory`.

Observed:

```text
SUMMARY raw_records=25766
derived_records=25766
parser_warnings=1
trace_incomplete=yes
```

No memory section was printed.

The `trace_incomplete=yes` result is the existing accepted Ctrl+C/truncated-trace behavior and is not a Phase 9.4 regression.

Result:

```text
PHASE 8 CLI COMPATIBILITY: PASS
```

### Integrated Monitor Validation

The same trace was then processed with the memory snapshot enabled.

Observed output included:

```text
MEMORY
  TASK_STACK
    DdsCddProcessData_Task allocated=32768 used=3576 free=29192
    DdsCddReadWrite_Task allocated=32768 used=6856 free=25912
    RTI_Task allocated=32768 used=7080 free=25688
    App_Task allocated=32768 used=4568 free=28200
    DdsCddTimerTick_Task allocated=32768 used=3904 free=28864
    TcpIp_Task allocated=32768 used=9792 free=22976

  PROCESS
    VmRSS=3108 kB
    VmHWM=3108 kB
    VmSize=70248 kB
    VmData=66012 kB

  GLIBC
    arena=135168 bytes
    used=8112 bytes
    free=127056 bytes
    mmap=0 bytes
```

Result:

```text
TRACE + MEMORY INTEGRATION: PASS
```

### Golden Regression

Clean generation/build completed successfully.

Linked symbols:

```text
Phase9_MemorySnapshot_WriteJson
Phase9_ProcessMemory_GetUsage
Phase9_StackMonitor_GetUsage
Phase9_StackMonitor_Init
```

Observed:

```text
0000000000055513 T Phase9_MemorySnapshot_WriteJson
0000000000055358 T Phase9_ProcessMemory_GetUsage
000000000005518c T Phase9_StackMonitor_GetUsage
00000000000550dd T Phase9_StackMonitor_Init
```

Python syntax validation:

```text
python3 -m py_compile tools/runtime_monitor/runtime_monitor.py
PASS
```

Phase 8 trace decoding remained operational.

Phase 9 memory integration remained operational.

The Virtual AUTOSAR runtime was reported normal after the Phase 9.4 changes.

### Measurement Semantics

The Phase 9.2 and Phase 9.3 semantic boundaries remain unchanged.

#### Task Stack

```text
Trampoline POSIX AUTOSAR Task Stack High-Water
```

It is not claimed to be exact physical MCU task-stack behavior.

#### Process Memory

```text
VmRSS  = Linux process resident memory
VmHWM  = Linux process peak resident memory
VmSize = Linux process virtual address-space size
VmData = Linux data mapping observation
```

`VmData` is not exact heap usage.

#### glibc Allocator

```text
arena / used / free / mmap
    = glibc allocator statistics
```

These values are not physical ECU heap usage.

### Design Constraints Preserved

Phase 9.4 does not modify:

- task priorities,
- task activation semantics,
- alarms,
- AUTOSAR resources,
- DDS transport,
- TcpIp polling,
- RTE behavior,
- DDS CDD behavior,
- Trampoline scheduling,
- Phase 8 trace format.

The existing project Golden Trampoline POSIX 1 ms timer dependency is unchanged.

No additional Trampoline modification was introduced.

### Repository State at Validation

Phase 9.4-related working-tree changes included:

```text
M  CMakeLists.txt
M  tools/runtime_monitor/runtime_monitor.py
?? platform/autosar/MemorySnapshot.c
?? platform/autosar/MemorySnapshot.h
?? memory_snapshot.json
```

The existing:

```text
m third_party/trampoline
```

is the pre-existing Golden Trampoline POSIX 1 ms timer modification and is not a Phase 9.4 change.

`memory_snapshot.json` is a generated runtime observation artifact. Its repository retention policy should be treated separately from the permanent source implementation.

### PASS Criteria

| Criterion | Result |
|-----------|--------|
| Separate memory snapshot format | PASS |
| Trace format unchanged | PASS |
| Task IDs mapped through generated metadata | PASS |
| No hardcoded application task names in snapshot | PASS |
| Task-stack snapshot export | PASS |
| Process-memory snapshot export | PASS |
| glibc allocator snapshot export | PASS |
| JSON serialization | PASS |
| JSON parsing | PASS |
| Optional `--memory` CLI | PASS |
| Existing Phase 8 CLI preserved | PASS |
| Memory report integrated | PASS |
| Valid snapshot accepted | PASS |
| Invalid task ID rejected | PASS |
| Stack consistency validation | PASS |
| Required process fields validated | PASS |
| Required glibc fields validated | PASS |
| Temporary App_Task probe removed | PASS |
| No permanent AUTOSAR task file I/O | PASS |
| Clean build/linkage | PASS |
| Python syntax validation | PASS |
| Runtime regression | PASS |

### Final Result

```text
PHASE 9.4: COMPLETE

STATUS: PASS / GOLDEN
```

Phase 9.4 establishes the unified project runtime-monitor interface for AUTOSAR scheduling traces and Phase 9 memory observations without changing the Golden scheduling or trace architecture.

The next planned subphase is:

```text
Phase 9.5 - Threshold / Warning Model
```

## Final Phase 9 status

```text
PHASE 9.1: COMPLETE / PASS
PHASE 9.2: COMPLETE / PASS
PHASE 9.3: COMPLETE / PASS
PHASE 9.4: COMPLETE / PASS
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
