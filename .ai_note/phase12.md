# Phase 12 - Final Virtual ECU Test Bench

## Intermediate Validation Report

### Current Status

```text
PHASE 12: IN PROGRESS

Phase 12.1  Reusable Golden Workflow Validation        PASS
Phase 12.2  DdsCdd Input / RTE Generation Validation  PASS
Phase 12.3  Integrated DDS Test-Bench Validation       PASS
Phase 12.4  Trace / Monitoring Evidence Validation     PASS

Phase 12.5  Repeatability / Cleanup Validation         NEXT
Phase 12.6  Perfetto Visualization                     OPTIONAL
```

Phase 12 packages and validates the existing Golden Linux AUTOSAR runtime as a repeatable Virtual ECU Test Bench.

It does not redesign the runtime architecture established by the previous phases.

The validated architecture remains:

```text
Application / Mock ASWC
        <->
Generated Minimal RTE
        <->
Generated DDS CDD
        <->
RTI AUTOSAR PSL
        <->
RTI DDS Micro PIL
        <->
Virtual AUTOSAR TcpIp
        <->
Trampoline POSIX AUTOSAR OS
        <->
Linux / ViPER
        <->
UDP / RTPS
        <->
Windows DDS Host
```

Phase 11 remains the integrated functional acceptance baseline.

---

# 1. Phase 12 Objectives

The purpose of Phase 12 is to convert the validated Linux AUTOSAR Virtual PoC into a reproducible Virtual ECU test workflow.

The target workflow is:

```text
DdsCdd Application Input
        |
        v
Generate RTE / Integration Artifacts
        |
        v
Clean Build
        |
        v
Run Virtual ECU
        |
        v
Real Bidirectional DDS Test
        |
        v
Capture Trampoline Trace
        |
        v
Runtime Monitor / Memory Evidence
        |
        v
Preserve Validation Evidence
```

The following Golden properties must remain intact:

- real DDS communication
- AUTOSAR task/alarm/event semantics
- Trampoline POSIX scheduling
- Virtual AUTOSAR TcpIp
- RTI AUTOSAR PSL
- RTI DDS Micro PIL
- Phase 8 runtime trace monitoring
- Phase 9 memory monitoring linkage
- Phase 10 cleanup
- Phase 11 integrated DDS baseline
- Trampoline POSIX 1 ms counter timer

---

# 2. Canonical Workflow

The reusable build workflow is:

```text
cd ~/autosar_virtual

source ./env.sh
./generate.sh
./clean_build.sh
./build.sh
./run.sh
```

Normal interactive termination:

```text
Ctrl+C
```

The canonical runtime trace inspection command is:

```text
python3 tools/runtime_monitor/runtime_monitor.py \
    trace.json \
    --static-info autosar_virtual/tpl_static_info.json \
    --derived \
    --limit 0
```

`--limit 0` is required for complete validation output.

Without it, the runtime monitor default output limit may hide later runtime events.

---

# 3. Phase 12.1 - Reusable Golden Workflow Validation

## Status

```text
PHASE 12.1: COMPLETE
STATUS: PASS
```

## 3.1 Baseline Repository Validation

Initial repository state:

```text
 M .ai_note/overview.md
 m  third_party/trampoline
?? .ai_note/phase12.md
```

The Trampoline submodule contains the expected Golden POSIX timer modification:

```text
tpl_viper_start_auto_timer(signal_for_counters,1000); /* 1 ms */
```

The previous value was 10 ms.

The 1 ms setting is an intentional Golden runtime dependency and must not be treated as Phase 12 contamination.

Required scripts were confirmed:

```text
env.sh          OK
generate.sh     OK
clean_build.sh  OK
build.sh        OK
run.sh          OK
```

## 3.2 Clean Generation and Build

The complete generation/build sequence was executed successfully.

```text
GENERATE_RC=0
CLEAN_RC=0
BUILD_RC=0
```

No unexpected repository modifications were produced by generation or compilation.

## 3.3 Runtime Startup and Shutdown

The generated Virtual AUTOSAR ECU was executed successfully using:

```text
./run.sh
```

The runtime was terminated using:

```text
Ctrl+C
```

Post-run process validation:

```text
LEFTOVER PROCESSES
NONE
```

A new Trampoline trace was generated successfully.

## 3.4 Trace Validation

The canonical runtime monitor successfully decoded:

