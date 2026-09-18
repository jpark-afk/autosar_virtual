# Phase 4 Handover Prompt

You are continuing the Linux AUTOSAR Virtual PoC in `/home/jpark/autosar_virtual`.

Read this file before changing anything. Phase 3 is complete and working. Preserve the existing architecture and do not restart the investigation from Phase 0.

## Mission

Continue development above the verified Phase 3 baseline. State one concrete Phase 4 goal before each change, make the smallest local edit, define one PASS criterion, and validate immediately.

The fixed architecture is:

```text
Windows Host DDS application
        <-> UDP/RTPS over enp0s8
192.168.56.1 <-> 192.168.56.105
        <-> Linux virtual AUTOSAR TcpIp
        <-> Trampoline POSIX AUTOSAR OS
        <-> RTI AUTOSAR PSL
        <-> RTI DDS Micro PIL
        <-> DDS CDD / RTE runnable
```

Do not redesign this architecture.

## Explicit Exclusions

Do not return to or introduce:

```text
QEMU
FreeRTOS
lwIP
ARM
32-bit builds
RTI POSIX PSL
```

RTI proprietary sources and libraries are external to this repository. Do not copy, modify, or commit proprietary RTI source. Project adapters and Linux compatibility code belong under `platform/autosar/`.

## Environment

```text
Host: Ubuntu Server 26.04.1 LTS
CPU/ABI: x86_64
Compiler: GCC 13.4.0
RTI: Connext DDS Micro 4.3.0 ER738
RTIMEHOME: $HOME/dds/rti_connext_dds_micro-4.3.0_ER738
PIL library: $RTIMEHOME/lib/x86_64leElfgcc13.3.0
Trampoline: third_party/trampoline
GOIL target: posix
Linux interface: enp0s8
Linux local IP: 192.168.56.105/24
Windows peer IP: 192.168.56.1
Repository: git@github.com:jpark-afk/autosar_virtual.git
```

Start every shell session with:

```bash
cd ~/autosar_virtual
source ./env.sh
```

## Standard Workflow

```bash
./generate.sh
./clean_build.sh
./build.sh
```

`generate.sh` applies the Trampoline POSIX patch and regenerates files from `config/os/autosar_virtual.oil`. Never hand-edit generated files under `autosar_virtual/`.

The build log is `/tmp/autosar_virtual_build.log` when enabled by the scripts.

## Current Source Map

```text
config/os/autosar_virtual.oil
  OIL tasks, alarms, events, resources, priorities, stack sizes

config/os/stub.c
  main, RTI bootstrap task, TcpIp task, read/write task, RX event task

platform/autosar/TcpIp.c
  Linux-backed AUTOSAR TcpIp implementation and DDS socket polling

platform/autosar/TcpIp.h
  Virtual TcpIp types, APIs, LocalAddrId definitions, diagnostic switch

platform/autosar/Rte_Type.h
  Virtual RTE signal types

platform/autosar/Rte_DdsCddType.c/.h
  RTE storage and RX internal trigger to SetEvent

dds_example/autosar_gen/DdsCdd.c
  Generated DDS CDD runnable implementations

dds_example/adaptation/dds_cdd_adapter.c/.h
  DDS CDD adapter, RTI system properties, SocketOwner and RX bridge

dds_example/dds_impl/dds_impl.c/.h
  DDS participant, DataWriter and DataReader operations

dds_example/dds_impl/dds_systemAppgen.c/.h
  Generated RTI AppGen participant/transport configuration

dds_example/dds_gen/
  Generated DDS types, plugins, support and conversions
```

`dds_example` must remain production/integration code only. Do not add temporary test prints, test sockets, or diagnostic markers there. Use `TcpIp_Log()` only when deliberately enabling diagnostics.

## Verified DDS Configuration

`dds_cdd_adapter.c` configures:

```c
system_property.psl_property.timer_resolution_ms = 10;
system_property.psl_property.sync_type = OSAPI_AUTOSAR_SYNCKIND_RESOURCES;
system_property.psl_property.mutex_resource_id = OsResource_DdsMain;
system_property.psl_property.timer_resource_id = OsResource_DdsTimer;
system_property.psl_property.netio_resource_id = OsResource_DdsNetio;
system_property.psl_property.use_socket_owner = TRUE;
system_property.psl_property.get_socket = DdsCdd_GetSocket;
system_property.psl_property.send_data = NULL;
system_property.psl_property.max_local_addr_id = 2;
system_property.psl_property.send_local_addr_id = 0;
system_property.psl_property.number_of_rcv_buffers = 8u;
system_property.psl_property.rcv_buffer_size = 1500u;
system_property.psl_property.use_udp_thread = TRUE;
system_property.psl_property.dds_rxindication = DdsCddRxIndication;
```

