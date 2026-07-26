#!/usr/bin/env bash
# LAB-07 원클릭 부팅 — 빌드 후 QEMU versatilepb로 실행
set -eu
make
echo "== 기대 출력: BOOT → SWI! → BACK 세 줄. 종료: Ctrl-A 다음 X =="
qemu-system-arm -M versatilepb -nographic -audio none -kernel h07.elf
