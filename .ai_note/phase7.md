# Phase 7 - OS Robustness / Error / Resource

Use this document as the starting context and prompt for the next Phase 7
conversation in `/home/jpark/autosar_virtual`.

Read this file and `.ai_note/overview.md` before changing anything. Also read
the relevant completed phase notes when a dependency is involved. Do not
restart Phase 0-6 investigations without new evidence.

## Status

```text
Phase 0  Environment / ABI                              PASS
Phase 1  Trampoline POSIX AUTOSAR OS                    PASS
Phase 2  RTI AUTOSAR PSL / PIL integration              PASS
Phase 3  Real DDS over Virtual AUTOSAR TcpIp             GOLDEN
Phase 4  Minimal Generated RTE                           PASS
Phase 5  RTE / ASWC scope resolution                     COMPLETE / ABSORBED
Phase 6  Generated CDD task integration                  PASS / GOLDEN
Phase 7  OS Robustness / Error / Resource                NEXT
Phase 8  AUTOSAR Trace / Runtime Monitor                 PLANNED
Phase 9  Stack / Heap / Memory Monitoring                PLANNED
Phase 10 Stress / Fault Injection                        PLANNED
Phase 11 Integrated DdsCdd / DDS Validation              PLANNED
Phase 12 Final Virtual ECU Test Bench                     PLANNED
Phase 13 Documentation / Reproducibility / Release        PLANNED
```

Phases 4 through 6 are one completed RTE automation body of work. Phase 7 is
the first OS robustness phase after that work.

## Mission

Validate the existing Trampoline POSIX AUTOSAR OS behavior for errors,
activation limits, resources, and priority ceiling without replacing or
simulating Trampoline semantics.

Phase 7 must add only the minimum project-owned observation and test control
needed to prove the behavior.

Ownership:

```text
Task scheduling                 [TRAMPOLINE]
Activation limits / E_OS_LIMIT  [TRAMPOLINE]
Events and service validation   [TRAMPOLINE]
Resources / priority ceiling    [TRAMPOLINE]
ErrorHook invocation            [TRAMPOLINE]
Error recording / summaries     [CUSTOM]
Linux process and timing host    [LINUX]
DDS CDD / PIL / PSL              [EXISTING]
```

Never reimplement a Trampoline feature in application code merely because it
is easier to instrument.

## Frozen Golden Baseline

Preserve this working path:

```text
Windows DDS Host 192.168.56.1
  <-> UDP / RTPS
Ubuntu VM 192.168.56.105/enp0s8
  <-> Virtual AUTOSAR TcpIp
  <-> Trampoline POSIX AUTOSAR OS
  <-> RTI AUTOSAR PSL / PIL
  <-> DDS CDD
  <-> Generated Minimal RTE and CDD Tasks
  <-> Mock ASWC
```

Verified baseline facts:

- DDS receive sockets bind on UDP 8910 and 8911.
- Windows and Linux exchange DDS samples in both directions.
- `TcpIp_Task` polls retained nonblocking DDS sockets every 5 ms.
- `TcpIp_Task` priority is 10 and owns `OsResource_DdsNetio` and
  `OsResource_DdsMain`.
- RTI mutex, timer, and NETIO resources map to `OsResource_DdsMain`,
  `OsResource_DdsTimer`, and `OsResource_DdsNetio`.
- Generated RTE and generated CDD task integration are Golden.

Do not change DDS transport properties, receive buffers, sockets, task
priorities, generated RTE semantics, or the TcpIp architecture unless a Phase 7
test proves that a narrowly scoped compatibility fix is required.

## Current OS Configuration

The authoritative OIL file is:

```text
config/os/autosar_virtual.oil
```

Current relevant facts:

```text
STATUS = EXTENDED
TRACE = TRUE
all current Tasks use ACTIVATION = 1
all current Tasks use SCHEDULE = FULL
```

Current resources:

```text
DummyResource
OsResource_DdsMain
OsResource_DdsTimer
OsResource_DdsNetio
```

Current task/resource relationships must be reviewed before adding any test
resource. DDS resources are production integration resources and must not be
repurposed for destructive tests.

At Phase 7 start, no dedicated project-owned `ErrorHook` or OS robustness
monitor was identified in the main project sources. Confirm this locally
before implementation. Do not infer support only from generated files or stale
build output.

`TRACE = TRUE` is an existing Trampoline trace setting. It does not mean that
Phase 8 AUTOSAR Trace / Runtime Monitor is complete, and Phase 7 must not expand
into Phase 8.

## Phase 7 Scope

Required behavior to validate:

```text
ErrorHook
E_OS_LIMIT from activation overflow
recoverable execution after ErrorHook returns
resource acquisition and release
nested resources
priority ceiling behavior
invalid resource ordering or ownership where Trampoline checks it
representative E_OS_RESOURCE / E_OS_STATE / E_OS_VALUE behavior where supported
```

Keep fatal and recoverable conditions distinct. Do not force execution to
continue after a condition that leaves kernel state unsafe.

Out of scope for Phase 7:

```text
stack usage and overflow instrumentation       Phase 9
heap accounting and limits                     Phase 9
Perfetto backend and full logical trace         Phase 8
stress campaigns and traffic bursts             Phase 10
full final DDS regression matrix                 Phase 11
```

