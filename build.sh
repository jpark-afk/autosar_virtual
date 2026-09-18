#!/usr/bin/env bash
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$ROOT/build/cmake"
LOG="/tmp/autosar_virtual_build.log"

cd "$ROOT"
source "$ROOT/env.sh"

if [ ! -f "$BUILD_DIR/CMakeCache.txt" ]; then
    echo "[AUTOSAR] ERROR: CMake is not configured."
    echo "[AUTOSAR] Run ./clean_build.sh first."
    exit 1
fi

echo "============================================================"
echo "[AUTOSAR] Incremental build"
echo "============================================================"
echo "[AUTOSAR] Log: $LOG"
echo

cmake --build "$BUILD_DIR" -j"$(nproc)" 2>&1 | tee "$LOG"
STATUS=${PIPESTATUS[0]}

if [ "$STATUS" -eq 0 ]; then
    echo
    echo "============================================================"
    echo "[AUTOSAR] Build PASS"
    echo "============================================================"
    exit 0
fi

echo
echo "============================================================"
echo "[AUTOSAR] Build FAILED"
echo "============================================================"

echo
echo "----- First compiler error -----"
grep -n -m1 -B5 -A10 'error:' "$LOG" || true

echo
echo "----- Undefined references -----"
grep "undefined reference" "$LOG" \
    | sed 's/.*undefined reference to //g' \
    | sort -u || true

echo
echo "[AUTOSAR] Full log: $LOG"

exit "$STATUS"
