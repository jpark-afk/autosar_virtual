# Phase 5 — Cancelled

PHASE 5: CANCELLED / NOT NEEDED

Reason:

- Phase 4 already provides a reusable endpoint-driven Virtual RTE sufficient for the current DDS CDD validation goal.
- The ASWC application ARXML adds useful semantic information, but it does not materially improve the current Virtual AUTOSAR PoC without expanding into a broader AUTOSAR stack.
- The protected architecture and Golden DDS E2E path must remain unchanged.

This plan is intentionally not implemented unless it is explicitly requested again later.
- preserve the fixed OIL topology

Exit condition:

- clean generation and clean build succeed

### Phase 5.6 — Golden DDS Regression

Goal:

- preserve the established Phase 3/4 Golden DDS behavior

Validation paths:

- Windows Publisher -> Linux DDS -> CDD -> generated RTE -> Mock ASWC
- Mock ASWC -> generated RTE -> CDD -> DDS -> Windows Subscriber

Required checks:

- payload verification remains active
- known payload values remain unchanged
- endpoint-specific behavior remains correct

Exit condition:

- both DDS directions remain PASS
- known payload remains preserved

### Phase 5.7 — Negative / Safety Tests

Goal:

- ensure unsupported or ambiguous semantics fail safely rather than being guessed

Validation items:

- same datatype on multiple endpoints
- read/write cardinality mismatch
- unresolved interface/data element
- ambiguous relationship
- unsupported ASWC relationship
- unsupported OS/event mapping

Expected behavior:

- explicit generator failure
- no silent heuristic guessing

Exit condition:

- Phase 5 generates only what is semantically supported and fails predictably for unsupported or ambiguous input

---

## 5. Inputs, Outputs, and Files To Change

### Expected inputs

- generated DDS CDD C/H
- CDD AUTOSAR ARXML
- ASWC application ARXML
- fixed OS platform configuration
- fixed OIL topology

### Expected outputs

Existing outputs retained:

- `Rte_Type.h`
- `Rte_DdsCddType.h`
- `Rte_DdsCddType.c`

Possible Phase 5 additions:

- ASWC-side RTE declarations
- ASWC-side glue or wrapper layer
- extended semantic JSON or intermediate model output

### Likely files to change

- `tools/ddscdd_scanner/scan_ddscdd.py`
- additional modules under `tools/ddscdd_scanner/`
- `generate.sh` if required for integration
- generated outputs in `platform/autosar/`
- Mock ASWC integration code only where strictly necessary
- `.ai_note/phase5.md`

### Protected files and areas

The following must remain protected:

- generated DDS CDD implementation semantics
- RTI DDS Micro PIL
- RTI AUTOSAR PSL
- Virtual TcpIp path
- Trampoline fixed OIL topology
- Phase 3 DDS behavior
- Phase 4 endpoint semantics
- local changes under `third_party/trampoline`

---

## 6. Generator-Time Validation Rules

### 6.1 Cases that must fail explicitly

The generator must fail when:

- `interface_ref` + `data_element` is duplicated or ambiguous
- P-port / R-port mapping is unclear
- CDD endpoint and ASWC endpoint cannot be semantically resolved
- an unsupported `InternalTrigger` target is encountered
- fixed OIL topology changes would be required
- datatype-only matching is attempted
- name-based heuristic inference is used

### 6.2 Acceptable safe behavior

The generator may safely:

- narrow the supported scope to what the ASWC semantic model clearly states
- require explicit configuration or approved mapping metadata when needed
- generate only fully supported endpoints

---

## 7. Conclusion from the Current Repository State

Based on the current repository, the proposed Phase 5 direction is valid, but only in a restricted form.

The exact interpretation is:

- the ASWC application model is a valid semantic input
- the current repository does not provide enough connector/composition data for fully automatic CDD-to-ASWC resolution
- Therefore, Phase 5 should be defined as a minimal semantic integration step, not a full AUTOSAR RTE generator

The practical model is:

1. scan ASWC semantics and normalize them
2. validate supported CDD/ASWC relationships only when they are explicit
3. reject ambiguous or unsupported mappings with explicit generator errors
4. preserve the existing Golden runtime architecture and generated artifacts

This is the most realistic path that keeps the Phase 4 baseline intact while extending the project in a controlled and verifiable direction.

---

## 8. Required Work vs Optional Work

### Required work

- ASWC ARXML semantic analysis
- minimal ASWC model normalization
- safe validation of CDD/ASWC relationships
- generator-level failure policy for unsupported semantics
- minimal RTE extension or contract generation
- clean generation and build validation
- preserve Golden DDS regression

### Optional improvements

- semantic diagnostics improvements
- clearer generator error messages
- additional consistency checks
- documentation cleanup
- more unit test coverage

### Future phases

- general composition/connector support
- broader multi-ASWC support
- full AUTOSAR RTE generation
- dynamic OIL topology generation
- QEMU, ARM, FreeRTOS, and lwIP-related platform expansion

---

## 9. Draft Exit Criteria

The provisional exit criteria for Phase 5 are:

- Phase 4 Golden baseline reconstructed: PASS
- ASWC ARXML scanner: PASS
- ASWC semantic intermediate representation: PASS
- CDD/ASWC endpoint resolution rules defined and validated: PASS
- no datatype-only matching: PASS
- no positional read/write pairing: PASS
- no underscore-based relationship guessing: PASS
- no application hardcoding: PASS
- unified semantic model: PASS
- generated ASWC-side RTE contract (minimal): PASS
- clean generation: PASS
- clean build: PASS
- Golden DDS regression preserved: PASS
- unsupported semantics fail explicitly: PASS

---

## 10. Final Recommendation

Phase 5 should be defined as a minimal ASWC-aware integration extension rather than a general-purpose AUTOSAR RTE generator. The repository evidence shows that application ARXML contains useful semantic information, but not enough connector information to infer full CDD-to-ASWC relationships safely. Because of that, the safe design is to generate only supported, explicitly validated relationships and fail explicitly for everything else.

This keeps the Golden baseline intact, avoids application-specific hardcoding, and gives a realistic next step beyond Phase 4 without overreaching into a broader AUTOSAR toolchain.