- task activation
- task dispatch
- task preemption
- task termination
- alarm expiration
- event set
- event reset
- task wakeup
- resource acquire
- resource release
- task wait/resume

At this stage a persistent single parser warning remained and was intentionally deferred to Phase 12.4 for detailed investigation.

## Phase 12.1 Result

```text
Reusable workflow        PASS
Generation               PASS
Clean build              PASS
Runtime startup          PASS
Ctrl+C shutdown          PASS
Process cleanup          PASS
Trace generation         PASS

PHASE 12.1: COMPLETE / PASS
```

---

# 4. Phase 12.2 - DdsCdd Input and RTE Generation Validation

## Status

```text
PHASE 12.2: COMPLETE
STATUS: PASS
```

## 4.1 Supported DdsCdd Input Boundary

`generate.sh` discovers the DDS CDD application using:

```text
dds_example/<DDS_CDD_APPLICATION>/autosar_gen/DdsCdd.c
```

Exactly one candidate must exist.

The supported conceptual input boundary is therefore:

```text
dds_example/
└── <DDS_CDD_APPLICATION>/
    ├── autosar_gen/
    │   └── DdsCdd.c
    ├── autosar_model/
    │   └── DdsCddType.arxml
    └── ...
```

The currently validated application is:

```text
dds_example/PDIO_FL_Domain_6/
```

However, Phase 12 does not define the PDIO application name as a hardcoded platform requirement.

The application directory is the replaceable input boundary.

## 4.2 Generator Flow

The generator performs the following sequence:

```text
Find exactly one:
    */autosar_gen/DdsCdd.c

Determine:
    DDS_CDD_AUTOSAR_GEN_DIR

Run:
    tools/ddscdd_scanner/scan_ddscdd.py

Input:
    DDS CDD generated source
    associated AUTOSAR model

Output:
    minimal Virtual AUTOSAR integration artifacts
```

## 4.3 Generated Artifact Ownership

The DDS CDD scanner directly owns the following generated artifacts:

```text
platform/autosar/Rte_Type.h
platform/autosar/Rte_DdsCddType.h
platform/autosar/Rte_DdsCddType.c
platform/autosar/DdsCdd_Task.c
platform/autosar/VirtualAswc.h
platform/autosar/VirtualAswc.c
```

Other files under `platform/autosar` are not automatically considered scanner-owned.

## 4.4 Deterministic Generation

Hashes of the generated artifacts were recorded before and after regeneration.

Result:

```text
HASH DIFF
<empty>
```

Therefore repeated generation from the same DDS CDD input produced identical artifacts.

## 4.5 Clean Regeneration

The six scanner-owned files were removed and regenerated from the source DDS CDD application.

All six artifacts were restored successfully and their expected hashes were recovered.

No unexpected source modifications were produced.

## Phase 12.2 Result

```text
Input boundary identified       PASS
Single application discovery    PASS
AUTOSAR model discovery         PASS
Generated ownership identified  PASS
Deterministic generation        PASS
Clean regeneration              PASS

PHASE 12.2: COMPLETE / PASS
```

---

# 5. Phase 12.3 - Integrated DDS Test-Bench Validation

## Status

```text
PHASE 12.3: COMPLETE
STATUS: PASS
```

## 5.1 DDS Configuration

The validated DDS application is:

```text
PDIO_FL_Domain_6
```

DDS participant:

```text
parlib::PDIO_FL_Domain_6
```

Domain:

```text
domain_id = 6
```

Configured initial peer:

```text
0@192.168.56.1
```

Linux Virtual ECU interface:

```text
enp0s8
192.168.56.105/24
```

Transport:

```text
UDP / RTPS
```

## 5.2 Windows to Virtual ECU DDS Path

The receive path was validated as:

```text
Windows DDS Host
        |
        | RTPS / UDP
        v
DDS Reader
        |
        v
GCS_LEFT_2_PDIO_FL
        |
        v
DdsCdd_Adapter_Read_GCS_LEFT_2_PDIO_FL()
        |
        v
Generated RTE
        |
        v
Virtual AUTOSAR Application
```

Runtime evidence included:

```text
DdsCdd_Adapter_Read_GCS_LEFT_2_PDIO_FL:
Valid sample received
```

Real Windows-to-Linux DDS reception was observed.

## 5.3 Virtual ECU to Windows DDS Path

The transmit path was validated as:

```text
Virtual AUTOSAR Application
        |
        v
Rte_Write(...)
        |
        v
DdsCdd_Adapter_Write_Cabin_Door_PDIO_FL()
        |
        v
DDS Writer
        |
        | RTPS / UDP
        v
Windows DDS Host
```

Runtime evidence included:

```text
DdsCdd_Adapter_Write_Cabin_Door_PDIO_FL:
Sample written successfully
```

Real Linux-to-Windows DDS reception was observed.

Therefore communication was not a mock transport test.

It was real bidirectional DDS communication.

## 5.4 Runtime Cleanup

After the DDS test the Virtual ECU was terminated using Ctrl+C.

Post-run process check:

```text
LEFTOVER
NONE
```

The resulting trace was approximately:

```text
1.9 MB
```

## 5.5 Integrated AUTOSAR Runtime Evidence

The DDS test generated:

```text
raw_records     = 25247
derived_records = 25247
```

before the Phase 12.4 parser defect correction.

The trace showed repeated AUTOSAR runtime activity including:

```text
DdsCddTimerTickAlarm
    ->
DdsCddTimerTick_Task
    ->
OsResource_DdsTimer
    ->
DdsCddTimerUpdateEvent
    ->
DdsCddReadWrite_Task WAKEUP
    ->
EVENT_RESET
    ->
OsResource_DdsMain
    ->
WAIT
```

The trace also showed periodic:

```text
TcpIp_5ms_Alarm
    ->
TcpIp_Task
```

This demonstrates that real DDS communication operated together with the expected AUTOSAR OS task, alarm, event and resource model.

## Phase 12.3 Result

```text
DDS configuration              PASS
Windows -> Virtual ECU DDS     PASS
Virtual ECU -> Windows DDS     PASS
Real UDP/RTPS transport        PASS
AUTOSAR task integration       PASS
Alarm/event/resource activity  PASS
Runtime cleanup                PASS

PHASE 12.3: COMPLETE / PASS
```

---

# 6. Phase 12.4 - Trace and Monitoring Evidence Validation

## Status

```text
PHASE 12.4: COMPLETE
STATUS: PASS
```

Phase 12.4 performed final trace integrity validation and Phase 9 memory-monitor integration verification.

---

# 7. Phase 12.4.1 - Runtime Trace Parser Validation

Initial monitor result:

```text
SUMMARY
raw_records=25247
derived_records=25247
parser_warnings=1
trace_incomplete=no
```

The warning was:

```text
WARNING MALFORMED_RECORD
```

Detailed parser inspection showed:

```text
sequence = 25247
line     = 148651
detail   = Extra data: line 6 column 3 (char 74)
```

## 7.1 Trace File Integrity

The trace was independently parsed using Python's standard JSON parser.

Result:

```text
JSON_VALID=yes
JSON_RECORDS=25248
```

Therefore the trace file itself was valid.

The final JSON record was:

```text
{
    "type": "proc",
    "ts": "6971",
    "proc_id": "6",
    "target_state": "2"
}
```

All known numeric fields across all 25,248 records were also tested using the same integer normalization performed by the runtime monitor.

Result:

```text
TOTAL_JSON_RECORDS = 25248
NORMALIZATION_FAILURES = 0
```

Therefore the problem was not:

- malformed Trampoline JSON
- invalid numeric data
- incomplete trace
- numeric normalization

## 7.2 Root Cause

The end of `trace.json` was:

```text
{
    "type":"proc",
    "ts":"6971",
    "proc_id":"1",
    "target_state":"3"
},
{
    "type":"proc",
    "ts":"6971",
    "proc_id":"6",
    "target_state":"2"
}]
```

The final object closing brace and JSON array closing bracket occur on the same line:

```text
}]
```

The streaming parser appended the entire line to its object buffer.

Consequently the final object was effectively passed to `json.loads()` as:

```text
{
    ...
}]
```

This caused:

```text
Extra data
```

The standard JSON parser did not have this problem because it parses the complete array.

## 7.3 Runtime Monitor Fix

`tools/runtime_monitor/runtime_monitor.py` was updated so that JSON array framing sharing the final object line is removed before parsing.

Added logic:

```text
# Remove JSON-array framing that may share the same line as
# the final object closing brace (for example "}]").
if text.endswith("]"):
    text = text[:-1].rstrip()
```

The existing object-comma handling remains unchanged.

## 7.4 Regression Result

After the parser correction:

```text
seq=25245 ts=6971 DERIVED RESOURCE_RELEASE
    resource=OsResource_DdsMain
    owner=DdsCddReadWrite_Task

seq=25246 ts=6971 DERIVED WAIT
    task=DdsCddReadWrite_Task

seq=25247 ts=6971 DERIVED RESUME
    task=idle
```

Final summary:

```text
SUMMARY
raw_records=25248
derived_records=25248
parser_warnings=0
trace_incomplete=no
```

Independent JSON count:

```text
JSON_RECORDS = 25248
```

The runtime monitor and standard JSON parser therefore agree exactly:

```text
Standard JSON records     25248
Runtime monitor raw       25248
Runtime monitor derived   25248
Parser warnings           0
Trace incomplete          no
```

The correction also recovered the previously lost final:

```text
RESUME task=idle
```

event.

This was therefore a real parser defect correction rather than merely suppression of a warning.

## Phase 12.4.1 Result

```text
Trace JSON integrity       PASS
Numeric normalization      PASS
Streaming parser diagnosis PASS
Parser correction          PASS
Record-count regression    PASS
Final event recovery       PASS
Warnings                   0
Incomplete trace           no

PHASE 12.4.1: COMPLETE / PASS
```

---

# 8. Phase 12.4.2 - Phase 9 Memory Monitoring Linkage

The runtime monitor provides native Phase 9 memory snapshot integration:

```text
--memory MEMORY
--stack-warn-percent STACK_WARN_PERCENT
```

The Phase 9 artifact was found at:

```text
memory_snapshot.json
```

The combined monitor invocation was validated using:

```text
python3 tools/runtime_monitor/runtime_monitor.py \
    trace.json \
    --static-info autosar_virtual/tpl_static_info.json \
    --memory memory_snapshot.json \
    --stack-warn-percent 80 \
    --derived \
    --limit 0
```

## 8.1 Task Stack Evidence

Decoded Phase 9 stack high-water data:

```text
DdsCddProcessData_Task
    allocated    32768
    used         3576
    free         29192
    utilization  10.9%

DdsCddReadWrite_Task
    allocated    32768
    used         6856
    free         25912
    utilization  20.9%

RTI_Task
    allocated    32768
    used         7080
    free         25688
    utilization  21.6%

App_Task
    allocated    32768
    used         4568
    free         28200
    utilization  13.9%

DdsCddTimerTick_Task
    allocated    32768
    used         3904
    free         28864
    utilization  11.9%

TcpIp_Task
    allocated    32768
    used         9792
    free         22976
    utilization  29.9%
```

The highest recorded stack utilization in this Phase 9 snapshot is:

```text
TcpIp_Task = 29.9%
```

## 8.2 Process Memory Evidence

The snapshot contains:

```text
VmRSS   = 3108 kB
VmHWM   = 3108 kB
VmSize  = 70248 kB
VmData  = 66012 kB
```

glibc allocator information:

```text
arena = 135168 bytes
used  =   8112 bytes
free  = 127056 bytes
mmap  =      0 bytes
```

With an 80% task-stack warning threshold:

```text
MEMORY_WARNINGS
none
```

## 8.3 Snapshot Lifetime

Artifact timestamps showed:

```text
trace.json
2026-09-22 09:32:25 +0000

tpl_static_info.json
2026-09-22 08:58:43 +0000

memory_snapshot.json
2026-09-21 13:57:29 +0000
```

Therefore `memory_snapshot.json` is not from the same Phase 12 DDS execution as the current trace.

This is intentional and consistent with the Golden runtime design.

Phase 9 previously validated snapshot generation using a temporary bounded probe.

That temporary probe was subsequently removed.

The Golden runtime does not permanently invoke:

```text
Phase9_MemorySnapshot_WriteJson()
```

No permanent shutdown/signal snapshot hook is present.

Phase 12 therefore does not add a new runtime hook merely to regenerate the snapshot.

Doing so would change the accepted Golden runtime instead of packaging and validating it.

The Phase 12 requirement is Phase 9 memory-monitor evidence linkage, which is satisfied by demonstrating that the existing Phase 9 snapshot can be consumed and correlated with current static task information by the runtime monitor.

## Phase 12.4.2 Result

```text
Memory snapshot detection       PASS
Task stack decoding             PASS
Task-name mapping               PASS
Process memory decoding         PASS
glibc memory decoding           PASS
Stack threshold evaluation      PASS
Memory warnings                 none
Runtime monitor linkage         PASS
Golden runtime unchanged        PASS

PHASE 12.4.2: COMPLETE / PASS
```