A small DDS regression is still required after Phase 7 changes to prove that
the Golden communication baseline was not damaged.

## Implementation Strategy

Use a project-owned, compile-time-selectable Phase 7 test mode or equivalent
isolated mechanism. Normal production/GOLDEN behavior must remain the default.
Do not inject activation overflow or invalid resource operations into the
normal DDS task path.

Preferred separation:

```text
normal build/run
  -> unchanged Golden Virtual ECU behavior

Phase 7 test scenario
  -> dedicated test Task/Alarm/Resource
  -> one controlled OS error or resource case
  -> small observation record
  -> deterministic PASS/FAIL output
  -> clean shutdown when safe
```

Do not create a general test framework. Add only the support required by the
current scenario.

ErrorHook must perform bounded work:

```text
ErrorHook(StatusType error)
  -> capture error code and available service context
  -> increment fixed counters or append to a fixed ring buffer
  -> return
```

Do not allocate memory, block, perform socket I/O, or emit high-volume output
inside ErrorHook.

## Ordered Work

### Phase 7.1 - Trampoline Capability and Hook Investigation

Investigation only. Do not modify code in the first step.

Determine from the checked-out Trampoline revision and generated application:

1. Exact OIL configuration required to enable `ErrorHook` on POSIX.
2. Exact `ErrorHook` signature and available service/error context APIs.
3. How `ActivateTask()` reports activation overflow with `ACTIVATION = 1`.
4. Which extended-status checks produce `E_OS_RESOURCE`, `E_OS_STATE`, and
   `E_OS_VALUE` on this target.
5. How resource ceilings are generated and represented internally.
6. Whether effective priority can be observed through a supported API or must
   be validated indirectly through dispatch order.
7. Which official Trampoline examples or tests are closest to each scenario.
8. Whether a separate OIL test configuration or compile-time mode is the
   smallest way to isolate robustness tests from the Golden DDS runtime.

Use actual source, headers, generated code, examples, and tests. Do not guess
API names or copy behavior from another OSEK implementation.

Phase 7.1 PASS criterion:

```text
A concise evidence-based mapping exists for:
scenario -> Trampoline API/check -> expected status -> hook context
and no project source has been modified.
```

After reporting the result, stop and select only the first implementation
scenario.

### Phase 7.2 - Minimal Error Monitor and ErrorHook

Add a fixed-size project-owned error record with no dynamic allocation.
Enable the Trampoline ErrorHook through the supported OIL configuration.

Minimum record:

```text
error code
service identifier when available
occurrence count
timestamp or counter tick only when safe and supported
scenario identifier
```

PASS criterion:

```text
A controlled recoverable OS error invokes ErrorHook exactly as expected,
the record is visible outside hook context, and normal OS execution continues.
```

### Phase 7.3 - Activation Limit / E_OS_LIMIT

Use a dedicated Basic Task configured with:

```text
ACTIVATION = 1
```

Trigger a second activation while the Task remains active. Do not overload an
existing DDS task for this test.

Validate:

```text
first activation accepted
second activation returns E_OS_LIMIT
ErrorHook observes E_OS_LIMIT
activation count/state are not fabricated by custom code
OS continues safely after the hook returns
```

PASS criterion:

```text
Console/test summary and monitor record agree on one intentional E_OS_LIMIT,
then the scenario terminates cleanly.
```

### Phase 7.4 - Resource and Priority Ceiling

Add dedicated test Tasks and Resources modeled after the intended relationship:

```text
TaskHigh       high priority
TaskProcess    medium priority
TaskStart      low priority
Resource_A
Resource_B
```

Validate actual Trampoline behavior for:

```text
GetResource(Resource_B)
nested GetResource(Resource_A)
reverse-order ReleaseResource(Resource_A)
ReleaseResource(Resource_B)
```

Prove priority ceiling through a supported Trampoline observation point or a
deterministic scheduling-order experiment. Do not implement an application
priority variable and call that proof.

PASS criterion:

```text
Resource ownership, nested release order, and observed scheduling behavior
match Trampoline's generated ceilings and OSEK/AUTOSAR semantics.
```

### Phase 7.5 - Resource and State Error Cases

Add one supported error case at a time, such as invalid release ownership or an
invalid service state. Reset or rebuild between scenarios if continuing after
the error is unsafe.

PASS criterion:

```text
Each enabled scenario has one expected status, one ErrorHook record, no
unexpected errors, and a documented safe termination behavior.
```

Do not manufacture unsupported status codes merely to fill a checklist.
Document target limitations when the POSIX target cannot expose a requested
case safely.

### Phase 7.6 - Golden Regression and Baseline

Disable the Phase 7 fault scenario and return to the normal configuration.
Run clean generation and build, then verify the normal Virtual ECU runtime.
Perform the smallest available DDS regression that confirms the Phase 3 Golden
path remains intact.

Create or finalize `.ai_note/phase7.md` as a verified baseline containing only:

```text
final architecture
verified Trampoline behavior
final OIL/configuration
scenario selection method
ErrorHook/monitor contract
commands and expected output
PASS evidence
limitations
Phase 8 starting point
```

Remove guesses, abandoned attempts, and temporary diagnostics.

## Phase 7 Overall PASS Criteria