Do not randomly change `use_udp_thread`, buffer values, or the three RTI resource IDs. They are coupled to the patched AUTOSAR PSL implementation.

AppGen transport facts are already verified:

```text
initial peer: 0@192.168.56.1
discovery transport: udpv4://
user traffic transport: udpv4://
allow interface: enp0s8
configured address: 192.168.56.105 / 255.255.255.0
DDS receive ports: 8910 and 8911
DDS send port: ephemeral
```

## OIL Baseline

Required resources:

```oil
RESOURCE OsResource_DdsMain { RESOURCEPROPERTY = STANDARD; };
RESOURCE OsResource_DdsTimer { RESOURCEPROPERTY = STANDARD; };
RESOURCE OsResource_DdsNetio { RESOURCEPROPERTY = STANDARD; };
```

Working task priorities and resources:

```text
TcpIp_Task              priority 10; resources OsResource_DdsNetio, OsResource_DdsMain
DdsCddTimerTick_Task    priority 5;  resource OsResource_DdsTimer
DdsCddReadWrite_Task    priority 5;  resources OsResource_DdsMain, OsResource_DdsTimer
DdsCddProcessData_Task  priority 1;  resources OsResource_DdsMain, OsResource_DdsNetio
RTI_Task                priority 1;  resources OsResource_DdsMain, OsResource_DdsTimer
```

Task behavior:

```text
DdsCddReadWrite_Task
  activated by DdsCdd100msAlarm
  ALARMTIME = 1000
  CYCLETIME = 1000
  calls timer update, DDS Writer, DDS Reader

DdsCddProcessData_Task
  AUTOSTART = TRUE
  priority 1
  waits for DdsCddProcessDataEvent
  calls DdsCddProcessData when event is set

TcpIp_Task
  activated every 5 ms
  initializes the virtual TcpIp once
  polls retained DDS sockets
```

Why both resources are needed:

```text
RTI autosarSocket mutex
  OSAPI_Mutex_new()
  -> mutex_resource_id
  -> OsResource_DdsMain

RTI UDP network lock
  UDP_Interface_receive()
  -> self->property.network_lock
  -> netio_resource_id
  -> OsResource_DdsNetio
```

`TcpIp_Task` calls the RX path directly, so it must own both resources. Removing `OsResource_DdsMain` from `TcpIp_Task` breaks valid RX handling.

## Verified Call Chains

Socket acquisition and binding:

```text
DDS participant/UDP transport
 -> NETIO_AutosarSocket_socket()
 -> PortProperty.get_socket
 -> DdsCdd_GetSocket()
 -> TcpIp_TcpIp_DdsCddGetSocket()
 -> socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
 -> TcpIp_Bind()
 -> bind()
```

RX:

```text
TcpIp_Task
 -> TcpIp_PollDdsRx()
 -> recvfrom() on DDS fd 10/11
 -> sockaddr_in conversion
 -> DdsCdd_RxIndication()
 -> NETIO_Autosar_TcpIp_udp_rx_indication()
 -> RTI receive buffer
 -> dds_rxindication = DdsCddRxIndication()
 -> Trigger_DdsCdd_RxIndication()
 -> Rte_IrTrigger_DdsCdd_RxIndication_ITP_DdsCdd_RxIndication()
 -> SetEvent(DdsCddProcessData_Task, DdsCddProcessDataEvent)
 -> DdsCddProcessData_Task
 -> DdsCddProcessData()
 -> NETIO_Autosar_udp_receive_callback()
 -> RTI NETIO/RTPS processing
```

TX:

```text
DdsCddReadWrite_Task
 -> DdsCddWrite_Cabin_Door_PDIO_FL()
 -> DdsCdd_Adapter_Write_Cabin_Door_PDIO_FL()
 -> DdsImpl_Cabin_Door_PDIO_FL_WriteSample()
 -> DDS DataWriter write()
 -> RTI UDP sendmsg/sendto
 -> NETIO_AutosarSocket_sendto/sendmsg()
 -> TcpIp_UdpTransmit()
 -> Linux sendto()
 -> 192.168.56.1
```

## Address and ABI Rules

There is one configured local address:

```text
LocalAddrId 0 = 192.168.56.105
TCPIP_LOCALADDRID_ANY = 0xFF
```

