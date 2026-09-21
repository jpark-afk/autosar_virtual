# Phase 6 — Generated CDD Task Integration

## Final Status

```text
PHASE 6: COMPLETE

STATUS: PASS / GOLDEN
```

Phase 6 investigated the remaining manual integration work after the Phase 4 Golden baseline.

The investigation showed that the Minimal Generated RTE was already reusable for different DDS CDD endpoints. The more valuable remaining manual dependency was the CDD-specific AUTOSAR OS task implementation in `config/os/task_impl.c`.

Phase 6 therefore implemented generation of the CDD task implementation from the existing CDD semantic model.

The protected Phase 4 communication architecture remains unchanged.

```text
Generated DDS CDD
        |
        v
Generated Virtual RTE
        |
        v
Generated CDD Task Implementation
        |
        v
Fixed Trampoline POSIX AUTOSAR OS
        |
        v
Virtual TcpIp
        |
        v
RTI AUTOSAR PSL
        |
        v
RTI DDS Micro PIL
```

---

## Objective

Reduce manual CDD-specific OS integration while preserving the fixed Virtual AUTOSAR OS architecture.

The objective was intentionally narrow:

* generate CDD-specific Task implementations
* keep Task/Event/Runnable control flow visible
* remove CDD-specific Task code from the generic application task file
* integrate generation into the normal project generation flow
* preserve the Phase 4 Golden DDS behavior

No general AUTOSAR OS generator was introduced.

---

## Investigation Result

Phase 4 already provided reusable endpoint-driven RTE generation.

The following investigation confirmed that:

* the scanner contains no application-specific hardcoded names
* endpoint identity is based on `(interface_ref, data_element)`
* ASWC R-Port and P-Port information is already scanned
* CDD Runnable and Event relationships are already available
* the existing generated RTE can adapt to the discovered endpoints

Therefore, creating another ASWC-side RTE abstraction was not considered necessary.

The practical reusable gap was the manual CDD Task implementation.

---

## Before Phase 6

CDD-specific Tasks were manually implemented in:

```text
config/os/task_impl.c
```

The file contained:

```text
DdsCddTimerTick_Task
DdsCddReadWrite_Task
DdsCddProcessData_Task
```

This mixed generic Virtual AUTOSAR application infrastructure with CDD-specific scheduling and Runnable dispatch logic.

Replacing the DDS CDD therefore required manual modification of the generic task implementation.

---

## Phase 6 Result

CDD-specific Task implementations are now generated into:

```text
platform/autosar/DdsCdd_Task.c
```

The generated file contains the actual AUTOSAR OS Task implementation.

Example structure:

```text
DdsCddTimerTick_Task
    |
    +-- DdsCddTimerTick()

DdsCddReadWrite_Task
    |
    +-- WaitEvent()
    |
    +-- DdsCddTimerUpdate()
    |
    +-- Rte_ConsumeDataReceived_*
    |
    +-- DdsCddWrite_*
    |
    +-- DdsCddRead_*

DdsCddProcessData_Task
    |
    +-- WaitEvent()
    |
    +-- DdsCddProcessData()
```

The Task control flow is intentionally visible directly in the generated source.

No wrapper function was introduced around the Task implementation.

---

## Generated File

```text
platform/autosar/DdsCdd_Task.c
```

The generated source contains:

* CDD Runnable declarations
* `DdsCddTimerTick_Task`
* `DdsCddReadWrite_Task`
* `DdsCddProcessData_Task`
* AUTOSAR `WaitEvent`
* AUTOSAR `GetEvent`
* AUTOSAR `ClearEvent`
* direct CDD Runnable calls
* DataReceived consumption

The fixed OS topology remains defined by the existing OIL configuration.

The generator does not create or modify:

* Tasks
* Events
* Alarms
* Counters
* OIL topology

---

## Generator Changes

The existing scanner:

```text
tools/ddscdd_scanner/scan_ddscdd.py
```

was extended to generate the CDD Task source.

The generator already had access to:

* CDD RTE dependencies
* CDD Runnable information
* TimingEvent information
* DataReceivedEvent information
* InternalTrigger information
* fixed OS mapping

The new Task generation uses these semantic results rather than application-specific names.

---

## Generated RTE / Task Outputs

The generation step now produces:

```text
build/ddscdd_scan.json

platform/autosar/Rte_Type.h
platform/autosar/Rte_DdsCddType.h
platform/autosar/Rte_DdsCddType.c
platform/autosar/DdsCdd_Task.c
```

The semantic intermediate model remains the central generator representation.

---

## Generate Workflow

`generate.sh` now automatically discovers the DDS CDD:

```text
dds_example/*/autosar_gen/DdsCdd.c
```

Exactly one CDD is required.

The generation flow is:

```text
apply_patches.sh
        |
        v
discover DDS CDD
        |
        v
scan_ddscdd.py
        |
        +--> ddscdd_scan.json
        +--> Rte_Type.h
        +--> Rte_DdsCddType.h
        +--> Rte_DdsCddType.c
        +--> DdsCdd_Task.c
        |
        v
GOIL
        |
        v
Trampoline POSIX OS
```

