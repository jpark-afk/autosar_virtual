# Phase 8 - AUTOSAR Trace / Runtime Monitor

## Status

```text
Phase 0  Environment / ABI                              PASS
Phase 1  Trampoline POSIX AUTOSAR OS                    PASS
Phase 2  RTI AUTOSAR PSL / PIL integration              PASS
Phase 3  Real DDS over Virtual AUTOSAR TcpIp             GOLDEN
Phase 4  Minimal Generated RTE                           PASS
Phase 5  RTE / ASWC scope resolution                     COMPLETE / ABSORBED
Phase 6  Generated CDD task integration                  PASS / GOLDEN
Phase 7  OS robustness / Error / Resource                PASS
Phase 8  AUTOSAR Trace / Runtime Monitor                 ACTIVE
```

Phase 8 is active. Phase 8.1, Phase 8.2, and Phase 8.3 have completed and
passed. No project-owned runtime tracing source or custom trace format has
been added.

## Objective

Establish a bounded, low-intrusion observation mechanism for the existing
Trampoline POSIX AUTOSAR runtime.

The monitor must observe Trampoline-owned behavior without replacing:

```text
task scheduling
task activation and dispatch
resource ownership and priority ceilings
event handling
alarm processing
generated RTE/CDD semantics
DDS transport behavior
```

The initial target is a reliable logical trace. A visualization backend such
as Perfetto is out of scope until the underlying runtime events and storage
path are proven.

## Frozen Golden Baseline

The Phase 3-7 runtime remains the protected baseline:

```text
Windows DDS Host
        <-> UDP / RTPS
Virtual AUTOSAR TcpIp
        <-> Trampoline POSIX AUTOSAR OS
        <-> RTI AUTOSAR PSL / PIL
        <-> DDS CDD / generated RTE / CDD Tasks
```

Phase 8 must not change DDS transport properties, socket architecture, task
priorities, production DDS resources, generated RTE semantics, or Trampoline
scheduling semantics merely to make tracing easier.

## Phase 8.1 Investigation

### Investigation goal

Determine what the checked-out Trampoline revision already provides for:

```text
process/task state transitions
resource state transitions
event set/reset
alarm/time-object state and expiration
timestamps
trace storage and output format
POSIX backend integration
decoder or viewer tooling
```

### OIL configuration evidence

The authoritative OIL configuration contains:

```text
TRACE = TRUE {
    FORMAT = json;
    PROC = TRUE;
};
```

The configuration is in:

```text
config/os/autosar_virtual.oil
```

GOIL generated the corresponding trace configuration:

```text
#define WITH_TRACE YES
#define WITH_ID YES
#define TRACE_PROC YES
#define TRACE_RES YES
#define TRACE_EVENT YES
#define TRACE_ALARM YES
#define TRACE_MESSAGE YES
#define TRACE_IOC NO
#define TRACE_FORMAT TRACE_FORMAT_JSON
```

The generated `autosar_virtual/tpl_static_info.json` provides static mappings
for process, resource, alarm/time-object, event, and state identifiers.

### Trampoline API evidence

The checked-out Trampoline source contains the trace interface:

```text
third_party/trampoline/os/tpl_trace.h
```

The interface declares hooks for:

```text
process state changes
resource state changes
time-object state changes
time-object expiration
event set/reset
IOC send/receive
message send/receive
```

The kernel sources include and invoke these hooks from process scheduling,
resource, event, alarm/time-object, and interrupt-related paths. The POSIX path
is:

```text
AUTOSAR OS operation -> Trampoline kernel -> TRACE_* -> tpl_trace_*
        -> machines/posix/tpl_trace.c -> trace.json
```

The trace abstraction is therefore located at the authoritative Trampoline
kernel boundary, not in application-level scheduling code.

### Current interpretation

The confirmed process state values are:

```text
0 SUSPENDED
1 READY
2 RUNNING
3 WAITING
4 AUTOSTART
5 READY_AND_NEW
```

Relevant kernel transitions are:

```text
activation/new instance  -> READY_AND_NEW
dispatch                 -> RUNNING
preemption               -> READY
resume                   -> RUNNING
WaitEvent                -> WAITING
termination              -> SUSPENDED or READY_AND_NEW
```

