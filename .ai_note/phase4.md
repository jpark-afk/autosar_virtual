# Phase 4 - Minimal Generated RTE

## Final Status

```text
PHASE 4: COMPLETE
STATUS: PASS / GOLDEN
```

Phase 4 established a minimal generated RTE layer for the Linux AUTOSAR Virtual PoC. The generator analyzes a supplied DDS CDD AUTOSAR model, builds a semantic intermediate model, and emits only the RTE glue required by the existing Virtual AUTOSAR platform.

The Phase 3 communication foundation remains unchanged:

```text
Mock ASWC
   <-> Generated Minimal RTE
   <-> Generated DDS CDD
   <-> RTI AUTOSAR PSL
   <-> RTI DDS Micro PIL
   <-> Virtual TcpIp
   <-> Trampoline POSIX AUTOSAR OS
```

## Plan Versus Result

| Planned item | Result |
|---|---|
| Phase 4.0 Golden RTE analysis and fixed event model | PASS |
| Phase 4.1 DdsCdd scanner | PASS |
| Phase 4.2 semantic intermediate model | PASS / GOLDEN |
| Phase 4.3-A datatype model | PASS |
| Phase 4.3-B `Rte_Type.h` generation | PASS |
| Phase 4.3-C `Rte_DdsCddType.h` generation | PASS |
| Phase 4.3-D endpoint buffers and Read/Write APIs | PASS |
| Phase 4.3-E DataReceived glue | PASS |
| Phase 4.3-F InternalTrigger to fixed OS mapping | PASS |
| Phase 4.3-G generated build and DDS regression | PASS |
| Phase 4.4 through 4.7 from the original roadmap | Superseded by the completed 4.3 generator integration and final regression |

## Design Boundary

Included:

- CDD ARXML scanning
- Semantic endpoint and runnable discovery
- AUTOSAR datatype extraction
- Normalized intermediate model
- `Rte_Type.h` generation
- `Rte_DdsCddType.h` and `Rte_DdsCddType.c` generation
- Endpoint-based RTE communication buffers
- `Rte_Read_*` and `Rte_Write_*`
- DataReceived pending state and consumption helpers
- Semantic InternalTrigger mapping
- Generated RTE build integration

Excluded by design:

- Full AUTOSAR RTE generation
- Full ECUC, Composition, or ECU Mapping generation
- GUI tooling
- Dynamic OS topology generation
- CDD-specific OIL generation
- QEMU, ARM, FreeRTOS, lwIP, and RTI POSIX PSL

## Semantic Model Rules

- Endpoint identity is `(interface_ref, data_element)`, not the datatype alone.
- Read and Write endpoints are independent; never pair them by list index.
- Generated CDD C/H is the mandatory compile-level source of truth.
- ARXML supplies semantic relationships and event information.
- RTE symbol names must not be split on underscores to guess port/type boundaries.
- Application identifiers such as `PDIO_FL_Domain_6`, `Cabin_Door_PDIO_FL`, and `GCS_LEFT_2_PDIO_FL` are validation data, not generator hardcoding.
- Unresolved endpoints and unsupported relationships must fail explicitly.

## Fixed OS Architecture

The Trampoline POSIX OIL topology is immutable. The generator does not create or modify Tasks, Events, Alarms, Resources, or OIL files.

Supported mappings include:

```text
InternalTrigger -> DdsCddProcessData
                 -> DdsCddProcessData_Task / DdsCddProcessDataEvent

InternalTrigger -> DdsCddTimerUpdate
                 -> DdsCddReadWrite_Task / DdsCddTimerUpdateEvent
```

Unsupported InternalTrigger targets or OS relationships are generator errors rather than reasons to mutate the platform topology.

## Generated RTE Behavior

Each semantic endpoint receives its own communication buffer. Generated APIs provide the CDD-side and ASWC-side Read/Write operations.

For DataReceived behavior:

```text
ASWC Rte_Write
    -> endpoint buffer update
    -> pending flag = TRUE
    -> next fixed CDD periodic dispatch
    -> Rte_ConsumeDataReceived_*
    -> generated CDD Write runnable
    -> DDS output
```

This is the accepted Virtual PoC approximation. No per-port OS object is generated. There is no invented `Rte_IsUpdated` contract for periodic ASWC polling.

## Build and Regression Evidence

The generated RTE was integrated into the real Virtual AUTOSAR executable with:

```bash
python3 tools/ddscdd_scanner/scan_ddscdd.py \
    dds_example/PDIO_FL_Domain_6/autosar_gen \
    -o build/ddscdd_scan.json \
    --rte-output-dir platform/autosar

./generate.sh
./clean_build.sh
./build.sh
./run.sh
```

The generated artifacts compiled and linked with Trampoline POSIX, Virtual TcpIp, RTI AUTOSAR PSL, RTI DDS Micro PIL, generated DDS code, generated CDD code, and the Mock ASWC.

Validated DDS paths:

```text
Windows DDS publisher -> Linux DDS reader -> CDD -> generated RTE -> Mock ASWC: PASS
Mock ASWC -> generated RTE -> CDD -> DDS writer -> Windows DDS subscriber: PASS
```

A known payload value was transmitted and preserved end to end:

```text
PwrDrOpnClsCmd_PDIO_FL: publisher = 7, Mock ASWC = 7
```

The Phase 3 bidirectional DDS Golden baseline is preserved after generated RTE integration and final cleanup.

## Reusable Debugging Lessons

- Validate the complete path incrementally before changing TcpIp, PSL, task priorities, or RTE architecture.
- Do not infer DDS failure from missing application output alone.
- Confirm the actual executable path is `build/cmake/autosar_virtual`.
- Temporary `printf` diagnostics can be affected by definitions in `dds_impl.h`.
- Verify payloads by configuring a known publisher value and comparing publisher, DDS-side, converted RTE, and ASWC values.
- Keep generated CDD source untouched; integration changes belong in RTE, platform, or generator layers.

## Exit Criteria

```text
CDD ARXML scanner                         PASS
Semantic intermediate model               PASS
Datatype generation                       PASS
Rte_Type.h generation                     PASS
Rte_DdsCddType.h generation               PASS
Rte_DdsCddType.c generation               PASS
Endpoint-based RTE buffers                PASS
Independent Read/Write cardinality        PASS
DataReceived state and glue               PASS
InternalTrigger semantic discovery        PASS
Fixed Task/Event mapping                  PASS
Unsupported topology explicit failure     PASS
Generated RTE compile and link            PASS
Windows -> Linux DDS E2E                  PASS
Payload-level RX verification             PASS
Linux -> Windows DDS E2E                  PASS
Phase 3 Golden regression                 PASS
Final clean regression                    PASS
```

## Baseline for Future Work

Phase 4 is now the Golden baseline. Future phases must build on the generated RTE rather than reintroducing the former hand-written RTE implementation. The fixed Phase 3 communication path and OIL topology remain protected architectural constraints.