`max_local_addr_id = 2` is an RTI property upper bound, not a count of implemented virtual addresses. `TcpIp_GetIpAddr()` and `TcpIp_Bind()` support LocalAddrId 0.

For IPv4:

```text
sin_addr.s_addr is retained as the network-order 32-bit value
port is converted with ntohs() when building TcpIp_SockAddrInetType
TcpIp_UdpTransmit() converts the AUTOSAR port back with htons()
```

Do not convert addresses based on host-endian display values. For example, log value `0x0138a8c0` represents bytes `C0 A8 38 01`, or `192.168.56.1`.

`TcpIp_SocketIdType` is `uint16` and stores small Linux file descriptors. No pointer is narrowed to 32 bits.

## Runtime Procedure

Normal direct `./run.sh` may exit when ViPER loses terminal input. For a persistent target session use:

```bash
cd ~/autosar_virtual
source ./env.sh
setsid script -q -f -c './run.sh' /tmp/autosar_pty.out >/dev/null 2>&1 &
```

Check readiness:

```bash
ss -lunp | grep -E '192.168.56.105:(8910|8911)'
```

Expected listener state:

```text
192.168.56.105:8910
192.168.56.105:8911
```

The Windows Host DDS test app is prepared by the user and must not be modified. Ask the user to launch it only after these listeners exist.

Force-stop according to the project rule:

```bash
pkill -f autosar_virtual
```

Do not combine that pattern with a command containing the same text if avoiding self-matching is important; run cleanup as a separate command.

## Diagnostics

`TcpIp_Log()` is retained for future use but disabled by default:

```c
#define TCPIP_ENABLE_DIAGNOSTIC_LOG 0
```

It is implemented in `config/os/stub.c`; with the switch disabled, the log file is not opened and the function is a no-op. Temporary diagnostics belong in `/tmp`, not in `dds_example` source output.

Do not print from the 5 ms TcpIp task. ViPER raw terminal mode causes interleaved/corrupted output. If diagnostics are needed, enable the switch deliberately and use low-frequency logs.

## Phase3 Final Status

The user confirmed successful DDS sample exchange in both directions after task priority correction:

```text
Windows Host -> Linux DDS Reader: PASS
Linux DDS Writer -> Windows Host Reader: PASS
RTPS TX through TcpIp_UdpTransmit/sendto: PASS
RTPS RX through TcpIp and RTE event task: PASS
```

Earlier valid RX evidence included:

```text
SocketId=10
domain=2
source=192.168.56.1
valid UDP source port
valid packet length
RTPS payload
```

An RTPS-sized TX boundary was observed:

```text
TcpIp_UdpTransmit socket=9 -> 192.168.56.1:8910
length=440 bytes
sent=440 bytes
```

`tcpdump` was not used as final evidence because the environment lacked `CAP_NET_RAW`. Application-level DDS sample exchange was confirmed with the Windows Host app.

## Phase4 Starting Prompt

```text
Continue Phase4 in /home/jpark/autosar_virtual.

Read .ai_note/phase4.md and .ai_note/phase3.md first. Phase3 is PASS; preserve it and do not redesign the architecture.

Fixed path:
Windows DDS Host 192.168.56.1 <-> Linux 192.168.56.105/enp0s8 <-> virtual AUTOSAR TcpIp <-> Trampoline POSIX <-> RTI AUTOSAR PSL/PIL <-> DDS CDD/RTE.

Do not use QEMU, FreeRTOS, lwIP, ARM, 32-bit, or RTI POSIX PSL. RTI proprietary source/libraries remain outside the repository.

Known working facts:
- DdsCdd_GetSocket reaches Linux socket allocation.
- DDS receive sockets bind on UDP 8910 and 8911.
- TcpIp_Task polls retained nonblocking DDS fds every 5 ms.
- TcpIp_Task priority is 10 and owns OsResource_DdsNetio and OsResource_DdsMain.
- DdsCddProcessData_Task is priority 1, AUTOSTART TRUE, and waits for DdsCddProcessDataEvent.
- DdsCddReadWrite_Task is priority 5 and runs every 1000 ms.
- RTI mutex/timer/netio resources map to DdsMain/DdsTimer/DdsNetio.
- Windows Host and Linux exchanged DDS samples both ways.
- TcpIp_Log exists but is disabled by default with TCPIP_ENABLE_DIAGNOSTIC_LOG 0.

Start by stating one Phase4 goal and one PASS criterion. Inspect only the owning code path, make the smallest edit, and run a focused validation immediately. Check git status before modifying files. Use pkill -f autosar_virtual for forced termination. Do not add temporary diagnostics to dds_example.
```
