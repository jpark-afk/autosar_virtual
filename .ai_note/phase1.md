# Phase 1 — Trampoline POSIX AUTOSAR OS Integration

## Goal

Validate a minimal AUTOSAR OS environment on Ubuntu x86_64 using Trampoline POSIX before integrating RTI PSL, PIL, or DDS.

Validated items:

- Trampoline source integration
- GOIL build
- POSIX/Linux code generation
- Trampoline application build
- ViPER build and execution
- `StartOS()`
- Basic Task execution
- `SystemCounter`
- Cyclic and one-shot Alarm
- Periodic Task activation
- Extended Task / Event handling
- `ShutdownOS()`

**Result: PASS**

---

## 1. Trampoline Source

Trampoline is managed as a Git submodule.

Repository:

```text
https://github.com/TrampolineRTOS/trampoline.git
```

Project location:

```text
third_party/trampoline
```

Validated revision:

```text
ff2870232
```

After cloning the main project, initialize the submodule with:

```bash
git submodule update --init --recursive
```

---

## 2. Build GOIL

GOIL is the OIL compiler used by Trampoline.

Build:

```bash
cd ~/autosar_virtual/third_party/trampoline/goil/makefile-unix
./build.py
```

Validated result:

```text
[100%] Linking for Unix (debug): goil-debug
Done
```

Generated executables:

```text
goil/makefile-unix/goil
goil/makefile-unix/goil-debug
```

**Result: PASS**

---

## 3. Build ViPER

The Trampoline POSIX target uses ViPER (Virtual Processor EmulatoR).

ViPER provides the simulated timer used by the Trampoline `SystemCounter`.

Build:

```bash
cd ~/autosar_virtual/third_party/trampoline/viper
make
```

Set the environment variable:

```bash
export VIPER_PATH="$HOME/autosar_virtual/third_party/trampoline/viper"
```

The project `env.sh` should provide this environment variable.

Load the project environment with:

```bash
source ~/autosar_virtual/env.sh
```

Without `VIPER_PATH`, a POSIX application fails with:

```text
Error: VIPER_PATH is not defined. Exiting
Exiting virtual platform.
```

**Result: PASS**

---

## 4. Basic AUTOSAR OS Task Test

Example:

```text
third_party/trampoline/examples/posix/one_task
```

### Generate

```bash
cd ~/autosar_virtual/third_party/trampoline/examples/posix/one_task

../../../goil/makefile-unix/goil \
  --target=posix/linux \
  --templates=../../../goil/templates/ \
  one_task.oil
```

Expected result:

```text
No warning, no error.
```

### Build

```bash
./make.py
```

Validated build result:

```text
[100%] Linking one_task_exe
```

### Run

```bash
source ~/autosar_virtual/env.sh
./one_task_exe
```

Validated output:

```text
Hello World
```

This verifies:

```text
main()
  |
StartOS()
  |
AUTOSAR Task
  |
Trampoline POSIX
  |
Linux
```

**Result: PASS**

---

## 5. Stopping Trampoline / ViPER

The `one_task` example does not automatically terminate after printing `Hello World`.

Normally stop it with:

```text
Ctrl+C
```

If Trampoline or ViPER processes remain:

```bash
pkill -f one_task_exe
pkill -f viper
```

Verify that no process remains:

```bash
ps aux | grep -E 'one_task_exe|viper' | grep -v grep
```

No output means all processes have terminated.

---

## 6. Periodic Task / SystemCounter / Alarm Test

Example:

```text
third_party/trampoline/examples/posix/periodic
```

The example uses `SystemCounter` and a cyclic Alarm.

Main configuration:

```text
SystemCounter
    |
one_second Alarm
    |
ACTIVATETASK
    |
my_periodic_task
```

The Alarm configuration uses:

```text
ALARMTIME = 100
CYCLETIME = 100
```

A second one-shot Alarm activates the `stop` Task at tick `1000`.

### Generate

```bash
cd ~/autosar_virtual/third_party/trampoline/examples/posix/periodic

../../../goil/makefile-unix/goil \
  --target=posix/linux \
  --templates=../../../goil/templates/ \
  periodic.oil
```

### Build

```bash
./make.py
```

