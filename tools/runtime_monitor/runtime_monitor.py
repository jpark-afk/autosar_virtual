#!/usr/bin/env python3

import argparse
import json
import signal
import sys

signal.signal(signal.SIGPIPE, signal.SIG_DFL)


SUPPORTED_TYPES = {
    "proc",
    "resource",
    "timeobj",
    "timeobj_expire",
    "set_event",
    "reset_event",
}



class StaticInfo:
    def __init__(self, path):
        with open(path, "r") as f:
            self.data = json.load(f)

        self.tasks = self.data.get("task", [])
        self.resources = self.data.get("resource", [])
        self.alarms = self.data.get("alarm", [])
        self.events = self.data.get("event", [])

        self.events_by_name = {
            event.get("NAME"): event
            for event in self.events
            if event.get("NAME")
        }

    def task_name(self, proc_id):
        if 0 <= proc_id < len(self.tasks):
            return self.tasks[proc_id].get(
                "NAME",
                f"proc#{proc_id}"
            )

        # Trampoline POSIX exposes idle after configured tasks.
        if proc_id == len(self.tasks):
            return "idle"

        return f"proc#{proc_id}"

    def resource_name(self, res_id):
        if 0 <= res_id < len(self.resources):
            return self.resources[res_id].get(
                "NAME",
                f"resource#{res_id}"
            )

        return f"resource#{res_id}"

    def alarm_name(self, timeobj_id):
        if 0 <= timeobj_id < len(self.alarms):
            return self.alarms[timeobj_id].get(
                "NAME",
                f"timeobj#{timeobj_id}"
            )

        return f"timeobj#{timeobj_id}"

    def alarm_info(self, timeobj_id):
        if not (0 <= timeobj_id < len(self.alarms)):
            return {
                "name": f"timeobj#{timeobj_id}",
                "action": "UNKNOWN",
                "target": None,
            }

        alarm = self.alarms[timeobj_id]

        name = alarm.get(
            "NAME",
            f"timeobj#{timeobj_id}"
        )

        action = alarm.get("ACTION", "UNKNOWN")
        action_s = alarm.get("ACTION_S", {})

        target = None

        if action == "ACTIVATETASK":
            target = action_s.get("TASK")

        elif action == "SETEVENT":
            task = action_s.get("TASK")
            event = action_s.get("EVENT")

            if task and event:
                target = f"{task}:{event}"
            else:
                target = task or event

        return {
            "name": name,
            "action": action,
            "target": target,
        }

    def event_name(self, task_id, mask):
        if not (0 <= task_id < len(self.tasks)):
            return None

        task = self.tasks[task_id]

        for ref in task.get("EVENT", []):
            name = ref.get("VALUE")
            event = self.events_by_name.get(name)

            if event is not None and event.get("MASK") == mask:
                return name

        return None