```text
[PASS] Trampoline ErrorHook enabled and invoked by a real OS error
[PASS] activation overflow produces Trampoline E_OS_LIMIT
[PASS] ErrorHook records bounded data and returns safely
[PASS] normal scheduling continues after the recoverable test
[PASS] resource acquisition/release uses Trampoline APIs
[PASS] nested resource behavior is verified
[PASS] priority ceiling is verified without custom emulation
[PASS] supported resource/state errors are characterized
[PASS] normal clean generation/build succeeds
[PASS] Phase 3 DDS Golden behavior remains intact
```

## Files and Ownership

Likely project-owned files to inspect or change:

```text
config/os/autosar_virtual.oil
config/os/task_impl.c
platform/autosar/            optional small monitor module
CMakeLists.txt
build/run helper scripts     only if scenario selection requires it
.ai_note/phase7.md
```

Generated files under `autosar_virtual/` must not be hand-edited.

Do not directly modify or commit files inside:

```text
third_party/trampoline/
$RTIMEHOME/
```

If a Trampoline source change is proven necessary, keep it as a minimal
project-owned patch under `patches/`, but first exhaust official configuration
and hook mechanisms.

## Environment and Commands

Start each shell session with:

```bash
cd ~/autosar_virtual
source ./env.sh
git status --short
```

Normal workflow:

```bash
./generate.sh
./clean_build.sh
./build.sh
./run.sh
```

Build log:

```text
/tmp/autosar_virtual_build.log
```

Force-stop only when required:

```bash
pkill -f autosar_virtual
```

Do not combine that pattern into a larger command where it can match the
invoking shell command itself.

## Working Rules

1. Work one scenario at a time.
2. Before the first edit, identify the exact Trampoline code path and one
   focused check that can falsify the hypothesis.
3. After each edit, immediately run the narrowest generation/build/runtime
   validation available.
4. Diagnose the first meaningful failure before changing architecture.
5. Keep fault injection disabled in normal builds.
6. Do not put temporary diagnostics in `dds_example`.
7. Avoid printing from the 5 ms `TcpIp_Task`.
8. Do not allocate or block inside ErrorHook or OS hooks.
9. Do not add stack, heap, Perfetto, or stress scope to Phase 7.
10. Preserve the Golden DDS path and commit only verified milestones.
11. Keep responses short and give one meaningful experiment at a time.

## Start Here

Begin with Phase 7.1 only.

State:

```text
Current phase: Phase 7.1 - Trampoline capability and hook investigation
Objective: map the exact ErrorHook, activation-limit, resource, and priority-
ceiling mechanisms available in the checked-out Trampoline POSIX target
Ownership: [TRAMPOLINE] behavior, [CUSTOM] observation only
PASS: evidence-based API/configuration map with no project code changes
```

Then inspect the current OIL, generated configuration, Trampoline headers,
kernel implementation, and the closest official examples/tests. Return the
exact findings and propose only the first small implementation experiment.
Do not edit files during Phase 7.1.

## Phase 7.1 Investigation Result

```text
PHASE 7.1: COMPLETE
STATUS: PASS
```

Phase 7.1 inspected the checked-out Trampoline POSIX AUTOSAR OS implementation
before introducing Phase 7 runtime changes. No project source code was
modified during this investigation.

### ErrorHook and Service Context

Enable ErrorHook in OIL with:

```text
ERRORHOOK = TRUE;
USEGETSERVICEID = TRUE;
```

GOIL generates `WITH_ERROR_HOOK = YES` and the current Trampoline callback is:

```c
void ErrorHook(StatusType error);
```

The kernel path is:

```text
OS service -> STORE_SERVICE / parameter capture -> PROCESS_ERROR(error)
           -> tpl_call_error_hook(error) -> ErrorHook(error)
```

`OSErrorGetServiceId()` and service-specific parameter accessors, including
`OSError_ActivateTask_TaskID()`, `OSError_GetResource_ResID()`, and
`OSError_ReleaseResource_ResID()`, provide native ErrorHook context. The
kernel also prevents recursive ErrorHook invocation.

### Activation Limit

With `ACTIVATION = 1`, Trampoline accepts the first activation while the task
is active and increments its native activation count. A second activation
fails in `tpl_activate_task()` with `E_OS_LIMIT`, then `PROCESS_ERROR()` invokes
ErrorHook. No project-owned activation counter or simulation is required.

### Resources and Priority Ceiling

Trampoline owns resource state, nested-resource ordering, priority elevation,
and restoration. `GetResource()` records the owner, links the resource into
the task resource list, saves `owner_prev_priority`, and raises the effective
priority to the generated resource ceiling when required. `ReleaseResource()`
restores the saved priority, removes the resource, clears ownership, and
reschedules.

Nested resources are LIFO:

```text
GetResource(A) -> GetResource(B) -> ReleaseResource(B) -> ReleaseResource(A)
```

With `STATUS = EXTENDED`, the supported resource results identified from the
kernel and functional tests are:

```text
valid GetResource                         -> E_OK
valid nested GetResource                 -> E_OK
valid reverse-order ReleaseResource      -> E_OK
invalid Resource ID                      -> E_OS_ID
already-owned Resource / priority error  -> E_OS_ACCESS
incorrect release order                  -> E_OS_NOFUNC
release of unowned Resource              -> E_OS_NOFUNC
```

