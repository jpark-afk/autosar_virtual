# Phase 10 - Stress / Fault Injection

## Status

```text
PHASE 9: COMPLETE / PASS / GOLDEN
PHASE 10: OPEN / DRAFT
CURRENT SUBPHASE: 10.1 Fault Injection Capability / Test Matrix
```

## Objective

Validate that the Linux AUTOSAR Virtual PoC can create bounded,
deterministic stress and fault conditions, observe their expected effects
through the existing OS, trace, and memory mechanisms, and produce
reproducible PASS/FAIL evidence.

Phase 10 preserves the established Golden architecture:

```text
Application / Mock ASWC
        -> Generated Minimal RTE
        -> Generated DDS CDD
        -> RTI AUTOSAR PSL
        -> RTI DDS Micro PIL
        -> Virtual AUTOSAR TcpIp
        -> Trampoline POSIX AUTOSAR OS
        -> Linux / ViPER
```

This phase is not intended to create random crashes or uncontrolled
corruption. Every injection must be intentional, bounded, reproducible,
observable, removable, and clearly separated from production behavior.

## Golden Baseline

The following behavior remains protected during Phase 10:

```text
clean generation and build                 PASS
Virtual AUTOSAR runtime                    PASS
Windows <-> Virtual AUTOSAR DDS            PASS
UDP / RTPS transport                       PASS
Phase 8 trace generation and monitoring    PASS / GOLDEN
Phase 9 stack and memory monitoring        PASS / GOLDEN
```

The existing Trampoline POSIX 1 ms timer dependency is a pre-existing
Golden requirement and must not be reverted:

```text
third_party/trampoline/machines/posix/tpl_machine_posix.c
tpl_viper_start_auto_timer(signal_for_counters, 1000);
```

Generated AUTOSAR artifacts must not be edited manually. Production task
priorities, DDS transport, TcpIp architecture, generated RTE/CDD
semantics, and Trampoline scheduler behavior remain unchanged unless an
experiment proves a change necessary.

## Observation Mechanisms

Use existing project-owned mechanisms first:

```text
AUTOSAR OS errors       Phase 7 ErrorHook record
scheduling and events   trace.json + runtime_monitor.py
task stack              Phase9_StackMonitor_GetUsage()
process memory          Phase9_ProcessMemory_GetUsage()
memory snapshot         Phase9_MemorySnapshot_WriteJson()
DDS behavior            existing Windows <-> Virtual AUTOSAR test
```

`ErrorHook` must remain minimal. It must not perform printf, file I/O,
socket I/O, blocking, dynamic allocation, or heavy monitoring.

## Phase 10.1 - Capability Matrix

No code changes are made before the capability investigation. Inspect the
existing Phase 7 fault/error infrastructure, task implementation, OIL
configuration, and project-owned test hooks first.

| Candidate | Classification | Expected observation | Initial risk | Trampoline modification |
| --- | --- | --- | --- | --- |
| Controlled over-activation | FAULT / AUTOSAR LOGICAL | `E_OS_LIMIT`, service ID, ErrorHook count, trace continuation | Low | None expected |
| Illegal resource access or release | FAULT / AUTOSAR LOGICAL | `E_OS_ACCESS` or `E_OS_NOFUNC`, ErrorHook evidence | Low | None expected |
| Bounded task workload | STRESS | changed dispatch/preemption timing and trace activity | Low | None expected |
| Bounded stack consumer | STRESS / HOST ARTIFACT | increased task stack high-water and reduced free bytes | Medium | None expected |
| Bounded allocation burst | STRESS / HOST ARTIFACT | process and glibc memory observations, cleanup | Medium | None expected |
| Event or message burst | STRESS / AUTOSAR LOGICAL | wakeup/dispatch trace activity and continuation | Medium | None expected |
| DDS/network burst | STRESS / DDS/NETWORK | communication continuity, trace, stack, and memory effects | Medium | None expected |

The smallest safe initial matrix should select one deterministic OS fault
first, preferably an existing Phase 7-derived condition that has a clear
ErrorHook result and allows runtime continuation.

## Experiment Evidence Format

Each experiment records:

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

An experiment is PASS only when the expected effect is produced and
observed through the intended mechanism. Process survival alone is not a
PASS criterion.

## Safety and Cleanup Rules

Do not add arbitrary pointer corruption, random memory writes, scheduler
corruption, uncontrolled recursion, infinite CPU loops, uncontrolled
native stack overflow, or host process termination as a substitute for
AUTOSAR fault handling.

Test-only behavior must be explicit, bounded, disableable, and removed or
cleanly isolated after validation. One meaningful experiment is run at a
time, followed by focused evidence collection and Golden regression.

## Next Step

Perform Phase 10.1 inspection only:

```bash
cd ~/autosar_virtual
git status --short
rg -n "ErrorHook|OSErrorGetServiceId|E_OS_LIMIT|E_OS_ACCESS|E_OS_NOFUNC|GetResource|ReleaseResource|ActivateTask|SetEvent|STACKSIZE|TASK\(" \
    platform dds_example config autosar_virtual CMakeLists.txt
```

The inspection result will determine the first real injection. Do not
implement multiple injections before that matrix is confirmed.

## Final Phase 10 Completion Criteria

Phase 10 can close only after selected fault and stress experiments are
reproducible, bounded, observable, cleaned up, and followed by a passing
Golden regression covering runtime, DDS, Phase 8 trace, and Phase 9
memory monitoring.

The final completion artifact must be an actual Markdown file named:

```text
phase10_<final>.md
```