class MemoryInfo:
    def __init__(self, path, static_info):
        with open(path, "r") as f:
            self.data = json.load(f)

        if self.data.get("schema") != "phase9-memory-v1":
            raise ValueError(
                f"unsupported memory schema: "
                f"{self.data.get('schema')}"
            )

        self.static_info = static_info
        self.task_stack = self.data.get("task_stack", [])
        self.process = self.data.get("process", {})
        self.glibc = self.data.get("glibc", {})

        self._validate()

    def _validate(self):
        task_count = len(self.static_info.tasks)

        for task in self.task_stack:
            task_id = task.get("task_id")

            if not isinstance(task_id, int) or not (
                0 <= task_id < task_count
            ):
                raise ValueError(
                    f"invalid memory task_id: {task_id}"
                )

            required = (
                "allocated_bytes",
                "used_high_water_bytes",
                "free_high_water_bytes",
            )

            for key in required:
                if key not in task:
                    raise ValueError(
                        f"missing task stack field: {key}"
                    )

            allocated = task["allocated_bytes"]
            used = task["used_high_water_bytes"]
            free = task["free_high_water_bytes"]

            if allocated != used + free:
                raise ValueError(
                    f"inconsistent task stack usage "
                    f"for task_id={task_id}: "
                    f"allocated={allocated} "
                    f"used={used} free={free}"
                )

        for key in (
            "vm_rss_kb",
            "vm_hwm_kb",
            "vm_size_kb",
            "vm_data_kb",
        ):
            if key not in self.process:
                raise ValueError(
                    f"missing process memory field: {key}"
                )

        for key in (
            "arena_bytes",
            "used_bytes",
            "free_bytes",
            "mmap_bytes",
        ):
            if key not in self.glibc:
                raise ValueError(
                    f"missing glibc memory field: {key}"
                )

    def print_report(self, stack_warn_percent=None):
        print()
        print("MEMORY")

        print("  TASK_STACK")

        stack_warnings = []

        for task in self.task_stack:
            task_id = task.get("task_id", -1)
            name = self.static_info.task_name(task_id)

            allocated = task["allocated_bytes"]
            used = task["used_high_water_bytes"]
            free = task["free_high_water_bytes"]

            utilization = (
                used * 100.0 / allocated
                if allocated > 0
                else 0.0
            )

            print(
                f"    {name} "
                f"allocated={allocated} "
                f"used={used} "
                f"free={free} "
                f"utilization={utilization:.1f}%"
            )

            if (
                stack_warn_percent is not None
                and utilization >= stack_warn_percent
            ):
                stack_warnings.append(
                    (name, utilization)
                )

        print("  PROCESS")
        print(
            f"    VmRSS={self.process.get('vm_rss_kb')} kB "
            f"VmHWM={self.process.get('vm_hwm_kb')} kB "
            f"VmSize={self.process.get('vm_size_kb')} kB "
            f"VmData={self.process.get('vm_data_kb')} kB"
        )

        print("  GLIBC")
        print(
            f"    arena={self.glibc.get('arena_bytes')} bytes "
            f"used={self.glibc.get('used_bytes')} bytes "
            f"free={self.glibc.get('free_bytes')} bytes "
            f"mmap={self.glibc.get('mmap_bytes')} bytes"
        )

        if stack_warn_percent is not None:
            print()
            print("MEMORY_WARNINGS")

            if not stack_warnings:
                print("  none")
            else:
                for name, utilization in stack_warnings:
                    print(
                        f"  STACK {name} "
                        f"utilization={utilization:.1f}% "
                        f"threshold={stack_warn_percent:.1f}%"
                    )

def iter_trace_records(path):
    """
    Incrementally parse Trampoline POSIX trace.json.

    The trace is a JSON array, but external termination may leave the
    array without its closing bracket or may leave a partial final object.

    Complete objects are yielded in original file order.
    Incomplete trailing data is reported separately and is not treated
    as a runtime error.
    """
    buffer = []
    inside_object = False
    sequence = 0

    with open(path, "r", errors="replace") as f:
        for line_no, line in enumerate(f, 1):
            stripped = line.strip()

            if not inside_object:
                if stripped.startswith("{"):
                    buffer = [line]
                    inside_object = True

                # Ignore [, ], commas and other array framing.
                continue

            buffer.append(line)

            # Current Trampoline trace objects are flat JSON objects.
            # A line containing '}' completes the current object.
            if "}" not in stripped:
                continue

            text = "".join(buffer).strip()

            # Objects inside the JSON array normally end with ','.
            if text.endswith(","):
                text = text[:-1].rstrip()

            try:
                obj = json.loads(text)

                # Trampoline POSIX JSON trace serializes numeric values
                # as JSON strings. Normalize known numeric fields here
                # so all downstream monitor logic receives integers.
                for key in (
                    "ts",
                    "proc_id",
                    "res_id",
                    "timeobj_id",
                    "target_task_id",
                    "event",
                    "target_state",
                ):
                    if key in obj:
                        obj[key] = int(obj[key])

            except (json.JSONDecodeError, ValueError, TypeError) as exc:
                yield {
                    "_kind": "parser_warning",
                    "sequence": sequence,
                    "line": line_no,
                    "warning": "MALFORMED_RECORD",
                    "detail": str(exc),
                }
            else:
                obj["_kind"] = "raw"
                obj["sequence"] = sequence
                yield obj

            sequence += 1
            buffer = []
            inside_object = False

    if inside_object and buffer:
        yield {
            "_kind": "parser_warning",
            "sequence": sequence,
            "warning": "INCOMPLETE_RECORD_AT_EOF",
        }