Generated resource ceilings are Trampoline/GOIL output and must not be copied
into application code. Existing DDS resources remain production resources and
must not be reused for destructive Phase 7 tests.

### Evidence Map

| Scenario | Trampoline mechanism | Expected result |
|---|---|---|
| OS service error | `PROCESS_ERROR()` | ErrorHook invoked |
| Service identification | `OSErrorGetServiceId()` | Service ID available |
| Activation overflow | native activation count vs. `ACTIVATION` | `E_OS_LIMIT` |
| Invalid Resource ID | extended-status ID check | `E_OS_ID` |
| Already-owned Resource | ownership check | `E_OS_ACCESS` |
| Resource priority violation | ceiling/base-priority check | `E_OS_ACCESS` |
| Nested Resource acquisition | native task resource list | `E_OK` |
| Incorrect release order | resource-order check | `E_OS_NOFUNC` |
| Priority ceiling | generated ceiling and dynamic priority | priority raised/restored |

### Design Decisions

Phase 7 observation code may record Trampoline results but must not replace
Trampoline semantics. The following are prohibited:

```text
custom activation-limit implementation
custom resource ownership or nesting stack
custom priority-ceiling implementation
fake application-level task priority
manual modification of generated Trampoline files
modification of third_party/trampoline
```

### Acceptance

```text
[PASS] ErrorHook configuration, prototype, and dispatch path identified
[PASS] service ID and parameter context identified
[PASS] activation overflow and E_OS_LIMIT identified
[PASS] resource ownership, nesting, and release ordering identified
[PASS] supported resource error codes identified
[PASS] priority ceiling generation and runtime behavior identified
[PASS] official functional tests inspected
[PASS] no project source modified
```

## Phase 7.1 Conclusion

Trampoline provides all native mechanisms required for the next phase. The
first implementation experiment is Phase 7.2: add a fixed-size project-owned
error monitor, enable the supported ErrorHook configuration, and validate one
controlled recoverable OS error. ErrorHook must only capture bounded data and
return; it must not allocate, block, perform socket I/O, or emit high-volume
output.

## Phase 7.2 - Minimal Error Monitor and ErrorHook

### Final Status

```text
PHASE 7.2: COMPLETE
STATUS: PASS
```

Phase 7.2 established a minimal project-owned OS error observation mechanism
using the real Trampoline AUTOSAR OS `ErrorHook`. Trampoline remains
responsible for detecting the OS error and invoking the hook; project-owned
code only records bounded observation data.

### Configuration

The OIL configuration enables:

```text
ERRORHOOK = TRUE;
USEGETSERVICEID = TRUE;
```

Generated configuration was verified as:

```text
WITH_ERROR_HOOK       = YES
WITH_ANY_HOOK         = YES
WITH_USEGETSERVICEID  = YES
```

No generated Trampoline source was manually modified.

### ErrorHook Contract

The active interface is:

```c
void ErrorHook(StatusType error);
```

The hook reads `OSErrorGetServiceId()`. The fixed-size project-owned record
contains only an occurrence count, the Trampoline `StatusType`, and the OS
service identifier stored as `uint8`:

```c
typedef struct
{
  volatile unsigned long count;
  volatile StatusType error;
  volatile uint8 service_id;
} Phase7_OsErrorRecord;
```

The hook performs bounded assignments only. It does not allocate, block,
perform file/socket/DDS I/O, print, or emit high-volume diagnostics. Output is
performed after returning from ErrorHook.

### Controlled Recoverable Error

Activation overflow remains reserved for Phase 7.3. The Phase 7.2 test instead
injects one invalid resource request from the project-owned `App_Task`:

```c
GetResource((ResourceType)RESOURCE_COUNT);
```

With `STATUS = EXTENDED` and generated `RESOURCE_COUNT = 5`, the requested ID
is invalid. Trampoline therefore returns and reports:

```text
E_OS_ID = 3
```

A local static flag ensures that the error is injected exactly once. The test
does not use `TcpIp_Task`, `RTI_Task`, DDS CDD generated tasks, or RTI
PSL/PIL, and it does not deliberately manipulate existing DDS resources.

### Runtime Evidence

Observed output:

```text
[Phase7.2] GetResource(invalid): return=3 hook_count=1 hook_error=3 service_id=24
DdsCdd_Adapter_Write_Cabin_Door_PDIO_FL: Sample written successfully
```

The result and hook record agree:

```text
GetResource return == ErrorHook error == 3
hook_count == 1
service_id == 24
```

The DDS CDD write after the hook demonstrates that execution continued after
the recoverable error and that the record was observable outside hook context.

### Build and Ownership Evidence

The clean build completed with:

```text
[100%] Built target autosar_virtual
```

Existing RTI AUTOSAR/Trampoline macro redefinition warnings predate Phase 7.2
and did not prevent the successful build. Trampoline owns invalid resource
detection, `E_OS_ID` generation, service-context storage, and ErrorHook
invocation. Project-owned code only records and reports the supplied values.

Phase 7.2 changes are limited to:

```text
config/os/autosar_virtual.oil
config/os/task_impl.c
```

No changes are required under `third_party/trampoline/`; generated files under
`autosar_virtual/` remain generated artifacts.

### Acceptance