`READY_AND_NEW` remains a raw Trampoline state and is not renamed to a
synthetic `ACTIVATE` event. Higher-level activation, preemption, and
resumption interpretation must remain monitor-derived.

Resource states are `FREE = 0` and `TAKEN = 1`. Resource acquisition/release,
event set/reset, and alarm/time-object state/expiration are observable through
dedicated kernel hooks.

## Implementation / Change

No project source, generated file, OIL configuration, or Trampoline submodule
source was changed during this initial investigation.

No custom scheduler state machine, printf instrumentation, ErrorHook writer,
Perfetto integration, or trace decoder has been added.

## Observed Evidence

Confirmed from the repository and unchanged Golden runtime:

```text
TRACE = TRUE with JSON format and process tracing enabled
tpl_trace.h exists in the checked-out Trampoline source
process trace hooks are called from kernel scheduling paths
resource trace hooks are called from resource acquisition/release paths
event trace hooks are called from event paths
alarm/time-object trace hooks are called from timing paths
POSIX trace backend writes runtime JSON records to trace.json
the Golden runtime produced approximately 999 KB and 76,604 trace lines
runtime records include proc, resource, and timeobj_expire events
TraceReader.py, TraceEvaluate.py, StaticInfo.py, and TraceAnalysis.py exist
```

The POSIX JSON output is not directly compatible with the generic evaluator in
all places:

```text
POSIX emits res_id while the evaluator expects resource_id
POSIX emits timeobj_expire, set_event, and reset_event types
the generic evaluator expects normalized timeobj/event records with kind
```

The generic static metadata and evaluator architecture remains reusable, but a
project-owned normalization layer is required for direct POSIX JSON decoding.

Trace timestamps come from the first AUTOSAR counter's `current_date`. They are
AUTOSAR/SystemCounter time, not Linux wall-clock or `CLOCK_MONOTONIC` time.

`ShutdownOS()` closes the JSON trace through `TRACE_CLOSE()`. External process
termination or Ctrl+C may leave the final JSON record incomplete.

## Phase 8.2 - Existing Trace Capture Baseline

### Status

```text
PHASE 8.2: COMPLETE
STATUS: PASS
```

### Objective

Establish a quantitative and behavioral baseline for the existing Trampoline
POSIX trace using the unchanged Virtual AUTOSAR Golden application.

The baseline covers:

```text
runtime trace volume and timestamp range
event-type distribution
process/task ID and state mapping
Basic Task lifecycle
Extended Task lifecycle
periodic alarm behavior
event wakeup behavior
resource activity
same-timestamp ordering
configured AUTOSAR behavior versus observed trace behavior
```

### Runtime Trace Baseline

The Golden application generated:

```text
~/autosar_virtual/trace.json
```

Observed baseline:

```text
trace size              approximately 31 MB
events_with_timestamp   411287
min_ts                  0
max_ts                  115320
span_ticks              115320
```

The timestamp is Trampoline AUTOSAR/SystemCounter time, not Linux wall-clock
time.

### Event Distribution

```text
185595  proc
167066  resource
 34826  timeobj_expire
 11911  set_event
 11889  reset_event
-------
411287  timestamped records
```

The Golden workload exercises all currently required trace categories:

```text
task/process scheduling
resource operations
alarm expiration
event setting
event resetting
```

### Process Mapping

`tpl_static_info.json` maps runtime process IDs as follows:

```text
0  DdsCddProcessData_Task
1  DdsCddReadWrite_Task
2  RTI_Task
3  App_Task
4  DdsCddTimerTick_Task
5  TcpIp_Task
6  idle
```

All process IDs from 0 through 6 appeared in the runtime trace. Observed
process-transition counts were:

```text
DdsCddProcessData_Task       729
DdsCddReadWrite_Task       34598
RTI_Task                       3
App_Task                     345
DdsCddTimerTick_Task       34596
TcpIp_Task                 69195
idle                       46129
```

### Process State Distribution

The Phase 8.1 state mapping is:

```text
0 = SUSPENDED
1 = READY
2 = RUNNING
3 = WAITING
4 = AUTOSTART
5 = READY_AND_NEW
```

Observed state-transition counts were:

```text
SUSPENDED       34713
READY           34838
RUNNING         69553
WAITING         11775
READY_AND_NEW   34716
```