---

# 9. Phase 12.4.3 - Final Monitoring Evidence

Final artifacts:

```text
trace.json
    size: 1943591 bytes

autosar_virtual/tpl_static_info.json
    size: 7664 bytes

memory_snapshot.json
    size: 1121 bytes
```

Final trace result:

```text
seq=25245 ts=6971
DERIVED RESOURCE_RELEASE
resource=OsResource_DdsMain
owner=DdsCddReadWrite_Task

seq=25246 ts=6971
DERIVED WAIT
task=DdsCddReadWrite_Task

seq=25247 ts=6971
DERIVED RESUME
task=idle
```

Final summary:

```text
raw_records=25248
derived_records=25248
parser_warnings=0
trace_incomplete=no
```

`git diff --check` completed successfully.

Expected working-tree state includes:

```text
M  .ai_note/overview.md
m  third_party/trampoline
M  tools/runtime_monitor/runtime_monitor.py
?? .ai_note/phase12.md
```

The Trampoline modification is the existing Golden 1 ms timer dependency.

The runtime monitor modification is the intentional Phase 12 parser defect correction.

## Phase 12.4.3 Result

```text
Trace evidence              PASS
Static information          PASS
Phase 9 memory evidence     PASS
Runtime monitor             PASS
Parser warnings             0
Trace incomplete            no
git diff --check            PASS

PHASE 12.4.3: COMPLETE / PASS
```

---

# 10. Phase 12.4 Final Result

```text
Phase 12.4.1 Trace Integrity / Parser        PASS
Phase 12.4.2 Phase 9 Memory Linkage          PASS
Phase 12.4.3 Monitoring Evidence             PASS

PHASE 12.4: COMPLETE / PASS
```

A runtime-monitor defect discovered during final integration was corrected without modifying the Golden AUTOSAR runtime architecture.

---

# 11. Current Phase 12 Status

```text
+-----------------------------------------------------+
| Phase 12 Final Virtual ECU Test Bench               |
+-----------------------------------------------------+
| 12.1 Reusable Golden Workflow          PASS         |
| 12.2 DdsCdd / RTE Generation           PASS         |
| 12.3 Integrated DDS Test Bench         PASS         |
| 12.4 Trace / Monitoring Evidence       PASS         |
| 12.5 Repeatability / Cleanup           NEXT         |
| 12.6 Perfetto                         OPTIONAL      |
+-----------------------------------------------------+
```

The following capabilities have now been demonstrated together:

```text
Replaceable DDS CDD application input
        +
Deterministic minimal RTE generation
        +
Clean Virtual AUTOSAR build
        +
Trampoline POSIX AUTOSAR OS
        +
1 ms OS counter base
        +
Virtual AUTOSAR TcpIp
        +
RTI AUTOSAR PSL
        +
RTI DDS Micro PIL
        +
Real bidirectional Windows/Linux DDS
        +
AUTOSAR task/alarm/event/resource semantics
        +
Complete runtime trace decoding
        +
Phase 9 memory-monitor linkage
        +
Clean Ctrl+C termination
```

---

# 12. Next Phase

The next required phase is:

```text
Phase 12.5 - Repeatability and Cleanup Validation
```

Its purpose is to prove that the complete Virtual ECU Test Bench can be reproduced again from the canonical workflow rather than relying on artifacts left by the previous validation run.

The final repeatability sequence will cover:

```text
Clean
  ->
Generate
  ->
Build
  ->
Run Virtual ECU
  ->
Real DDS Communication
  ->
Trace Capture
  ->
Runtime Monitor
  ->
Shutdown
  ->
Process Cleanup
  ->
Repository / Artifact Inspection
```

The expected Phase 12.5 result is:

```text
Same workflow
Same generated integration
Successful clean build
Successful Virtual ECU startup
Successful real DDS communication
Complete trace
Zero parser warnings
Clean termination
No unexpected source contamination
```

After Phase 12.5 passes, Phase 12 can be considered functionally complete.

Phase 12.6 Perfetto remains optional and must remain a visualization layer only.

The authoritative runtime evidence remains:

```text
Trampoline trace.json
        +
tpl_static_info.json
        +
runtime_monitor.py
```

Perfetto must not replace or redefine the runtime-monitor semantics.
