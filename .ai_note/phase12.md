# Phase 12 - Final Virtual ECU Test Bench

## Final Status

```text
PHASE 12: COMPLETE

STATUS: PASS / GOLDEN
```

Phase 12 completed the Linux AUTOSAR Virtual PoC as a reusable Virtual ECU test bench.

The final environment integrates generated AUTOSAR RTE/CDD artifacts, RTI AUTOSAR PSL/PIL, real DDS communication, Trampoline POSIX AUTOSAR OS execution, runtime monitoring, memory monitoring, stress/fault validation, and Perfetto-compatible execution visualization.

The validated architecture is:

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
External DDS Host
```

Phase 12 does not replace the Golden baselines established by the previous phases. It verifies that those components can be regenerated, rebuilt, executed, monitored, and used together as one repeatable Virtual ECU test bench.

---

## 1. Phase 12 Scope

The Phase 12 validation consisted of:

```text
Subphase  Scope                                      Result
12.1      Reusable Golden Workflow                   PASS
12.2      DdsCdd Input / RTE Generation              PASS
12.3      Integrated DDS Test Bench                  PASS
12.4      Trace / Monitoring Evidence                PASS
12.5      Repeatability / Cleanup                    PASS
12.6      Perfetto Visualization                     PASS
```

Final result:

```text
Phase 12 = COMPLETE / PASS / GOLDEN
```

---

# 2. Phase 12.1 - Reusable Golden Workflow

## Result

```text
PASS
```

The complete Virtual AUTOSAR environment can be regenerated, rebuilt, and executed using the standard project workflow.

Canonical workflow:

```text
cd ~/autosar_virtual

source ./env.sh

./generate.sh
./clean_build.sh
./build.sh
./run.sh
```

Normal runtime termination:

```text
Ctrl+C
```

If a Trampoline/ViPER process remains after abnormal termination, the existing process cleanup procedure may be used.

The workflow successfully preserves the Golden integration established by the previous phases.

---

# 3. Phase 12.2 - DdsCdd Input and RTE Generation

## Result

```text
PASS
```

The test bench accepts the DDS CDD application model under:

```text
dds_example/<DDS_CDD_APPLICATION>/
```

The application used for final validation was:

```text
dds_example/PDIO_FL_Domain_6/
```

The generator analyzes the supplied AUTOSAR/DDS model and regenerates the minimal Virtual AUTOSAR integration artifacts.

Scanner-owned generated outputs are:

```text
platform/autosar/Rte_Type.h
platform/autosar/Rte_DdsCddType.h
platform/autosar/Rte_DdsCddType.c
platform/autosar/DdsCdd_Task.c
platform/autosar/VirtualAswc.h
platform/autosar/VirtualAswc.c
```

Generation was verified to be deterministic.

The generated source tree remained clean after repeated generation when the same input model was used.

---

# 4. Phase 12.3 - Integrated DDS Test Bench

## Result

```text
PASS
```

Real DDS communication was validated in both directions between the Linux Virtual ECU and an external Windows DDS host.

Validated configuration:

```text
DDS Domain : 6

Linux Virtual ECU:
192.168.56.105/24

Configured peer:
0@192.168.56.1
```

## Windows -> Linux

The Linux Virtual ECU successfully received valid DDS data for:

```text
GCS_LEFT_2_PDIO_FL
```

The data passed through the integrated DDS CDD / RTE path.

## Linux -> Windows

The Linux Virtual ECU successfully published:

```text
Cabin_Door_PDIO_FL
```

The external DDS host successfully received the transmitted DDS data.

Therefore the complete communication path was validated:

```text
External DDS Host
        <->
UDP / RTPS
        <->
Virtual TcpIp
        <->
RTI DDS Micro PIL
        <->
RTI AUTOSAR PSL
        <->
Generated DDS CDD
        <->
Generated RTE
        <->