If zero or multiple DDS CDD applications are found, generation fails explicitly.

---

## Build Integration

`CMakeLists.txt` now includes:

```text
platform/autosar/DdsCdd_Task.c
```

The generic task implementation remains responsible for generic infrastructure such as:

```text
RTI_Task
TcpIp_Task
App_Task
```

CDD-specific Tasks are no longer implemented there.

---

## Generic Task Separation

After Phase 6:

```text
config/os/task_impl.c
```

contains no CDD-specific Task implementation.

The following CDD Task definitions were removed:

```text
TASK(DdsCddTimerTick_Task)
TASK(DdsCddReadWrite_Task)
TASK(DdsCddProcessData_Task)
```

CDD-specific scheduling and dispatch now belong to the generated artifact.

This creates a cleaner separation:

```text
Generic platform/application infrastructure
    -> config/os/task_impl.c

CDD-specific generated OS integration
    -> platform/autosar/DdsCdd_Task.c
```

---

## Fixed Scheduling Assumption

The Virtual AUTOSAR PoC uses a fixed OS topology.

The current periodic configuration is intentionally fixed.

In particular:

```text
DdsCddReadWriteAlarm
    -> fixed 1-second period
```

Dynamic timing or general scheduling generation is not part of Phase 6.

---

## Protected Architecture

The following remain unchanged:

* Phase 3 DDS communication path
* Phase 4 generated RTE endpoint semantics
* endpoint identity `(interface_ref, data_element)`
* DataReceived behavior
* InternalTrigger semantic mapping
* fixed Trampoline POSIX OIL topology
* RTI AUTOSAR PSL
* RTI DDS Micro PIL
* Virtual TcpIp
* generated DDS CDD source

No manual modification was made to the generated DDS CDD implementation.

---

## Validation

### Generator

```text
generate.sh
    PASS

CDD discovery
    PASS

Virtual RTE generation
    PASS

CDD Task generation
    PASS

GOIL generation
    PASS
```

Generated artifacts were successfully recreated:

```text
build/ddscdd_scan.json
platform/autosar/Rte_Type.h
platform/autosar/Rte_DdsCddType.h
platform/autosar/Rte_DdsCddType.c
platform/autosar/DdsCdd_Task.c
```

### Build

```text
CMake configure
    PASS

Compilation
    PASS

Link
    PASS
```

### DDS Golden Regression

The existing bidirectional DDS communication was preserved.

```text
Windows DDS publisher
    ->
Linux DDS reader
    ->
CDD
    ->
Generated RTE
    ->
Mock ASWC

PASS
```

```text
Mock ASWC
    ->
Generated RTE
    ->
CDD
    ->
DDS writer
    ->
Windows DDS subscriber

PASS
```

Known payload verification remained successful.

---

## Reusability Result

Phase 6 improves CDD replacement/re-generation workflow.

For a new generated DDS CDD, the intended flow is now:

```text
Replace generated CDD
        |
        v
Run generate.sh
        |
        +--> discover CDD
        +--> scan CDD
        +--> generate RTE
        +--> generate CDD Tasks
        +--> generate Trampoline OS
        |
        v
build.sh
```

The generic application task implementation does not need to contain CDD-specific Task code.

This is the main practical reuse improvement delivered by Phase 6.

---

## Out of Scope

Phase 6 does not provide:

* full AUTOSAR RTE generation
* full ECUC generation
* Composition generation
* ECU Mapping generation
* dynamic OIL generation
* dynamic Task/Event creation
* general-purpose AUTOSAR scheduling generation
* automatic ASWC composition resolution
* QEMU integration
* ARM/FreeRTOS integration
* lwIP integration
* RTI POSIX PSL replacement

---

## Exit Criteria

```text
Phase 4 Golden baseline preserved             PASS
CDD-specific Task generation                  PASS
DdsCdd_Task.c generated                       PASS
Generic task_impl.c CDD Task removal         PASS
CMake generated Task integration              PASS
generate.sh automatic CDD discovery           PASS
generate.sh scanner integration               PASS
GOIL generation                               PASS
Clean build                                   PASS
DDS bidirectional E2E                         PASS
Payload-level validation                      PASS
Fixed OS topology preserved                   PASS
No generated CDD source modification          PASS
No application-specific generator hardcoding  PASS
```

---

## Final Conclusion

Phase 6 is complete.

The most useful remaining manual integration point after Phase 4 was identified as the CDD-specific AUTOSAR OS Task implementation.

That implementation is now generated from the existing CDD semantic information.

The result is:

```text
CDD ARXML / Generated CDD
        |
        v
Semantic Scanner
        |
        +--> Generated RTE
        |
        +--> Generated CDD Tasks
        |
        v
Fixed Virtual AUTOSAR OS
```

The Phase 4 Golden communication architecture remains intact.

Phase 6 therefore establishes the current Golden baseline for future work.