### Run

```bash
source ~/autosar_virtual/env.sh
./periodic_exe
```

Validated output:

```text
Activation #1
Activation #2
Activation #3
Activation #4
Activation #5
Activation #6
Activation #7
Activation #8
Activation #9
Shutdown
Exiting virtual platform.
```

Validated periodic execution path:

```text
ViPER timer
    |
SystemCounter
    |
cyclic Alarm
    |
ActivateTask()
    |
my_periodic_task
    |
TerminateTask()
```

Validated shutdown path:

```text
one-shot Alarm
    |
stop Task
    |
CancelAlarm()
    |
ShutdownOS()
```

This confirms that Trampoline POSIX provides a working timer source for the AUTOSAR `SystemCounter`.

**Result: PASS**

---

## 7. Extended Task / Event Test

Example:

```text
third_party/trampoline/examples/posix/events
```

Unlike the periodic example, the Alarm does not directly activate the worker Task.

Instead:

```text
SystemCounter
    |
Alarm
    |
SetEvent(ev_act)
    |
Extended Task
```

The Task is AUTOSTARTed and waits for events.

Main Task flow:

```text
WaitEvent()
    |
GetEvent()
    |
ClearEvent()
    |
Application processing
```

### Generate

```bash
cd ~/autosar_virtual/third_party/trampoline/examples/posix/events

../../../goil/makefile-unix/goil \
  --target=posix/linux \
  --templates=../../../goil/templates/ \
  events.oil
```

### Build

```bash
./make.py
```

### Run

```bash
source ~/autosar_virtual/env.sh
./events_exe
```

Validated output:

```text
Activation #1
Activation #2
Activation #3
Activation #4
Activation #5
Activation #6
Activation #7
Activation #8
Activation #9
Activation #10
Exiting virtual platform.
```

Validated event execution path:

```text
ViPER timer
    |
SystemCounter
    |
one_second Alarm
    |
SetEvent(ev_act)
    |
WaitEvent() returns
    |
GetEvent()
    |
ClearEvent(ev_act)
```

Validated stop sequence:

```text
stopper Alarm
    |
ActivateTask(stop)
    |
CancelAlarm(one_second)
    |
SetEvent(my_periodic_task, ev_stop)
    |
WaitEvent() returns
    |
ClearEvent(ev_stop)
    |
ShutdownOS()
```

The final number of `Activation` messages can depend on scheduling at the tick where the cyclic Alarm and stopper Alarm coincide.

The observed run produced 10 activations.

**Result: PASS**

---

## 8. AUTOSAR OS APIs Validated

The following AUTOSAR OS APIs/mechanisms were successfully exercised:

```text
StartOS()

TASK()
TerminateTask()

SystemCounter

Alarm
ActivateTask()
CancelAlarm()

WaitEvent()
GetEvent()
ClearEvent()
SetEvent()

ShutdownOS()
```

---

## 9. Validated Architecture

Phase 1 validates the following execution environment:

```text
AUTOSAR Application
        |
   AUTOSAR OS API
        |
     Trampoline
        |
    POSIX Target
        |
       ViPER
        |
  Ubuntu x86_64
```

ViPER supplies the simulated timer required for `SystemCounter`.

Trampoline supplies the AUTOSAR OS API.

The complete environment runs natively on Ubuntu x86_64.

---

## 10. Scope Confirmation

The following were intentionally NOT used in Phase 1:

- QEMU
- FreeRTOS
- lwIP
- ARM
- 32-bit environment
- RTI DDS Micro integration
- RTI PIL integration
- RTI PSL integration

Phase 1 was intentionally limited to validating the AUTOSAR OS foundation.

---

# Phase 1 Final Result

```text
Trampoline source        PASS
GOIL build               PASS
OIL code generation      PASS
POSIX/Linux build        PASS
ViPER build              PASS
StartOS()                PASS
Basic Task               PASS
SystemCounter            PASS
Cyclic Alarm             PASS
Periodic Task            PASS
Extended Task            PASS
AUTOSAR Event API        PASS
ShutdownOS()             PASS
```

**Phase 1: PASS**

Next phase:

**Phase 2 — RTI AUTOSAR PSL integration with Trampoline**