Virtual ASWC
```

This is real DDS communication and not a mocked transport path.

---

# 5. Phase 12.4 - Trace and Monitoring Evidence

## Result

```text
PASS
```

The Phase 8 runtime monitor remains the authoritative semantic decoder for Trampoline AUTOSAR OS traces.

Canonical inspection command:

```bash
python3 tools/runtime_monitor/runtime_monitor.py \
  trace.json \
  --static-info autosar_virtual/tpl_static_info.json \
  --derived \
  --limit 0
```

`--limit 0` means unlimited output and is required for complete trace inspection.

A parser boundary defect involving the final JSON array terminator was corrected. The parser now handles the final `}]` boundary without treating the array terminator as an incomplete record.

Final regression:

```text
RAW_RECORDS      == DERIVED_RECORDS
PARSER_WARNINGS  == 0
TRACE_INCOMPLETE == no
```

Phase 9 memory monitoring compatibility was retained. No permanent artificial memory snapshot trigger was required for the final Golden runtime.

---

# 6. Phase 12.5 - Repeatability and Cleanup

## Result

```text
PASS
```

The complete test bench was repeatedly regenerated, rebuilt, executed, and inspected.

```text
generation       PASS
clean build      PASS
runtime          PASS
DDS RX           PASS
DDS TX           PASS
runtime trace    PASS
runtime monitor  PASS
cleanup          PASS
```

Generated source residue checks passed. Temporary validation modifications were removed after testing. The final AUTOSAR OS configuration was restored to its Golden configuration.

---

# 7. Phase 12.6 - Perfetto Visualization

## Result

```text
PASS
```

Perfetto visualization was added as an offline visualization layer on top of the existing authoritative Trampoline runtime trace. Perfetto does not replace the Phase 8 runtime monitor.

Architecture:

```text
Trampoline
    |
    v
trace.json
    |
    +----> runtime_monitor.py
    |          |
    |          +--> authoritative AUTOSAR semantic analysis
    |
    +----> trampoline_to_perfetto.py
               |
               +--> Perfetto visualization
```

Exporter:

```text
tools/perfetto/trampoline_to_perfetto.py
```

Generated visualization artifact:

```text
perfetto_trace.json
```

---

# 12.1 Runtime Trace and Perfetto Wrapper

Phase 12 provides a single post-processing wrapper for the trace generated by
the Virtual AUTOSAR ECU.

After `run.sh` generates `trace.json`, run:

```bash
./trace.sh
```

The wrapper generates both:

```text
runtime.txt
perfetto_trace.json
```

The resulting workflow is:

```text
./run.sh
        |
        v
trace.json
        |
        v
./trace.sh
        |
        +----> runtime_monitor.py
        |          |
        |          +----> runtime.txt
        |
        +----> trampoline_to_perfetto.py
                           |
                           +----> perfetto_trace.json
```

`runtime.txt` is the authoritative derived AUTOSAR semantic trace.
`perfetto_trace.json` is the graphical visualization artifact.

## Wrapper Behavior

The wrapper validates the trace, static information, runtime monitor, and
Perfetto exporter before processing. It uses the complete derived stream with
`--limit 0` and prints the final runtime-monitor summary after both outputs are
created.

The default input and output files are:

```text
input:  trace.json
output: runtime.txt
output: perfetto_trace.json
```

A different trace can be processed with:

```bash
./trace.sh /tmp/test_trace.json
```

Output paths can be overridden for comparison runs:

```bash
RUNTIME_OUTPUT=/tmp/run1.txt \
PERFETTO_OUTPUT=/tmp/run1_perfetto.json \
./trace.sh /tmp/run1_trace.json
```

## Quick Inspection

Because `trace.sh` creates the complete derived trace once, repeated analysis
should use `runtime.txt`:

```bash
grep 'task=TcpIp_Task' runtime.txt

The generated file is not source-controlled.