```text
[PASS] Trampoline ErrorHook enabled through OIL
[PASS] USEGETSERVICEID enabled
[PASS] ErrorHook(StatusType) interface used
[PASS] fixed-size record with no allocation, blocking, or I/O
[PASS] real recoverable Trampoline OS error generated
[PASS] ErrorHook invoked and error/service ID captured
[PASS] record observable outside ErrorHook
[PASS] error injected exactly once
[PASS] execution and DDS processing continue after ErrorHook
[PASS] no DDS task used for fault injection
[PASS] no generated Trampoline source manually modified
[PASS] clean build completed
```

## Phase 7.2 Conclusion

Minimal ErrorHook infrastructure is operational. A real recoverable Trampoline
OS error invokes the configured hook, supplies the error and service context,
updates a bounded project-owned record, and resumes normal execution. The
Virtual AUTOSAR/DDS Golden behavior remains operational.

Next step: Phase 7.3 - activation limit validation with a dedicated task and
native `E_OS_LIMIT` behavior.

## Phase 7.3 - Activation Limit / E_OS_LIMIT

### Final Status

```text
PHASE 7.3: COMPLETE
STATUS: PASS
```

Phase 7.3 validated the real Trampoline AUTOSAR OS activation-limit behavior.
A second activation of a task configured with `ACTIVATION = 1` was rejected
with `E_OS_LIMIT`, delivered to the configured ErrorHook, and followed by
continued OS and DDS execution.

### Test Task and Native Limit

The existing project-owned task was used without changing any DDS task:

```text
TASK App_Task {
  PRIORITY = 2;
  AUTOSTART = FALSE;
  ACTIVATION = 1;
  SCHEDULE = FULL;
};
```

Generated task information identified `App_Task` as task ID `3`. The task was
already active when it called:

```c
ActivateTask(App_Task);
```

Trampoline's native activation count was therefore at its configured limit.
The OS definition confirms:

```text
E_OS_LIMIT = 4
OSServiceId_ActivateTask = 12
```

No project-owned activation counter or scheduling emulation was introduced.

### Fault Isolation

The Phase 7.2 invalid-resource injection was removed from the active test
path. A static flag ensured that the controlled activation-limit request was
performed once. No fault was injected into `TcpIp_Task`, `RTI_Task`, either
DdsCdd task, generated DDS CDD code, or RTI PSL/PIL.

### Runtime Evidence

Observed output:

```text
[Phase7.3] ActivateTask(App_Task): return=4 hook_before=0 hook_after=1 hook_error=4 service_id=12
[Phase7.3] App_Task continued after E_OS_LIMIT
```

The observed values match the native Trampoline expectations:

```text
ActivateTask() return       = 4  = E_OS_LIMIT
ErrorHook count before      = 0
ErrorHook count after       = 1
ErrorHook error             = 4  = E_OS_LIMIT
ErrorHook service ID        = 12 = ActivateTask
```

Thus exactly one ErrorHook invocation was associated with the controlled
activation overflow:

```text
hook_after - hook_before = 1
```

### Recovery and Golden Behavior

`App_Task` continued after `ActivateTask()` returned `E_OS_LIMIT` and then
terminated normally. Subsequent periodic OS scheduling and DDS CDD processing
also continued. Observed DDS evidence included:

```text
DdsCdd_Adapter_Write_Cabin_Door_PDIO_FL: Sample written successfully
```

No DDS transport properties, socket architecture, task priorities, generated
RTE semantics, or DDS resource configuration were changed for this scenario.

### Ownership and Safety

Trampoline owns the task activation count, limit enforcement, `E_OS_LIMIT`
generation, service-context storage, ErrorHook invocation, and scheduling.
Project-owned code only initiates one controlled activation request, records
the hook data, and reports it outside ErrorHook.

The bounded Phase 7.2 ErrorHook contract remains unchanged: no allocation,
blocking, `printf`, file/socket/DDS I/O, or high-volume diagnostics occur in
the hook.

### Acceptance

```text
[PASS] Real Trampoline activation mechanism exercised
[PASS] Test task configured with ACTIVATION = 1
[PASS] Second activation attempted while task was active
[PASS] ActivateTask() returned E_OS_LIMIT (4)
[PASS] ErrorHook invoked exactly once
[PASS] ErrorHook recorded error 4 and service ID 12
[PASS] Calling task continued after the recoverable error
[PASS] Subsequent OS scheduling continued
[PASS] Subsequent DDS processing continued
[PASS] No DDS task was deliberately overloaded
[PASS] No custom activation counter was used
[PASS] No Trampoline source modification was required
```

## Phase 7.3 Conclusion

Trampoline correctly enforced `ACTIVATION = 1`. A second activation of the
active `App_Task` returned `E_OS_LIMIT (4)`, invoked ErrorHook exactly once,
and recorded `service_id = 12` for `ActivateTask`. The task and subsequent DDS
CDD processing continued successfully, proving the recoverable activation
overflow path without reproducing OS behavior in project-owned code.

Next step: Phase 7.4 - dedicated resource and priority-ceiling validation.

## Phase 7.4 - Resource and Priority Ceiling Validation

### Final Status

```text
PHASE 7.4: COMPLETE
STATUS: PASS
```

Phase 7.4 validated the real Trampoline AUTOSAR OS resource mechanism,
including normal acquisition/release, nested resources, LIFO release,
generated priority ceilings, runtime priority-ceiling scheduling, priority
restoration, and preemption after release.

