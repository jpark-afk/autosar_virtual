# Phase 3 — DDS CDD and RTPS over Virtual AUTOSAR TcpIp

## Result

**STATUS: PASS**

Phase 3 validated DDS CDD communication over the Linux virtual AUTOSAR path:

```text
DDS CDD
  -> RTI DDS Micro PIL
  -> RTI AUTOSAR PSL
  -> Virtual AUTOSAR TcpIp
  -> Linux UDP
  -> Windows Host DDS application
```

The Windows Host test application exchanged DDS samples in both directions with the Linux target.

## Validated Items

- RTI SocketOwner callback reached `DdsCdd_GetSocket()`.
- Virtual TcpIp allocated Linux UDP sockets for DDS.
- DDS receive sockets bound through `TcpIp_Bind()` on ports 8910 and 8911.
- DDS send socket bound to an ephemeral local port.
- `TcpIp_Task` retained and polled DDS-owned nonblocking sockets.
- Linux `sockaddr_in` converted to `TcpIp_SockAddrInetType`.
- RX indication reached the RTI AUTOSAR NETIO layer.
- RTE `SetEvent()` activated `DdsCddProcessData_Task`.
- `DdsCddProcessData_Task` processed received RTPS data.
- RTPS traffic was transmitted through `TcpIp_UdpTransmit()` and Linux `sendto()`.
- Windows Host and Linux target exchanged DDS samples successfully.
- Required AUTOSAR resources were configured for RTI mutexes and NETIO synchronization.

## Important Fixes

### Local IP assignment

The virtual target calls:

```c
DdsCdd_LocalIpAddrAssignmentChg(
    0U,
    TCPIP_IPADDR_STATE_ASSIGNED);
```

at the beginning of `RTI_Task`, after `StartOS()` has established the OS context. Calling it before `StartOS()` caused a fault.

### Resource ownership

The RTI AUTOSAR implementation uses multiple resources:

```text
mutex_resource_id -> OsResource_DdsMain
netio_resource_id -> OsResource_DdsNetio
timer_resource_id -> OsResource_DdsTimer
```

The working task configuration gives `TcpIp_Task` both `OsResource_DdsNetio` and `OsResource_DdsMain`. This is required because the RX indication path enters RTI AUTOSAR socket code that takes the main mutex resource.

### RX event task priority

The working priority relationship is:

```text
TcpIp_Task              priority 10
DdsCddTimerTick_Task    priority 5
DdsCddReadWrite_Task    priority 5
DdsCddProcessData_Task  priority 1
```

`DdsCddProcessData_Task` is autostarted and waits for `DdsCddProcessDataEvent`.

### Read/write task

The periodic task was renamed:

```text
DdsCdd100ms_Task -> DdsCddReadWrite_Task
```

Its period is now 1000 ms:

```text
ALARMTIME = 1000;
CYCLETIME = 1000;
```

It performs the DDS timer update, Writer operation, and Reader operation.

## Key Runtime Evidence

SocketOwner and bind path:

```text
DdsCdd_GetSocket -> TcpIp_TcpIp_DdsCddGetSocket
TcpIp_Bind PASS: 192.168.56.105:8910
TcpIp_Bind PASS: 192.168.56.105:8911
```

RTPS transmit boundary:

```text
TcpIp_UdpTransmit
  destination: 192.168.56.1:8910
  length: 440 bytes
  sent: 440 bytes
```

The Windows Host application produced valid RTPS traffic, and the Linux target completed the RX event path. The user confirmed DDS samples moved successfully in both directions after the task-priority adjustment.

## Verification Commands

```bash
cd ~/autosar_virtual
source ./env.sh
./generate.sh
./build.sh
./run.sh
```

Runtime sockets can be checked with:

```bash
ss -lunp
```

The runtime process must be stopped with:

```bash
pkill -f autosar_virtual
```

## Cleanup

Temporary runtime diagnostics were removed from `dds_example`. `TcpIp_Log()` remains available for future diagnostics but is disabled by default:

```c
#define TCPIP_ENABLE_DIAGNOSTIC_LOG 0
```

RTI proprietary source and libraries remain outside the repository. `tcpdump` evidence was not collected because the current environment lacks `CAP_NET_RAW`; the application-level DDS sample exchange was verified with the Windows Host application.

## Remaining Non-blocking Work

- Optional packet capture after granting `CAP_NET_RAW`.
- Optional cleanup of compiler macro redefinition warnings between Trampoline and RTI AUTOSAR headers.
- Optional replacement of the minimal virtual TcpIp shim with additional production-specific AUTOSAR behavior.
