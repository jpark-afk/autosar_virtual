# Virtual AUTOSAR Linux PoC

## Phase 0 — PIL ABI / Development Environment Validation

### Host
- OS: Ubuntu Server 26.04.1 LTS
- Architecture: x86_64
- GCC: 13.4.0
- Binutils: 2.46

### RTI Connext DDS Micro
- Version: 4.3.0 ER738
- PIL target: x86_64leElfgcc13.3.0
- PIL library: librti_mezd.a
- Variant: static debug (zd)
- PIL compiler: GCC 13.3.0

### Phase 0 Result
- Repository / Git remote: PASS
- Host architecture: PASS
- Native GCC / binutils: PASS
- PIL archive format: PASS
- PIL object architecture: ELF64 x86-64 little-endian — PASS
- PIL ABI inspection: PASS
- Native relocatable linking: PASS
- Undefined-symbol/dependency enumeration: SKIPPED

### Conclusion
The RTI Micro PIL is compatible with the native x86_64 Linux toolchain.

Phase 0: PASS

Next: Phase 1 — Trampoline POSIX AUTOSAR OS integration.
