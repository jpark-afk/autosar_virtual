#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"

source "$ROOT/env.sh"

echo "============================================================"
echo "[AUTOSAR] Apply project patches"
echo "============================================================"
"$ROOT/apply_patches.sh"

echo
echo "============================================================"
echo "[AUTOSAR] Generate Trampoline OS with GOIL"
echo "============================================================"

"$GOIL" \
    --log-file-read \
    --templates="$GOIL_TEMPLATES" \
    --target=posix \
    config/os/autosar_virtual.oil

echo
echo "[AUTOSAR] GOIL generation PASS"