### Dedicated Test Resources

Two project-owned resources were added and kept separate from the production
DDS resources:

```text
Phase7_ResourceA
Phase7_ResourceB
```

`OsResource_DdsMain`, `OsResource_DdsTimer`, and `OsResource_DdsNetio` were not
repurposed for destructive Phase 7 testing.

`App_Task` was configured to use both dedicated resources. The normal nested
sequence was:

```text
GetResource(Phase7_ResourceA)
GetResource(Phase7_ResourceB)
ReleaseResource(Phase7_ResourceB)
ReleaseResource(Phase7_ResourceA)
```

Observed result:

```text
[Phase7.4.1] nested resource: getA=0 getB=0 releaseB=0 releaseA=0 hook_before=0 hook_after=0
```

This proves normal acquisition, nested acquisition, correct LIFO release, and
no unexpected ErrorHook invocation.

### Priority Ceiling Scheduling

The dedicated `Phase7_MidTask` was configured at a priority above the
`App_Task` base priority and registered as a user of `Phase7_ResourceA`, but it
did not acquire the resource itself. GOIL generated the following relationship:

```text
App_Task base priority             = 3
Phase7_MidTask base priority       = 5
Phase7_ResourceA ceiling priority  = 6

3 < 5 < 6
```

While `App_Task` owned `Phase7_ResourceA`, Trampoline raised its effective
priority to `6`. The ready `Phase7_MidTask` at priority `5` therefore could not
preempt it. The controlled sequence was:

```text
GetResource(Phase7_ResourceA)
ActivateTask(Phase7_MidTask)
LOW_BEFORE_RELEASE
ReleaseResource(Phase7_ResourceA)
LOW_AFTER_RELEASE
```

Observed runtime order:

```text
[Phase7.4.2] LOW_GOT_RESOURCE get=0
[Phase7.4.2] LOW_BEFORE_RELEASE activate=0
[Phase7.4.2] MID_TASK_RUNNING
[Phase7.4.2] LOW_AFTER_RELEASE release=0 hook_count=0
```

`MID_TASK_RUNNING` did not occur after activation while the resource was held.
It ran immediately after `ReleaseResource()` restored `App_Task` from effective
priority `6` to base priority `3`, before the following `LOW_AFTER_RELEASE`
output. This demonstrates actual Trampoline priority-ceiling scheduling and
priority restoration through dispatch behavior, without a custom priority
variable or scheduler implementation.

### Ownership and Isolation

Trampoline remained responsible for resource ownership, nested-resource
tracking, ceiling calculation, dynamic priority elevation, restoration, ready
task scheduling, and context switching. Project-owned code only declared the
dedicated resources/task, called standard AUTOSAR OS APIs, and recorded
deterministic observation points.

No generated descriptor or Trampoline source was modified. Internal generated
resource descriptor fields were not assumed to be public resource-table
indices because all public resource operations already passed independently.

### Acceptance

```text
[PASS] Dedicated Phase 7 resources used
[PASS] Production DDS resources preserved
[PASS] Normal GetResource() and ReleaseResource() passed
[PASS] Nested acquisition and correct LIFO release passed
[PASS] No unexpected ErrorHook invocation
[PASS] GOIL-generated ceiling inspected
[PASS] App base < MidTask priority < resource ceiling (3 < 5 < 6)
[PASS] Resource ownership suppressed MidTask preemption
[PASS] ReleaseResource() restored task priority
[PASS] MidTask preempted after priority restoration
[PASS] Real Trampoline scheduler used
[PASS] No custom resource/ceiling implementation
[PASS] No Trampoline source modification required
```

## Phase 7.4 Conclusion

Normal and nested resource operations passed with correct LIFO release. GOIL
generated `App_Task = 3`, `Phase7_MidTask = 5`, and
`Phase7_ResourceA ceiling = 6`; while the resource was held, the ceiling
prevented preemption, and release restored the priority so `Phase7_MidTask`
ran before `App_Task` continued. The behavior was provided entirely by
Trampoline and remained isolated from the DDS production resources.

Next step: Phase 7.5 - supported resource and state error-case validation.

## Phase 7.5 - Supported Resource / State Error Validation

### Final Status

```text
PHASE 7.5: COMPLETE
STATUS: PASS
```

Phase 7.5 validated supported Trampoline AUTOSAR OS resource error paths under
`STATUS = EXTENDED`, `ERRORHOOK = TRUE`, and `USEGETSERVICEID = TRUE`. Only
errors confirmed by the Trampoline implementation were exercised. No
unsupported status was manufactured, and production DDS resources were not
used for fault injection.

### 7.5.1 Duplicate GetResource

The controlled sequence used the dedicated `Phase7_ResourceA`:

```text
GetResource(A) -> E_OK
GetResource(A) -> E_OS_ACCESS
ErrorHook
ReleaseResource(A) -> E_OK
```

Observed result:

```text
[Phase7.5.1] double GetResource:
first=0
second=1
release=0
hook_before=0
hook_after=1
hook_error=1
service_id=24
```

The second acquisition returned `E_OS_ACCESS = 1`, invoked ErrorHook exactly
once, and identified `GetResource` with service ID `24`. The final successful
release proves that the rejected duplicate acquisition preserved the original
resource ownership.