All runtime states required for logical scheduling analysis were observed.
`AUTOSTART` is an internal configuration/state constant and did not appear as
a runtime process transition in this baseline.

### Basic and Extended Task Lifecycle

`TcpIp_Task` demonstrated the repeating Basic Task lifecycle:

```text
READY_AND_NEW -> RUNNING -> SUSPENDED
```

The sequence was observed at timestamps 0, 5, 10, and 15, confirming the
configured 5-tick periodic activation. `DdsCddTimerTick_Task` showed the same
Basic Task pattern at timestamps 10, 20, and 30, confirming the configured
10-tick periodic activation. `App_Task` showed 115 occurrences each of
`READY_AND_NEW`, `RUNNING`, and `SUSPENDED`.

`DdsCddReadWrite_Task` demonstrated the Extended Task model:

```text
initial:  READY_AND_NEW -> RUNNING -> WAITING
periodic: READY -> RUNNING -> WAITING
```

The initial transition occurred at timestamp 0, 3, and 3. Subsequent periodic
wakeups showed `READY`, `RUNNING`, and `WAITING` at timestamps 10, 20, and
later ticks. This distinguishes event-driven Extended Task execution from
Basic Task termination.

### Scope and Interpretation

Phase 8.2 introduced no custom trace format or runtime monitor. It did not
modify:

```text
Trampoline source
generated RTE/CDD behavior
DDS transport configuration
task priorities
AUTOSAR OS scheduling behavior
```

The baseline proves that the existing trace contains sufficient real workload
data for the next project-owned decoder/normalization step. Same-timestamp
ordering and state sequences remain trace-derived; higher-level lifecycle
labels are monitor interpretations rather than replacement kernel events.

## Phase 8.3 - Task Lifecycle and Scheduling Observation

### Status

```text
PHASE 8.3: COMPLETE
STATUS: PASS
```

### Objective and Scope

Phase 8.3 validated how the existing Trampoline process trace represents
AUTOSAR task lifecycle and scheduling behavior. The validation covered:

```text
task activation and creation of a new instance
initial dispatch
task termination
Extended Task waiting
event-driven wakeup
application-task preemption
task resumption after preemption
```

No Trampoline source modification was required. DDS transport configuration,
production task priorities and resources, generated RTE semantics, and the
Virtual AUTOSAR communication architecture remained unchanged.

### Raw Trace Model

The POSIX trace records process state transitions rather than synthetic events
such as `ACTIVATE`, `DISPATCH`, `PREEMPT`, `RESUME`, `TERMINATE`, or `WAKEUP`.
The relevant raw states are:

```text
SUSPENDED     = 0
READY         = 1
RUNNING       = 2
WAITING       = 3
READY_AND_NEW = 5
```

The raw trace remains authoritative. Lifecycle events are derived only from
ordered state history and must remain distinct from raw kernel records.

### Golden Extended Task Lifecycle

The Golden `DdsCddReadWrite_Task` showed the initial lifecycle:

```text
ts=0  READY_AND_NEW
ts=2  RUNNING
ts=2  WAITING
```

This proves that activation and initial dispatch are distinct. `READY_AND_NEW`
means that a new task instance became ready; the later `RUNNING` record proves
that it was dispatched.

After waiting, the task repeatedly showed:

```text
ts=10  READY
ts=10  RUNNING
ts=10  WAITING

ts=20  READY
ts=20  RUNNING
ts=20  WAITING

ts=30  READY
ts=30  RUNNING
ts=30  WAITING
```

This validates the event-driven lifecycle:

```text
WAITING -> READY -> RUNNING -> WAITING
```

`WAITING -> READY` represents wakeup in this surrounding trace context, while
`READY -> RUNNING` represents dispatch after wakeup.

### Controlled Application Preemption

The Golden workload did not naturally produce application-task preemption. A
temporary project-owned higher-priority `Phase8_PreemptTask` was therefore used
while `App_Task` remained the lower-priority task. No production DDS task
priority or resource was changed or reused.

Generated static information confirmed the relative priority:

```text
App_Task               generated priority = 3
Phase8_PreemptTask     generated priority = 5
App_Task < Phase8_PreemptTask
```

Both tasks used `SCHEDULE = FULL`. The controlled trace contained:

```text
ts=1000  App_Task           -> READY_AND_NEW
ts=1000  App_Task           -> RUNNING
ts=1000  Phase8_PreemptTask -> READY_AND_NEW
ts=1000  App_Task           -> READY
ts=1000  Phase8_PreemptTask -> RUNNING
ts=1000  Phase8_PreemptTask -> SUSPENDED
ts=1000  App_Task           -> RUNNING
ts=1000  App_Task           -> SUSPENDED
```

This directly validates:

```text
RUNNING -> READY -> RUNNING
        preemption followed by resumption
```

### Context-Sensitive READY Interpretation

`READY` cannot be interpreted independently. Two observed paths have different
meanings:

```text
WAITING -> READY -> RUNNING
        wakeup followed by dispatch

RUNNING -> READY -> RUNNING
        preemption followed by resumption
```

Therefore `READY -> RUNNING` must not automatically be labeled `RESUME`. A
decoder must retain each process's preceding state history.

### Validated Lifecycle Rules

```text
READY_AND_NEW
        New task instance became ready.

READY_AND_NEW -> RUNNING
        Initial dispatch.

RUNNING -> SUSPENDED
        Task instance terminated.

RUNNING -> WAITING
        Extended Task entered the waiting state.

WAITING -> READY
        Waiting task became ready.

WAITING -> READY -> RUNNING
        Wakeup followed by dispatch.

RUNNING -> READY
        Running task was preempted.

RUNNING -> READY -> RUNNING
        Preemption followed by resumption.
```

These are monitor-derived interpretations and do not replace the raw
Trampoline state records.

### Timestamp Ordering

Multiple scheduler events can share one SystemCounter timestamp. The complete
preemption sequence occurred at `ts=1000`, including activation, preemption,
dispatch, termination, resumption, and final termination.

The monitor must preserve original trace record order for equal timestamps.
Sorting records solely by timestamp can destroy scheduling semantics.

### Test Isolation and Restoration

The temporary `Phase8_PreemptTask` and its temporary activation call were
removed after validation. `App_Task` was restored to its Golden behavior:

```c
TASK(App_Task)
{
        VirtualAswc_Run();
        TerminateTask();
}
```

The project was regenerated and rebuilt after cleanup. No remaining
`Phase8_PreemptTask` reference was found in the inspected project configuration
or source. Production DDS resources remained unchanged:

```text
OsResource_DdsMain
OsResource_DdsTimer
OsResource_DdsNetio
```

## Limitations

The investigation does not establish direct compatibility between POSIX JSON
and the generic evaluator. The following limitations remain:

```text
POSIX JSON requires project-owned normalization for generic evaluation
external termination can truncate the final JSON record
task activation, preemption, and resumption are monitor-derived interpretations
timestamps represent AUTOSAR counter time rather than host time
```

No event should be invented until its Trampoline source path and emitted
representation are established. Monitor-derived states must remain distinct
from kernel-reported events.

## Phase 8.1 PASS Criteria

Phase 8.1 passes only when the actual checked-out implementation documents:

```text
trace generation path
trace event types
task/process state capabilities
resource capabilities
event capabilities
alarm capabilities
timestamp mechanism
storage/output format
available decoder/tooling
POSIX-specific limitations
```

The result may document unsupported capabilities. Unsupported behavior must be
recorded as a limitation rather than synthesized by application code.

## Current Conclusion

```text
PHASE 8: ACTIVE
PHASE 8.1: COMPLETE
PHASE 8.2: COMPLETE
PHASE 8.3: COMPLETE
STATUS: PASS
```

The existing Trampoline POSIX trace path is operational. It generates
timestamped JSON records for process, resource, event, and time-object activity
and provides static object mappings through `tpl_static_info.json`. Phase 8.2
established a 31 MB Golden workload baseline with 411,287 timestamped records,
all required trace categories, and distinguishable Basic/Extended Task
lifecycle behavior. Phase 8.3 established context-sensitive lifecycle rules
for activation, dispatch, waiting, wakeup, preemption, resumption, and
termination while preserving equal-timestamp record order. The next Phase 8
experiment is a project-owned capture/normalization or decoder layer for the
existing `trace.json` output. The POSIX JSON schema mismatch and
external-termination truncation behavior remain documented limitations.

Phase 9 and later work remain out of scope.