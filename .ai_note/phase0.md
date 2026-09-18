아래 그대로 `README.md`로 사용하면 돼.

````markdown
# Virtual AUTOSAR Linux PoC — Phase 0

## PIL ABI / Development Environment Validation

## 1. Purpose

Phase 0 verifies that the existing RTI Connext DDS Micro PIL can be used with the native Ubuntu x86_64 development environment before integrating Trampoline and AUTOSAR PSL.

Phase 0 does **not** integrate Trampoline, PSL, DDS CDD, or RTE.

The objective is to establish a validated native Linux toolchain and PIL ABI baseline.

---

## 2. Target Environment

```text
Host OS        : Ubuntu Server 26.04.1 LTS
Host Arch      : x86_64
Compiler       : GCC 13.4.0
Compiler Target: x86_64-linux-gnu
Binutils       : 2.46

RTI Micro      : 4.3.0 ER738
PIL Target     : x86_64leElfgcc13.3.0
PIL Library    : librti_mezd.a
PIL Variant    : static debug (zd)
PIL Compiler   : GCC 13.3.0
```

The following environments are not used:

- QEMU
- FreeRTOS
- lwIP
- ARM
- 32-bit target

---

# 3. Phase 0 Validation Order

## Step 1 — Repository Check

Clone and enter the project repository.

```bash
git clone git@github.com:jpark-afk/autosar_virtual.git
cd autosar_virtual
git status
```

Verify:

- Repository is accessible
- Git branch is valid
- Working tree state is known

---

## Step 2 — Host OS and Architecture

```bash
cat /etc/os-release
uname -m
```

Expected environment:

```text
Ubuntu Server 26.04.x LTS
x86_64
```

Result:

```text
PASS
```

---

## Step 3 — Native Toolchain

Check GCC:

```bash
gcc --version
gcc -dumpmachine
```

Check binutils:

```bash
ld --version
ar --version
nm --version
readelf --version
```

Validated environment:

```text
GCC       : 13.4.0
Target    : x86_64-linux-gnu
Binutils  : 2.46
```

Result:

```text
PASS
```

---

## Step 4 — RTI Environment

The repository uses `env.sh` to define the external RTI installation.

```bash
#!/usr/bin/env bash

export RTIMEHOME="${RTIMEHOME:-$HOME/dds/rti_connext_dds_micro-4.3.0_ER738}"

export RTI_PIL_LIB_DIR="$RTIMEHOME/lib/x86_64leElfgcc13.3.0"
export RTI_PIL_INCLUDE_DIR="$RTIMEHOME/include"
```

Load the environment:

```bash
source ./env.sh
```

The selected RTI compile combination is:

```text
x86_64leElfgcc13.3.0
```

RTI binaries and source remain outside the Git repository.

---

## Step 5 — PIL Archive Validation

The PIL used by this project is:

```text
librti_mezd.a
```

The `zd` static debug variant is used for the PoC.

Check the library:

```bash
ls -lh "$RTI_PIL_LIB_DIR/librti_mezd.a"

file "$RTI_PIL_LIB_DIR/librti_mezd.a"
```

Expected:

```text
current ar archive
```

Result:

```text
PASS
```

---

## Step 6 — PIL Object Architecture

List objects contained in the archive:

```bash
ar t "$RTI_PIL_LIB_DIR/librti_mezd.a" | head
```

Example:

```text
Duration.c.o
BuiltinTopicKey.c.o
Entity.c.o
GUID.c.o
QosPolicy.c.o
RtpsWellKnownPorts.c.o
LocatorSeq.c.o
VendorId.c.o
ProductVersion.c.o
ProtocolVersion.c.o
```

Extract one representative object:

```bash
cd /tmp
ar x "$RTI_PIL_LIB_DIR/librti_mezd.a" Duration.c.o
```

Inspect its ELF header:

```bash
readelf -h /tmp/Duration.c.o
```

Validated ABI:

```text
Class     : ELF64
Data      : Little Endian
OS/ABI    : UNIX - System V
Type      : REL (Relocatable)
Machine   : AMD X86-64
```

Therefore:

```text
PIL  : ELF64 / x86_64 / little-endian
Host : x86_64 Linux
```

Result:

```text
PASS
```

---