def format_raw(record, static_info=None):
    if record["_kind"] == "parser_warning":
        return (
            f"seq={record['sequence']:<8} "
            f"WARNING {record['warning']}"
        )

    typ = record.get("type", "unknown")
    ts = record.get("ts", "?")
    fields = []

    if "proc_id" in record:
        pid = record["proc_id"]
        name = (
            static_info.task_name(pid)
            if static_info is not None
            else None
        )
        fields.append(
            f"proc_id={pid}"
            + (f"({name})" if name else "")
        )

    if "res_id" in record:
        rid = record["res_id"]
        name = (
            static_info.resource_name(rid)
            if static_info is not None
            else None
        )
        fields.append(
            f"res_id={rid}"
            + (f"({name})" if name else "")
        )

    if "timeobj_id" in record:
        oid = record["timeobj_id"]
        name = (
            static_info.alarm_name(oid)
            if static_info is not None
            else None
        )
        fields.append(
            f"timeobj_id={oid}"
            + (f"({name})" if name else "")
        )

    if "target_task_id" in record:
        tid = record["target_task_id"]
        name = (
            static_info.task_name(tid)
            if static_info is not None
            else None
        )
        fields.append(
            f"target_task_id={tid}"
            + (f"({name})" if name else "")
        )

    if "event" in record:
        mask = record["event"]

        event_name = None

        if (
            static_info is not None
            and "target_task_id" in record
        ):
            event_name = static_info.event_name(
                record["target_task_id"],
                mask,
            )

        fields.append(
            f"event={mask}"
            + (f"({event_name})" if event_name else "")
        )

    if "target_state" in record:
        fields.append(
            f"target_state={record['target_state']}"
        )

    return (
        f"seq={record['sequence']:<8} "
        f"ts={str(ts):<8} "
        f"type={typ:<16} "
        + " ".join(fields)
    ).rstrip()


PROC_STATES = {
    0: "SUSPENDED",
    1: "READY",
    2: "RUNNING",
    3: "WAITING",
    4: "AUTOSTART",
    5: "READY_AND_NEW",
}


