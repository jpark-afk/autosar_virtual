#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXECUTABLE="$ROOT/build/cmake/autosar_virtual"

cd "$ROOT"
source "$ROOT/env.sh"

if [ ! -x "$EXECUTABLE" ]; then
    echo "[AUTOSAR] ERROR: executable not found:"
    echo "          $EXECUTABLE"
    echo "[AUTOSAR] Run ./clean_build.sh first."
    exit 1
fi

echo "============================================================"
echo "[AUTOSAR] Run Virtual AUTOSAR"
echo "============================================================"

"$EXECUTABLE"

echo
echo "============================================================"
echo "[AUTOSAR] Run completed"
echo "============================================================"
