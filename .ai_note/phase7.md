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