### 7.5.2 Wrong Resource Release Order

The nested sequence used the dedicated resources A and B:

```text
GetResource(A) -> E_OK
GetResource(B) -> E_OK
ReleaseResource(A) -> E_OS_NOFUNC
ReleaseResource(B) -> E_OK
ReleaseResource(A) -> E_OK
```

Observed result:

```text
[Phase7.5.2] wrong release order:
getA=0
getB=0
wrongA=5
releaseB=0
releaseA=0
hook_before=0
hook_after=1
hook_error=5
service_id=9
```

The invalid release returned `E_OS_NOFUNC = 5`, invoked ErrorHook exactly once,
and identified `ReleaseResource` with service ID `9`. The subsequent valid B
then A releases prove that the rejected out-of-order release preserved the
resource stack.

### ErrorHook and Recovery

Both scenarios used the bounded Phase 7 ErrorHook record containing only the
error code, service ID, and occurrence counter. The hook performed no
allocation, blocking, socket/DDS I/O, or high-volume logging.

Both errors were recoverable:

```text
duplicate GetResource -> ErrorHook -> ReleaseResource(A) succeeds
wrong release order   -> ErrorHook -> ReleaseResource(B), then A succeeds
```

After the wrong-order scenario and cleanup, normal DDS processing continued,
including:

```text
DdsCdd_Adapter_Write_Cabin_Door_PDIO_FL:
Sample written successfully
```

### Ownership and Isolation

Trampoline remained responsible for resource ownership checks, nested-resource
tracking, release-order validation, `E_OS_ACCESS` and `E_OS_NOFUNC` generation,
ErrorHook dispatch, service-ID recording, and resource-stack preservation.
Project-owned code only issued controlled standard OS API calls and observed
the results.

Fault injection used only `Phase7_ResourceA`, `Phase7_ResourceB`, and
`App_Task`. The production resources `OsResource_DdsMain`,
`OsResource_DdsTimer`, and `OsResource_DdsNetio` remained isolated. No
Trampoline source modification was required.

### Acceptance

```text
[PASS] Real Trampoline resource APIs exercised
[PASS] Dedicated Phase 7 resources used
[PASS] Production DDS resources isolated
[PASS] Duplicate GetResource detected as E_OS_ACCESS
[PASS] GetResource ErrorHook invoked exactly once with service ID 24
[PASS] Original ownership preserved after failed duplicate acquisition
[PASS] Wrong release order detected as E_OS_NOFUNC
[PASS] ReleaseResource ErrorHook invoked exactly once with service ID 9
[PASS] Nested resource stack preserved after rejected release
[PASS] Correct cleanup completed after both errors
[PASS] Execution and DDS processing continued
[PASS] No unsupported status manufactured
[PASS] No Trampoline source modification required
```

## Phase 7.5 Conclusion

Trampoline `STATUS = EXTENDED` resource error handling passed two controlled
misuse cases. Duplicate acquisition returned `E_OS_ACCESS` and preserved the
original ownership; out-of-order release returned `E_OS_NOFUNC` and preserved
the nested resource stack. Both errors reached ErrorHook with the expected
service context, cleanup succeeded, and normal DDS processing continued.

Next step: Phase 7.6 - Golden regression, clean generation/build, and Phase 7
baseline finalization.

## Phase 7.6 - Golden Regression and Baseline Restoration

### Final Status

```text
PHASE 7.6: COMPLETE
STATUS: PASS
```

Phase 7.6 removed the temporary Phase 7 fault-injection and resource-test
infrastructure and restored the normal Linux AUTOSAR Virtual PoC Golden path.
The bounded project-owned ErrorHook remains as the permanent OS error
observation mechanism.

### Baseline Cleanup

The following test-only elements were removed:

```text
Phase7_ResourceA
Phase7_ResourceB
Phase7_MidTask
Phase 7.3 activation-limit injection
Phase 7.4 resource/priority-ceiling test
Phase 7.5 resource-error injection
```

The production resources were unchanged:

```text
OsResource_DdsMain
OsResource_DdsTimer
OsResource_DdsNetio
```

`App_Task` was restored to its normal path:

```c
TASK(App_Task)
{
  MockAswc_Run();
  TerminateTask();
}
```

Normal runtime no longer contains deliberate AUTOSAR OS errors.

### Permanent ErrorHook Monitor

The bounded Phase 7 monitor was retained:

```c
typedef struct
{
  volatile unsigned long count;
  volatile StatusType error;
  volatile uint8 service_id;
} Phase7_OsErrorRecord;
```

`ErrorHook(StatusType error)` only records the error, service ID from
`OSErrorGetServiceId()`, and occurrence count. It performs no `printf`,
allocation, blocking, socket I/O, or file I/O. The OIL configuration retains:

```text
ERRORHOOK = TRUE;
USEGETSERVICEID = TRUE;
```

### Residue and Build Verification

Project source inspection confirmed no remaining references to:

```text
Phase7_ResourceA
Phase7_ResourceB
Phase7_MidTask
Phase 7.4 test logic
Phase 7.5 test logic
```

The normal workflow completed successfully:

```bash
source ./env.sh
./generate.sh
./clean_build.sh
./build.sh
./run.sh
```

