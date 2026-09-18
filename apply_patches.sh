#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TRAMPOLINE="$ROOT/third_party/trampoline"
PATCH="$ROOT/patches/trampoline-posix-1ms-systemcounter.patch"

echo "[PATCH] Checking Trampoline POSIX 1ms SystemCounter patch..."

if git -C "$TRAMPOLINE" apply --reverse --check "$PATCH" >/dev/null 2>&1; then
    echo "[PATCH] Already applied"
elif git -C "$TRAMPOLINE" apply --check "$PATCH" >/dev/null 2>&1; then
    git -C "$TRAMPOLINE" apply "$PATCH"
    echo "[PATCH] Applied"
else
    echo "[PATCH] ERROR: patch cannot be applied"
    exit 1
fi