grep -E 'ALARM_EXPIRE|EVENT_SET|EVENT_RESET' runtime.txt
## Perfetto Semantic Model
```

Inspect a logical AUTOSAR time window:

```bash
awk '
match($0, /ts=([0-9]+)/, a) {
        ts = a[1] + 0
        if (ts >= 3000 && ts <= 3100)
                print
}' runtime.txt
```

The expected trace-integrity conditions remain:

```text
RAW_RECORDS == DERIVED_RECORDS
parser_warnings=0
trace_incomplete=no
```

The authoritative semantic analysis remains `runtime_monitor.py`; Perfetto is
the visualization layer and must not redefine AUTOSAR scheduling semantics.

## Generated Artifact Policy

The following are runtime/generated artifacts and are not source files:

```text
trace.json
runtime.txt
perfetto_trace.json
```

The source implementations are:

```text
trace.sh

The exporter reuses the existing Phase 8 semantic implementation, including:
```

## Phase 12 Trace Workflow Result

```text
RUNTIME MONITOR : INTEGRATED
PERFETTO EXPORT : INTEGRATED

STATUS: PASS / GOLDEN USABILITY IMPROVEMENT
```

```text
StaticInfo
iter_trace_records
RuntimeDeriver
```

This keeps Perfetto visualization and the authoritative runtime monitor on the same AUTOSAR OS state interpretation.

The exporter produces tracks for:

```text
AUTOSAR Tasks
AUTOSAR Alarms
AUTOSAR Events
AUTOSAR Resources
```

Task visualization includes:

```text
ACTIVATE
DISPATCH_NEW
DISPATCH_READY
WAKEUP
WAKEUP_DISPATCH
PREEMPT
RESUME
WAIT
TERMINATE
```

RUNNING execution intervals are represented using Perfetto begin/end slices. Alarm expiration, event operations, and resource operations are represented on their corresponding semantic tracks.

## Perfetto Regression

```text
RAW_RECORDS       = 14964
DERIVED_RECORDS   = 14964
PARSER_WARNINGS   = 0
TRACE_INCOMPLETE   = no

PERFETTO_EVENTS   = 19954

TASK_TRACKS       = 7
ALARM_TRACKS       = 6
EVENT_TRACKS       = 5
RESOURCE_TRACKS   = 4
```

Required semantic track categories were generated.

## Perfetto Export Determinism

The same `trace.json` input was exported twice independently. Both generated files produced:

```text
SHA-256 = 66a2d90de6bfcf5359d94774fb0b9c204098a860ad602b4c10ce1a1ddbff69b8
```

Binary comparison passed:

```text
PASS: Perfetto export deterministic
```

Python source validation passed:

```text
PASS: exporter syntax
```

## High-Resolution Runtime Timing

The original Trampoline trace timestamp remains unchanged and continues to represent AUTOSAR OS logical counter time:

```text
ts
```

A second timestamp was added for visualization/profiling:

```text
hires_ts_ns
```

It is generated using `clock_gettime(CLOCK_MONOTONIC, ...)` in:

```text
third_party/trampoline/machines/posix/tpl_trace.c
```

The logical timestamp remains authoritative for scheduling semantics. `hires_ts_ns` is used for host-side execution visualization and profiling only.

## Wall-Clock Timing Limitation

The Trampoline logical OS clock is not equivalent to real wall-clock time in the current VirtualBox execution environment.

Measured standalone sleep behavior:

```text
100 x usleep(10 ms)
expected = 1.000 sec
actual   = 1.561725 sec

1000 x usleep(1 ms)
expected = 1.000 sec
actual   = 4.997838 sec
```

The ViPER timer uses `usleep(delay)` and signal delivery, so short-duration timer behavior in the current Ubuntu VirtualBox environment does not guarantee wall-clock fidelity.

Final interpretation:

```text
AUTOSAR logical scheduling:
VALIDATED