GOIL generation produced no Phase 7 test resource/task residue, and the clean
project build completed without test-only dependencies. Normal Virtual AUTOSAR
startup and DDS CDD processing remained operational.

### Golden Baseline

The restored communication architecture remains:

```text
Mock ASWC
   <-> Generated Minimal RTE
   <-> Generated DDS CDD
   <-> RTI AUTOSAR PSL
   <-> RTI DDS Micro PIL
   <-> Virtual TcpIp
   <-> Trampoline POSIX AUTOSAR OS
```

No DDS transport configuration, receive sockets, `TcpIp_Task` architecture,
generated RTE semantics, RTI PSL/PIL integration, or production DDS resources
were changed during restoration.

### Final Baseline Contents

```text
Trampoline STATUS = EXTENDED
ERRORHOOK = TRUE
USEGETSERVICEID = TRUE
bounded project-owned ErrorHook
OS error counter
last OS error
last service ID
```

The baseline does not contain intentional activation overflow, duplicate
`GetResource()`, invalid resource release order, Phase 7 test resources,
Phase 7 test scheduling tasks, or normal-runtime fault injection.

### Acceptance

```text
[PASS] Phase 7 fault injection disabled
[PASS] Test resources removed
[PASS] Test task removed
[PASS] App_Task restored
[PASS] Bounded ErrorHook retained
[PASS] ERRORHOOK enabled
[PASS] USEGETSERVICEID enabled
[PASS] Clean GOIL generation
[PASS] Generated test residue removed
[PASS] Clean project build
[PASS] Normal runtime restored
[PASS] DDS Golden behavior preserved
[PASS] DDS production resources unchanged
[PASS] No Trampoline source modification required
```

## Phase 7.6 Conclusion

Temporary Phase 7 test infrastructure was removed after the OS robustness
experiments. The normal Golden application path was restored, while the
bounded ErrorHook remained enabled for permanent OS error observation. Clean
generation/build and normal Virtual AUTOSAR/DDS runtime verification passed;
no DDS transport architecture, generated RTE semantics, production resources,
or Trampoline kernel source required modification.

Phase 7 is complete. Next starting point: Phase 8 - AUTOSAR trace and runtime
monitoring.

## Phase 7 Final Record

```text
PHASE 7: COMPLETE
STATUS: PASS
```

Phase 7 validated the real Trampoline POSIX AUTOSAR OS robustness mechanisms
used by the Linux AUTOSAR Virtual PoC. The completed scope covers ErrorHook,
service identification, activation limits, `E_OS_LIMIT`, recoverability,
resource acquisition/release, nested resources, priority ceiling, priority
restoration, `E_OS_ACCESS`, `E_OS_NOFUNC`, and Golden baseline regression.

### Phase Results

```text
7.1  Trampoline capability / hook investigation       PASS
7.2  Minimal ErrorHook / OS error monitor              PASS
7.3  Activation limit / E_OS_LIMIT                    PASS
7.4  Resource / nested resource / priority ceiling    PASS
7.5  Supported resource error paths                   PASS
7.6  Golden regression / baseline restoration         PASS
```

### Final Ownership Boundary

```text
Trampoline:
  scheduling, task activation, activation limits, events,
  resources, nesting, priority ceiling/restoration,
  ErrorHook dispatch, and OS status generation

Project-owned:
  bounded ErrorHook observation record, application tasks,
  Virtual AUTOSAR integration, and DDS CDD integration
```

No Trampoline OS mechanism was duplicated in application code, and no
Trampoline kernel source was modified.

### Golden DDS Preservation

The Phase 3 Golden architecture remained unchanged:

```text
Mock ASWC
   <-> Generated Minimal RTE
   <-> Generated DDS CDD
   <-> RTI AUTOSAR PSL
   <-> RTI DDS Micro PIL
   <-> Virtual TcpIp
   <-> Trampoline POSIX AUTOSAR OS
```

Phase 7 required no changes to DDS transport properties, receive sockets,
`TcpIp_Task`, generated CDD/RTE semantics, RTI PSL/PIL, or production DDS
resources. All deliberate fault injection and test-only resources/tasks were
removed in Phase 7.6.

### Final Acceptance

```text
[PASS] Real Trampoline ErrorHook and bounded observation
[PASS] Service-context capture
[PASS] Real activation-limit error and E_OS_LIMIT
[PASS] Recoverable execution after ErrorHook
[PASS] Normal and nested resource acquire/release
[PASS] Priority ceiling and priority restoration
[PASS] Supported E_OS_ACCESS path
[PASS] Supported E_OS_NOFUNC path
[PASS] Resource state preserved after errors
[PASS] Fault injection removed from final baseline
[PASS] Clean GOIL generation and project build
[PASS] Golden runtime restored
[PASS] DDS integration preserved
[PASS] Trampoline source unchanged
```

### Final Conclusion

The Linux AUTOSAR Virtual PoC now has verified Trampoline-backed OS behavior
for error reporting, activation-limit enforcement, recoverable errors,
resource ownership, nested resources, priority-ceiling scheduling, priority
restoration, and extended-status resource errors. The bounded ErrorHook is
retained as the permanent Phase 7 runtime OS error observation mechanism, and
the normal Golden DDS execution path is restored.

Phase 7 is complete. Phase 8 starts with AUTOSAR trace and runtime monitoring.
