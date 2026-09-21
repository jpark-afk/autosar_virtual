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

APP_PID=""

cleanup()
{
    local rc=$?

    trap - INT TERM EXIT

    echo
    echo "[AUTOSAR] Stopping..."

    if [ -n "${APP_PID}" ] && kill -0 "$APP_PID" 2>/dev/null; then
        kill -TERM "$APP_PID" 2>/dev/null || true

        # Also terminate child processes created by the application.
        pkill -TERM -P "$APP_PID" 2>/dev/null || true

        wait "$APP_PID" 2>/dev/null || true
    fi

    # ViPER can remain after the AUTOSAR process exits.
    pkill -TERM -f '[v]iper' 2>/dev/null || true

    echo "[AUTOSAR] Stopped"
    exit "$rc"
}

trap cleanup INT TERM EXIT

echo "============================================================"
echo "[AUTOSAR] Run Virtual AUTOSAR"
echo "============================================================"

"$EXECUTABLE" &
APP_PID=$!

set +e
wait "$APP_PID"
APP_RC=$?
set -e

trap - INT TERM EXIT

echo
echo "============================================================"
echo "[AUTOSAR] Run completed"
echo "============================================================"

exit "$APP_RC"