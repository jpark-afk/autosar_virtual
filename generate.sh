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
echo "[AUTOSAR] Generate Virtual RTE / CDD task integration"
echo "============================================================"

mapfile -t DDS_CDD_CANDIDATES < <(
    find "$ROOT/dds_example" \
        -mindepth 3 \
        -maxdepth 3 \
        -type f \
        -path '*/autosar_gen/DdsCdd.c' \
        | sort
)

if [[ ${#DDS_CDD_CANDIDATES[@]} -ne 1 ]]; then
    echo "ERROR: expected exactly one DDS CDD application under dds_example/"
    echo "Found: ${#DDS_CDD_CANDIDATES[@]}"

    for candidate in "${DDS_CDD_CANDIDATES[@]}"; do
        echo "  $candidate"
    done

    exit 1
fi

DDS_CDD_MAIN="${DDS_CDD_CANDIDATES[0]}"
DDS_CDD_AUTOSAR_GEN_DIR="$(dirname "$DDS_CDD_MAIN")"

echo "[AUTOSAR] CDD source: $DDS_CDD_AUTOSAR_GEN_DIR"

python3 "$ROOT/tools/ddscdd_scanner/scan_ddscdd.py" \
    "$DDS_CDD_AUTOSAR_GEN_DIR" \
    -o "$ROOT/build/ddscdd_scan.json" \
    --rte-output-dir "$ROOT/platform/autosar"

echo "[AUTOSAR] Virtual RTE / CDD task generation PASS"

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
