#!/usr/bin/env bash
# LAB-04 툴체인 검증 — 트리플릿과 버전을 증거로 남긴다
set -u
O=toolchain_report.txt
{
echo "=== 툴체인 검증 $(date '+%F %T') ==="
for c in gcc aarch64-linux-gnu-gcc arm-linux-gnueabihf-gcc arm-none-eabi-gcc; do
  if command -v $c >/dev/null 2>&1; then
    echo "[OK ] $c"
    echo "      triplet : $($c -dumpmachine)"
    echo "      version : $($c --version | head -1)"
  else
    echo "[MISS] $c"
  fi
done
echo "--- QEMU ---"
for q in qemu-aarch64 qemu-arm qemu-system-arm; do
  command -v $q >/dev/null 2>&1 && echo "[OK ] $q $($q --version | head -1 | grep -o 'version [0-9.]*')" || echo "[MISS] $q"
done
} | tee "$O"
echo "[OK] 저장: $O"
