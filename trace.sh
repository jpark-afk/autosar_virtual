#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT_DIR"

TRACE_FILE="${1:-trace.json}"

STATIC_INFO="autosar_virtual/tpl_static_info.json"
MONITOR="tools/runtime_monitor/runtime_monitor.py"
PERFETTO_EXPORTER="tools/perfetto/trampoline_to_perfetto.py"

RUNTIME_OUTPUT="${RUNTIME_OUTPUT:-runtime.txt}"
PERFETTO_OUTPUT="${PERFETTO_OUTPUT:-perfetto_trace.json}"

echo "============================================================"
echo "[AUTOSAR] Runtime Trace Post-Processing"
echo "============================================================"
echo "Trace       : $TRACE_FILE"
echo "Static info : $STATIC_INFO"
echo

# --------------------------------------------------------------------------
# Input validation
# --------------------------------------------------------------------------

if [[ ! -f "$TRACE_FILE" ]]; then
    echo "ERROR: trace file not found: $TRACE_FILE"
    exit 1
fi

if [[ ! -f "$STATIC_INFO" ]]; then
    echo "ERROR: static info not found: $STATIC_INFO"
    exit 1
fi

if [[ ! -f "$MONITOR" ]]; then
    echo "ERROR: runtime monitor not found: $MONITOR"
    exit 1
fi

if [[ ! -f "$PERFETTO_EXPORTER" ]]; then
    echo "ERROR: Perfetto exporter not found: $PERFETTO_EXPORTER"
    exit 1
fi

# --------------------------------------------------------------------------
# 1. AUTOSAR semantic runtime trace
# --------------------------------------------------------------------------

echo "------------------------------------------------------------"
echo "[1/2] Generating derived AUTOSAR runtime trace"
echo "------------------------------------------------------------"

python3 "$MONITOR" \
    "$TRACE_FILE" \
    --static-info "$STATIC_INFO" \
    --derived \
    --limit 0 \
    > "$RUNTIME_OUTPUT"

echo "Generated: $RUNTIME_OUTPUT"

# --------------------------------------------------------------------------
# 2. Perfetto trace
# --------------------------------------------------------------------------

echo
echo "------------------------------------------------------------"
echo "[2/2] Generating Perfetto trace"
echo "------------------------------------------------------------"

python3 "$PERFETTO_EXPORTER" \
    "$TRACE_FILE" \
    --static-info "$STATIC_INFO" \
    -o "$PERFETTO_OUTPUT"

# --------------------------------------------------------------------------
# Summary
# --------------------------------------------------------------------------

echo
echo "============================================================"
echo "[AUTOSAR] Trace Post-Processing Complete"
echo "============================================================"
echo "Raw trace     : $TRACE_FILE"
echo "Derived trace : $RUNTIME_OUTPUT"
echo "Perfetto trace: $PERFETTO_OUTPUT"

echo
echo "===== TRACE SUMMARY ====="
tail -5 "$RUNTIME_OUTPUT"