class RuntimeDeriver:
    """
    Stateful interpretation of normalized Trampoline trace records.

    Raw records remain authoritative.

    Derived information includes:
      - task lifecycle
      - currently running task
      - resource owner context
      - event reset task context

    These associations are inferred from original record order.
    """

    def __init__(self, static_info):
        self.static_info = static_info

        self.task_state = {}
        self.ready_reason = {}

        self.running_task = None

        # resource_id -> stack/list of derived owner task IDs.
        # A list is used so malformed or nested observations can be
        # represented without destroying previous state.
        self.resource_owners = {}

    def _base(self, record, kind):
        return {
            "_kind": "derived",
            "sequence": record.get("sequence"),
            "ts": record.get("ts"),
            "derived_type": kind,
        }

    def process(self, record):
        if record.get("_kind") != "raw":
            return []

        typ = record.get("type")

        if typ == "proc":
            return self._process_proc(record)

        if typ == "resource":
            return self._process_resource(record)

        if typ == "set_event":
            return self._process_set_event(record)

        if typ == "reset_event":
            return self._process_reset_event(record)

        if typ == "timeobj_expire":
            return self._process_alarm(record)

        return []

    def _process_proc(self, record):
        pid = record.get("proc_id")
        new_state = record.get("target_state")
        old_state = self.task_state.get(pid)

        task = self.static_info.task_name(pid)

        derived = []

        def emit(kind, detail=None):
            item = self._base(record, kind)
            item["task_id"] = pid
            item["task"] = task

            if detail is not None:
                item["detail"] = detail

            derived.append(item)

        if new_state == 5:
            emit("ACTIVATE")
            self.ready_reason[pid] = "NEW"

        elif old_state == 5 and new_state == 2:
            emit("DISPATCH_NEW")
            self.ready_reason.pop(pid, None)

        elif old_state == 2 and new_state == 1:
            emit("PREEMPT")
            self.ready_reason[pid] = "PREEMPTED"

        elif old_state == 3 and new_state == 1:
            emit("WAKEUP")
            self.ready_reason[pid] = "WAKEUP"

        elif new_state == 2 and old_state == 1:
            reason = self.ready_reason.pop(pid, None)

            if reason == "PREEMPTED":
                emit("RESUME")

            elif reason == "WAKEUP":
                emit("WAKEUP_DISPATCH")

            else:
                emit(
                    "DISPATCH_READY",
                    "ready origin not established",
                )

        elif old_state == 2 and new_state == 3:
            emit("WAIT")

        elif old_state == 2 and new_state == 0:
            emit("TERMINATE")

        # Maintain current running-task context.
        if new_state == 2:
            self.running_task = pid

        elif (
            self.running_task == pid
            and new_state in (0, 1, 3)
        ):
            self.running_task = None

        self.task_state[pid] = new_state

        return derived

    def _process_resource(self, record):
        rid = record.get("res_id")
        state = record.get("target_state")

        resource = self.static_info.resource_name(rid)

        item = self._base(
            record,
            "RESOURCE_ACQUIRE"
            if state == 1
            else "RESOURCE_RELEASE"
        )

        item["resource_id"] = rid
        item["resource"] = resource

        if state == 1:
            owner = self.running_task

            self.resource_owners.setdefault(rid, []).append(owner)

        else:
            owners = self.resource_owners.get(rid, [])

            if owners:
                owner = owners.pop()
            else:
                owner = None
                item["detail"] = "release without observed acquire"

        item["owner_task_id"] = owner
        item["owner"] = (
            self.static_info.task_name(owner)
            if owner is not None
            else "UNKNOWN"
        )

        return [item]

    def _process_alarm(self, record):
        oid = record.get("timeobj_id")
        info = self.static_info.alarm_info(oid)

        item = self._base(record, "ALARM_EXPIRE")

        item["timeobj_id"] = oid
        item["alarm"] = info["name"]
        item["action"] = info["action"]
        item["target"] = info["target"]

        return [item]

    def _process_set_event(self, record):
        tid = record.get("target_task_id")
        mask = record.get("event")

        item = self._base(record, "EVENT_SET")

        item["task_id"] = tid
        item["task"] = self.static_info.task_name(tid)
        item["event_mask"] = mask

        name = self.static_info.event_name(tid, mask)

        item["event_name"] = (
            name if name is not None else "UNKNOWN"
        )

        return [item]

    def _process_reset_event(self, record):
        mask = record.get("event")
        tid = self.running_task

        item = self._base(record, "EVENT_RESET")

        item["task_id"] = tid
        item["task"] = (
            self.static_info.task_name(tid)
            if tid is not None
            else "UNKNOWN"
        )

        item["event_mask"] = mask

        name = (
            self.static_info.event_name(tid, mask)
            if tid is not None
            else None
        )

        item["event_name"] = (
            name if name is not None else "UNKNOWN"
        )

        return [item]


    def finalize(self, trace_incomplete):
        """
        Produce end-of-capture diagnostics.

        An open resource at an incomplete trace boundary is not
        classified as a runtime resource leak.
        """
        diagnostics = []

        for rid, owners in self.resource_owners.items():
            for owner in owners:
                resource = self.static_info.resource_name(rid)

                owner_name = (
                    self.static_info.task_name(owner)
                    if owner is not None
                    else "UNKNOWN"
                )

                diagnostics.append({
                    "resource": resource,
                    "owner": owner_name,
                    "status": (
                        "INCOMPLETE_AT_EOF"
                        if trace_incomplete
                        else "OPEN_RESOURCE_AT_COMPLETE_EOF"
                    ),
                })

        return diagnostics