## Step 7 — PIL Compiler and Build Flags

Inspect compiler information stored in DWARF:

```bash
readelf --debug-dump=info /tmp/Duration.c.o 2>/dev/null | \
grep -m1 -A3 DW_AT_producer
```

Validated PIL compiler:

```text
GNU C99 13.3.0
```

Recovered compiler options:

```text
-mtune=generic
-march=x86-64
-g
-std=c99
-fsigned-char
-fstrict-aliasing
-fPIC
-fasynchronous-unwind-tables
-fstack-protector-strong
-fstack-clash-protection
-fcf-protection
```

Additional compiler identification:

```bash
readelf -p .comment /tmp/Duration.c.o
```

Validated:

```text
GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
```

Check GNU properties:

```bash
readelf -n /tmp/Duration.c.o
```

Validated properties:

```text
IBT
SHSTK
```

The PIL was built using GCC 13.3.0 while the current host uses GCC 13.4.0.

No ABI incompatibility was identified during Phase 0.

Result:

```text
PASS
```

---

## Step 8 — RTI Public Headers

Check the RTI Micro public include tree:

```bash
ls "$RTI_PIL_INCLUDE_DIR/rti_me"
```

Important interfaces include:

```text
rti_me_c.h
rti_me_psl.h
rti_me_psl/
autosar/
dds_c/
netio/
osapi/
```

Result:

```text
PASS
```

---

## Step 9 — Undefined Symbols / Dependency Enumeration

Full undefined-symbol enumeration using:

```text
nm -u
```

is intentionally skipped in Phase 0.

The existing PIL is treated as a known Linux-capable library.

Full dependency reverse engineering is therefore not performed at this stage.

Dependencies will instead be analyzed when actual linker requirements appear during PSL / Trampoline integration.

Result:

```text
SKIPPED
```

---

## Step 10 — Native x86_64 Linker Validation

Perform a relocatable link of the complete PIL archive:

```bash
ld -r -o /tmp/pil_combined.o \
  --whole-archive "$RTI_PIL_LIB_DIR/librti_mezd.a" \
  --no-whole-archive

echo $?
```

Validated result:

```text
0
```

This confirms that the complete PIL archive can be processed by the native x86_64 GNU linker without architecture or object-format conflicts.

Result:

```text
PASS
```

---

# 4. Phase 0 Final Result

| Validation | Result |
|---|---|
| Repository / Git | PASS |
| Ubuntu environment | PASS |
| x86_64 architecture | PASS |
| Native GCC | PASS |
| GNU binutils | PASS |
| RTI environment | PASS |
| PIL archive format | PASS |
| PIL ELF64 / x86-64 ABI | PASS |
| PIL compiler information | PASS |
| RTI public headers | PASS |
| Undefined-symbol enumeration | SKIPPED |
| Exhaustive dependency classification | SKIPPED |
| Native relocatable linking | PASS |

## Overall Result

```text
PHASE 0: PASS
```

The validated baseline is:

```text
Ubuntu 26.04 x86_64
        |
Native GCC 13.x
        |
RTI Micro x86_64leElfgcc13.3.0
        |
librti_mezd.a
```

No x86_64 ABI or object-format blocker was identified.

---

# 5. Next Phase

Phase 1 introduces Trampoline.

Target architecture:

```text
Application / Runnable
        |
       RTE
        |
     DDS CDD
        |
   RTI Micro PIL
        |
   AUTOSAR PSL
        |
 AUTOSAR OS / TcpIp
        |
 Trampoline POSIX
        |
 Ubuntu Linux
```

Phase 1 first validates Trampoline independently.

Initial Phase 1 goals:

1. Obtain Trampoline source
2. Build Trampoline for POSIX/Linux
3. Generate a minimal AUTOSAR OS configuration
4. Start the OS with `StartOS()`
5. Execute AUTOSAR Tasks
6. Validate Counter / Alarm operation
7. Validate basic AUTOSAR OS APIs

DDS/PIL/PSL integration starts only after the Trampoline baseline is stable.

---

# 6. Phase 0 Milestone

After validation:

```bash
git add README.md env.sh
git commit -m "phase0: record validated RTI Micro environment"
```

This commit represents the validated Phase 0 baseline.
````
