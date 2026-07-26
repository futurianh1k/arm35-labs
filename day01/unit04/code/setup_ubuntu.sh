#!/usr/bin/env bash
# LAB-04 Ubuntu 24.04 개발환경 일괄 설치 — Legacy(ARM32)와 Modern(AArch64) 동시 구축
# 사용법: bash setup_ubuntu.sh   (sudo 비밀번호 1회 필요, 약 5~10분)
set -eu
echo "[1/4] 패키지 목록 갱신"
sudo apt update
echo "[2/4] 공통 개발 도구"
sudo apt install -y build-essential git make gdb-multiarch python3 python3-pip \
  minicom picocom tree curl unzip
echo "[3/4] 크로스 툴체인 — Modern(AArch64) + Legacy(ARM32)"
sudo apt install -y gcc-aarch64-linux-gnu g++-aarch64-linux-gnu \
  gcc-arm-linux-gnueabihf gcc-arm-none-eabi binutils-arm-none-eabi
echo "[4/4] QEMU — 사용자 모드 + 시스템 모드"
sudo apt install -y qemu-user qemu-user-static qemu-system-arm
echo "----------------------------------------"
echo "[OK] 설치 완료. verify_toolchain.sh로 검증하라."