VirtualBox wall-clock real-time accuracy:
NOT GUARANTEED
```

This does not invalidate the functional Virtual ECU test bench. `hires_ts_ns` must not be interpreted as WCET or physical ECU timing.

## Final Trampoline Modifications

The final Trampoline submodule contains two intentional POSIX modifications:

```text
machines/posix/tpl_machine_posix.c
    1 ms SystemCounter timer base

machines/posix/tpl_trace.c
    CLOCK_MONOTONIC hires_ts_ns for visualization
```

No existing AUTOSAR logical trace timestamp semantics were replaced.

---

# 8. Generated Artifact Policy

Perfetto output is a generated runtime artifact:

```text
perfetto_trace.json
```

It is excluded from source control. Python cache files are also not retained. The source-controlled Perfetto implementation consists of:

```text
tools/perfetto/trampoline_to_perfetto.py
```

---

# 9. Golden Runtime Monitoring Commands

## AUTOSAR Semantic Trace

```bash
python3 tools/runtime_monitor/runtime_monitor.py \
  trace.json \
  --static-info autosar_virtual/tpl_static_info.json \
  --derived \
  --limit 0
```

## Perfetto Export

```bash
python3 tools/perfetto/trampoline_to_perfetto.py \
  trace.json \
  --static-info autosar_virtual/tpl_static_info.json \
  -o perfetto_trace.json
```

The resulting file can be loaded into a compatible Perfetto trace viewer.

---

# 10. Final Golden Workflow

```text
cd ~/autosar_virtual

source ./env.sh

./generate.sh
./clean_build.sh
./build.sh
./run.sh
```

After runtime execution:

```bash
python3 tools/runtime_monitor/runtime_monitor.py \
  trace.json \
  --static-info autosar_virtual/tpl_static_info.json \
  --derived \
  --limit 0
```

Optional visualization:

```bash
python3 tools/perfetto/trampoline_to_perfetto.py \
  trace.json \
  --static-info autosar_virtual/tpl_static_info.json \
  -o perfetto_trace.json
```

The functional flow is:

```text
DdsCdd AUTOSAR Model
        |
        v
Generation
        |
        v
Generated RTE / DDS CDD / Virtual ASWC
        |
        v
Build
        |
        v
Trampoline POSIX Virtual ECU
        |
        +---- DDS/RTPS ---- External DDS Host
        |
        +---- trace.json
                 |
                 +---- runtime_monitor.py
                 |
                 +---- Perfetto exporter
```

---

# 11. Quick Inspection Commands

The Phase 8 runtime monitor remains the authoritative trace decoder. Generate the complete derived stream first:

```bash
python3 tools/runtime_monitor/runtime_monitor.py \
  trace.json \
  --static-info autosar_virtual/tpl_static_info.json \
  --derived \
  --limit 0
```

For repeated investigation, save it once:

```bash
python3 tools/runtime_monitor/runtime_monitor.py \
  trace.json \
  --static-info autosar_virtual/tpl_static_info.json \
  --derived \
  --limit 0 \
  > /tmp/runtime.txt
```

Inspect one task or lifecycle:

```bash
grep 'task=TcpIp_Task' /tmp/runtime.txt
grep 'task=DdsCddReadWrite_Task' /tmp/runtime.txt
grep 'task=DdsCddReadWrite_Task' /tmp/runtime.txt | \
  grep -E 'ACTIVATE|DISPATCH|PREEMPT|RESUME|WAIT|TERMINATE|WAKEUP'
