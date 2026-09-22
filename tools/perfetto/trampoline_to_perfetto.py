#!/usr/bin/env python3

import argparse
import importlib.util
import json
from pathlib import Path


PID_TASK = 1
PID_ALARM = 2
PID_EVENT = 3
PID_RESOURCE = 4


# Perfetto/Chrome trace reserves tid=0 effectively as the process-level
# track in some views. Keep AUTOSAR IDs unchanged semantically, but use
# 1-based display track IDs so task/alarm/event/resource ID 0 remains
# visible as a normal named thread.
def task_tid(entity_id):
    return int(entity_id) + 1


def alarm_tid(entity_id):
    return int(entity_id) + 1


def perfetto_event_tid(entity_id):
    return int(entity_id) + 1


def resource_tid(entity_id):
    return int(entity_id) + 1


def load_runtime_monitor(path):
    spec = importlib.util.spec_from_file_location("runtime_monitor", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def add_process_name(events, pid, name):
    events.append({
        "name": "process_name",
        "ph": "M",
        "pid": pid,
        "tid": 0,
        "args": {"name": name},
    })


def add_thread_name(events, pid, tid, name):
    events.append({
        "name": "thread_name",
        "ph": "M",
        "pid": pid,
        "tid": tid,
        "args": {"name": name},
    })


def main():
    parser = argparse.ArgumentParser(
        description=(
            "Convert Linux AUTOSAR Trampoline trace "
            "to semantic Perfetto/Chrome Trace JSON"
        )
    )

    parser.add_argument("trace")
    parser.add_argument("--static-info", required=True)
    parser.add_argument(
        "--runtime-monitor",
        default="tools/runtime_monitor/runtime_monitor.py",
    )
    parser.add_argument(
        "-o",
        "--output",
        default="perfetto_trace.json",
    )
    parser.add_argument(
        "--tick-us",
        type=int,
        default=1000,
        help="Trampoline counter tick duration in microseconds",
    )

    args = parser.parse_args()

    rm = load_runtime_monitor(args.runtime_monitor)

    static_info = rm.StaticInfo(args.static_info)
    deriver = rm.RuntimeDeriver(static_info)

    events = []
    running = {}

    raw_count = 0
    derived_count = 0
    warning_count = 0
    trace_incomplete = False
    last_ts = 0
    last_hires_us = None

    def ts_us(ts):
        return int(ts) * args.tick_us

    def instant(name, category, ts, pid, tid, extra=None):
        e = {
            "name": name,
            "cat": category,
            "ph": "i",
            "s": "t",
            "ts": ts_us(ts),
            "pid": pid,
            "tid": tid,
        }

        if extra:
            e["args"] = extra

        events.append(e)

    def begin(name, category, ts, pid, tid, extra=None):
        e = {
            "name": name,
            "cat": category,
            "ph": "B",
            "ts": ts_us(ts),
            "pid": pid,
            "tid": tid,
        }

        if extra:
            e["args"] = extra

        events.append(e)

    def end(ts, pid, tid):
        events.append({
            "ph": "E",
            "ts": ts_us(ts),
            "pid": pid,
            "tid": tid,
        })

    def hires_us(record):
        value = record.get("hires_ts_ns")

        if value is None:
            return None

        return int(value) / 1000.0

    def begin_hires(name, category, timestamp_us, pid, tid, extra=None):
        e = {
            "name": name,
            "cat": category,
            "ph": "B",
            "ts": timestamp_us,
            "pid": pid,
            "tid": tid,
        }

        if extra:
            e["args"] = extra

        events.append(e)

    def end_hires(timestamp_us, pid, tid):
        events.append({
            "ph": "E",
            "ts": timestamp_us,
            "pid": pid,
            "tid": tid,
        })

    def instant_hires(name, category, timestamp_us, pid, tid, extra=None):
        e = {
            "name": name,
            "cat": category,
            "ph": "i",
            "s": "t",
            "ts": timestamp_us,
            "pid": pid,
            "tid": tid,
        }

        if extra:
            e["args"] = extra

        events.append(e)

    # ------------------------------------------------------------
    # Semantic process groups
    # ------------------------------------------------------------

    add_process_name(events, PID_TASK, "AUTOSAR Tasks")
    add_process_name(events, PID_ALARM, "AUTOSAR Alarms")
    add_process_name(events, PID_EVENT, "AUTOSAR Events")
    add_process_name(events, PID_RESOURCE, "AUTOSAR Resources")

    # ------------------------------------------------------------
    # Task tracks
    # configured tasks + Trampoline POSIX idle
    # ------------------------------------------------------------

    task_count = len(static_info.tasks)

    for tid in range(task_count + 1):
        add_thread_name(
            events,
            PID_TASK,
            task_tid(tid),
            static_info.task_name(tid),
        )

    # ------------------------------------------------------------
    # Alarm tracks
    # timeobj_id == static alarm index
    # ------------------------------------------------------------

    for alarm_id, alarm in enumerate(static_info.alarms):
        add_thread_name(
            events,
            PID_ALARM,
            alarm_tid(alarm_id),
            alarm.get("NAME", f"timeobj#{alarm_id}"),
        )

    # ------------------------------------------------------------
    # Resource tracks
    # res_id == static resource index
    # ------------------------------------------------------------

    for resource_id, resource in enumerate(static_info.resources):
        add_thread_name(
            events,
            PID_RESOURCE,
            resource_tid(resource_id),
            resource.get("NAME", f"resource#{resource_id}"),
        )

    # ------------------------------------------------------------
    # Event tracks
    #
    # Event masks are not globally unique:
    #   mask 1 may mean different things for different tasks.
    #
    # Therefore create one semantic track per:
    #   (task_id, event_mask, event_name)
    # ------------------------------------------------------------

    event_track = {}
    next_event_tid = 0

    for task_id, task in enumerate(static_info.tasks):
        for ref in task.get("EVENT", []):
            event_name = ref.get("VALUE")

            if not event_name:
                continue

            event_info = static_info.events_by_name.get(event_name)

            if event_info is None:
                continue

            mask = event_info.get("MASK")

            key = (task_id, mask, event_name)

            if key in event_track:
                continue

            tid = next_event_tid
            next_event_tid += 1

            event_track[key] = tid

            add_thread_name(
                events,
                PID_EVENT,
                perfetto_event_tid(tid),
                f"{task.get('NAME', f'task#{task_id}')}:{event_name}",
            )

    def resolve_event_track(task_id, mask, event_name):
        if event_name is not None:
            key = (task_id, mask, event_name)

            if key in event_track:
                return event_track[key]

        # Defensive fallback.
        for (tid_task, tid_mask, tid_name), tid in event_track.items():
            if tid_task == task_id and tid_mask == mask:
                return tid

        return 10000 + int(task_id or 0)

    # ------------------------------------------------------------
    # Trace conversion
    # ------------------------------------------------------------

    for record in rm.iter_trace_records(args.trace):

        if record.get("_kind") != "raw":
            warning_count += 1

            if record.get("warning") == "INCOMPLETE_RECORD_AT_EOF":
                trace_incomplete = True

            continue

        raw_count += 1
        last_ts = record.get("ts", last_ts)

        # All runtime trace records share the same CLOCK_MONOTONIC
        # timeline. The original Trampoline "ts" remains the
        # authoritative AUTOSAR OS tick used by runtime_monitor.
        # Perfetto visualization uses one CLOCK_MONOTONIC timeline
        # for all runtime records. The original "ts" remains the
        # authoritative AUTOSAR OS tick for runtime_monitor.
        record_hires_us = hires_us(record)

        if record_hires_us is not None:
            last_hires_us = record_hires_us

        for d in deriver.process(record):
            derived_count += 1

            typ = d["derived_type"]
            ts = d["ts"]

            # ----------------------------------------------------
            # TASK
            # ----------------------------------------------------

            if typ in (
                "DISPATCH_NEW",
                "DISPATCH_READY",
                "WAKEUP_DISPATCH",
                "RESUME",
            ):
                task_id = d["task_id"]
                tid = task_tid(task_id)

                if tid in running:
                    previous = running[tid]

                    if previous["hires"] and record_hires_us is not None:
                        end_hires(record_hires_us, PID_TASK, tid)
                    else:
                        end(ts, PID_TASK, tid)

                use_hires = record_hires_us is not None

                if use_hires:
                    begin_hires(
                        "RUNNING",
                        "autosar.task",
                        record_hires_us,
                        PID_TASK,
                        tid,
                        {
                            "task": d.get("task"),
                            "dispatch": typ,
                            "timing": "CLOCK_MONOTONIC",
                        },
                    )

                    instant_hires(
                        typ,
                        "autosar.task.dispatch",
                        record_hires_us,
                        PID_TASK,
                        tid,
                        {"task": d.get("task")},
                    )
                else:
                    begin(
                        "RUNNING",
                        "autosar.task",
                        ts,
                        PID_TASK,
                        tid,
                        {
                            "task": d.get("task"),
                            "dispatch": typ,
                        },
                    )

                    instant(
                        typ,
                        "autosar.task.dispatch",
                        ts,
                        PID_TASK,
                        tid,
                        {"task": d.get("task")},
                    )

                running[tid] = {
                    "ts": ts,
                    "hires": use_hires,
                }

            elif typ in ("PREEMPT", "WAIT", "TERMINATE"):
                task_id = d["task_id"]
                tid = task_tid(task_id)

                if tid in running:
                    previous = running[tid]

                    if previous["hires"] and record_hires_us is not None:
                        end_hires(record_hires_us, PID_TASK, tid)
                    else:
                        end(ts, PID_TASK, tid)

                    running.pop(tid, None)

                if record_hires_us is not None:
                    instant_hires(
                        typ,
                        "autosar.task.state",
                        record_hires_us,
                        PID_TASK,
                        tid,
                        {"task": d.get("task")},
                    )
                else:
                    instant(
                        typ,
                        "autosar.task.state",
                        ts,
                        PID_TASK,
                        tid,
                        {"task": d.get("task")},
                    )

            elif typ in ("ACTIVATE", "WAKEUP"):
                if record_hires_us is not None:
                    instant_hires(
                        typ,
                        "autosar.task.state",
                        record_hires_us,
                        PID_TASK,
                        task_tid(d["task_id"]),
                        {
                            "task": d.get("task"),
                            "autosar_task_id": d["task_id"],
                        },
                    )
                else:
                    instant(
                        typ,
                        "autosar.task.state",
                        ts,
                        PID_TASK,
                        task_tid(d["task_id"]),
                        {
                            "task": d.get("task"),
                            "autosar_task_id": d["task_id"],
                        },
                    )

            # ----------------------------------------------------
            # ALARM
            # ----------------------------------------------------

            elif typ == "ALARM_EXPIRE":
                alarm_name = d.get("alarm", "UNKNOWN_ALARM")
                alarm_id = d.get("timeobj_id", 0)

                (instant_hires if record_hires_us is not None else instant)(
                    "EXPIRE",
                    "autosar.alarm",
                    record_hires_us if record_hires_us is not None else ts,
                    PID_ALARM,
                    alarm_tid(alarm_id),
                    {
                        "autosar_alarm_id": alarm_id,
                        "alarm": alarm_name,
                        "action": d.get("action"),
                        "target": d.get("target"),
                    },
                )

            # ----------------------------------------------------
            # EVENT
            # ----------------------------------------------------

            elif typ in ("EVENT_SET", "EVENT_RESET"):
                task_id = d.get("task_id", 0)
                mask = d.get("event_mask")
                event_name = d.get("event")

                if not event_name:
                    event_name = static_info.event_name(task_id, mask)

                event_tid = resolve_event_track(
                    task_id,
                    mask,
                    event_name,
                )

                (instant_hires if record_hires_us is not None else instant)(
                    "SET" if typ == "EVENT_SET" else "RESET",
                    "autosar.event",
                    record_hires_us if record_hires_us is not None else ts,
                    PID_EVENT,
                    perfetto_event_tid(event_tid),
                    {
                        "event": event_name or f"mask={mask}",
                        "task": d.get("task"),
                        "mask": mask,
                    },
                )

            # ----------------------------------------------------
            # RESOURCE
            # ----------------------------------------------------

            elif typ in (
                "RESOURCE_ACQUIRE",
                "RESOURCE_RELEASE",
            ):
                resource_id = d.get(
                    "resource_id",
                    d.get("res_id", 0),
                )

                (instant_hires if record_hires_us is not None else instant)(
                    "ACQUIRE"
                    if typ == "RESOURCE_ACQUIRE"
                    else "RELEASE",
                    "autosar.resource",
                    record_hires_us if record_hires_us is not None else ts,
                    PID_RESOURCE,
                    resource_tid(resource_id),
                    {
                        "autosar_resource_id": resource_id,
                        "resource": d.get("resource"),
                        "owner": d.get("owner"),
                    },
                )

    # ------------------------------------------------------------
    # Close RUNNING slices at capture boundary
    # ------------------------------------------------------------

    for tid in list(running):
        previous = running[tid]

        if previous["hires"] and last_hires_us is not None:
            end_hires(last_hires_us, PID_TASK, tid)
        else:
            end(last_ts, PID_TASK, tid)

    final_records = deriver.finalize(trace_incomplete)

    derived_count += len(final_records)

    # ------------------------------------------------------------
    # Output
    # ------------------------------------------------------------

    output = {
        "traceEvents": events,
        "displayTimeUnit": "ms",
        "metadata": {
            "schema": "linux-autosar-perfetto-v2",
            "source": "Linux AUTOSAR Trampoline POSIX",
            "raw_records": raw_count,
            "derived_records": derived_count,
            "parser_warnings": warning_count,
            "trace_incomplete": trace_incomplete,
            "tick_us": args.tick_us,
        },
    }

    Path(args.output).write_text(
        json.dumps(output, indent=2),
        encoding="utf-8",
    )

    print(f"OUTPUT={args.output}")
    print(f"RAW_RECORDS={raw_count}")
    print(f"DERIVED_RECORDS={derived_count}")
    print(f"PARSER_WARNINGS={warning_count}")
    print(
        "TRACE_INCOMPLETE="
        + ("yes" if trace_incomplete else "no")
    )
    print(f"PERFETTO_EVENTS={len(events)}")
    print(f"TASK_TRACKS={task_count + 1}")
    print(f"ALARM_TRACKS={len(static_info.alarms)}")
    print(f"EVENT_TRACKS={len(event_track)}")
    print(f"RESOURCE_TRACKS={len(static_info.resources)}")


if __name__ == "__main__":
    main()
