#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$ROOT/build/cmake"

cd "$ROOT"
source "$ROOT/env.sh"

echo "============================================================"
echo "[AUTOSAR] Clean CMake build"
echo "============================================================"

echo "[AUTOSAR] Removing: $BUILD_DIR"
rm -rf "$BUILD_DIR"

echo
echo "============================================================"
echo "[AUTOSAR] CMake configure"
echo "============================================================"

cmake -S "$ROOT" -B "$BUILD_DIR"

echo
echo "[AUTOSAR] CMake configure PASS"
echo

exec "$ROOT/build.sh"