def format_derived(record):
    prefix = (
        f"seq={record['sequence']:<8} "
        f"ts={str(record['ts']):<8} "
        f"DERIVED "
        f"{record['derived_type']:<18}"
    )

    typ = record["derived_type"]

    if typ == "ALARM_EXPIRE":
        body = (
            f"alarm={record['alarm']} "
            f"action={record['action']} "
            f"target={record['target'] or 'NONE'}"
        )

    elif typ.startswith("RESOURCE_"):
        body = (
            f"resource={record['resource']} "
            f"owner={record['owner']}"
        )

    elif typ in ("EVENT_SET", "EVENT_RESET"):
        body = (
            f"task={record['task']} "
            f"event={record['event_name']} "
            f"mask={record['event_mask']}"
        )

    else:
        body = f"task={record.get('task', 'UNKNOWN')}"

    if record.get("detail"):
        body += f" detail={record['detail']}"

    return prefix + " " + body

def main():
    parser = argparse.ArgumentParser(
        description="Linux AUTOSAR Trampoline runtime trace monitor"
    )

    parser.add_argument(
        "trace",
        nargs="?",
        default="trace.json",
        help="Trampoline POSIX trace file (default: trace.json)",
    )

    parser.add_argument(
        "--static-info",
        default="autosar_virtual/tpl_static_info.json",
        help="Generated Trampoline static-info JSON",
    )

    parser.add_argument(
        "--memory",
        default=None,
        help="Optional Phase 9 memory snapshot JSON",
    )
    parser.add_argument(
        "--stack-warn-percent",
        type=float,
        default=None,
        help="Warn when task stack high-water utilization reaches this percent",
    )

    parser.add_argument(
        "--derived",
        action="store_true",
        help="Print derived task lifecycle records instead of raw records",
    )

    parser.add_argument(
        "--limit",
        type=int,
        default=30,
        help="Maximum number of records to print (0 = unlimited)",
    )

    args = parser.parse_args()

    if (
        args.stack_warn_percent is not None
        and not (0.0 < args.stack_warn_percent <= 100.0)
    ):
        parser.error(
            "--stack-warn-percent must be greater than 0 "
            "and less than or equal to 100"
        )

    static_info = StaticInfo(args.static_info)
    deriver = RuntimeDeriver(static_info)

    printed = 0
    raw_count = 0
    warning_count = 0
    derived_count = 0
    trace_incomplete = False

    for record in iter_trace_records(args.trace):
        if record["_kind"] == "raw":
            raw_count += 1
        else:
            warning_count += 1

            if record.get("warning") == "INCOMPLETE_RECORD_AT_EOF":
                trace_incomplete = True

        derived_records = deriver.process(record)
        derived_count += len(derived_records)

        if args.derived:
            for derived in derived_records:
                if args.limit == 0 or printed < args.limit:
                    print(format_derived(derived))
                    printed += 1
        else:
            if args.limit == 0 or printed < args.limit:
                print(format_raw(record, static_info))
                printed += 1

    diagnostics = deriver.finalize(trace_incomplete)

    memory_info = None

    if args.memory is not None:
        memory_info = MemoryInfo(
            args.memory,
            static_info,
        )

    print()
    print(
        f"SUMMARY raw_records={raw_count} "
        f"derived_records={derived_count} "
        f"parser_warnings={warning_count} "
        f"trace_incomplete={'yes' if trace_incomplete else 'no'}"
    )

    if memory_info is not None:
        memory_info.print_report(
            stack_warn_percent=args.stack_warn_percent
        )

    if diagnostics:
        print("EOF_DIAGNOSTICS")

        for d in diagnostics:
            print(
                f"  resource={d['resource']} "
                f"owner={d['owner']} "
                f"status={d['status']}"
            )


if __name__ == "__main__":
    main()