```

Inspect scheduling, alarms, events, and resources:

```bash
grep -E 'DISPATCH|RESUME' /tmp/runtime.txt
grep 'ALARM_EXPIRE' /tmp/runtime.txt
grep -E 'EVENT_SET|EVENT_RESET' /tmp/runtime.txt
grep -E 'RESOURCE_ACQUIRE|RESOURCE_RELEASE' /tmp/runtime.txt
grep 'resource=OsResource_DdsMain' /tmp/runtime.txt
```

Count resource operations:

```bash
grep 'RESOURCE_ACQUIRE.*resource=OsResource_DdsMain' /tmp/runtime.txt | wc -l
grep 'RESOURCE_RELEASE.*resource=OsResource_DdsMain' /tmp/runtime.txt | wc -l
```

Inspect a logical time range:

```bash
awk '
match($0, /ts=([0-9]+)/, a) {
    ts = a[1] + 0
    if (ts >= 3000 && ts <= 3100)
        print
}' /tmp/runtime.txt
```

Quick trace integrity check:

```bash
python3 tools/runtime_monitor/runtime_monitor.py \
  trace.json \
  --static-info autosar_virtual/tpl_static_info.json \
  --derived \
  --limit 0 | tail -5
```

Expected:

```text
RAW_RECORDS == DERIVED_RECORDS
parser_warnings=0
trace_incomplete=no
```

Inspect raw trace and static AUTOSAR information:

```bash
ls -lh trace.json
head -40 trace.json
tail -40 trace.json
grep -o '"type":"[^"]*"' trace.json | sort | uniq -c | sort -nr
python3 -m json.tool autosar_virtual/tpl_static_info.json
```

Network and DDS inspection:

```bash
ip addr show enp0s8
ip route
sudo tcpdump -i enp0s8 -n -vv 'udp and host 192.168.56.1'
```

Process cleanup:

```bash
ps aux | grep -E 'autosar_virtual|viper' | grep -v grep
pkill -f autosar_virtual
pkill -f viper
```

Repository checks:

```bash
git status --short
git status --short platform/autosar
git -C third_party/trampoline diff -- \
  machines/posix/tpl_machine_posix.c \
  machines/posix/tpl_trace.c
```

Perfetto visualization:

```bash
python3 tools/perfetto/trampoline_to_perfetto.py \
  trace.json \
  --static-info autosar_virtual/tpl_static_info.json \
  -o perfetto_trace.json
```

---

# 12. Phase 12 Acceptance Criteria

```text
Criterion                                      Result
Clean generation                               PASS
Clean build                                    PASS
Virtual ECU startup                            PASS
Generated RTE integration                      PASS
Generated DDS CDD integration                  PASS
Real DDS receive                               PASS
Real DDS transmit                              PASS
AUTOSAR task execution                        PASS
Alarm/event/resource behavior                  PASS
Runtime trace integrity                        PASS
Runtime semantic derivation                    PASS
Memory-monitor compatibility                  PASS
Stress/fault regression compatibility          PASS
Perfetto task tracks                          PASS
Perfetto alarm tracks                         PASS
Perfetto event tracks                         PASS
Perfetto resource tracks                      PASS
High-resolution visualization timestamps       PASS
Perfetto deterministic generation             PASS
Temporary test cleanup                        PASS
Reusable Golden workflow                      PASS
```

---

# 13. Final Phase 12 Conclusion

Phase 12 successfully converts the previous Linux AUTOSAR PoC phases into a complete reusable Virtual ECU test bench.

The final system demonstrates:

```text
AUTOSAR model input
        ->
generated minimal RTE/CDD integration
        ->
Trampoline POSIX AUTOSAR OS
        ->
RTI AUTOSAR PSL/PIL
        ->
real DDS/RTPS communication
        ->
runtime semantic monitoring
        ->
memory/stress/fault validation
        ->
Perfetto execution visualization
```

The authoritative AUTOSAR execution model remains based on Trampoline logical OS time. High-resolution host timing is deliberately maintained as a separate profiling domain.

The VirtualBox environment does not provide ECU-equivalent wall-clock real-time timing, and host-side execution durations must not be interpreted as WCET or physical ECU timing. This limitation is understood, characterized, reproducible, and does not affect the functional/integration goals of the Virtual ECU test bench.

Final status:

```text
PHASE 12
FINAL VIRTUAL ECU TEST BENCH

COMPLETE
PASS
GOLDEN
```
