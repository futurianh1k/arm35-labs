#!/usr/bin/env bash
# LAB-02 시스템 해부 스크립트 — 내 앞의 기계는 MCU/MPU/SoC/SBC 중 무엇인가
# 사용법: bash sysinfo.sh   (RPi4와 개발 PC 양쪽에서 실행해 결과를 비교한다)
set -u
O=sysinfo_$(hostname)_$(date +%m%d_%H%M).txt
{
echo "=== 시스템 해부 리포트 · $(hostname) · $(date '+%F %T') ==="
echo "--- 1) 커널과 아키텍처 ---"
uname -a
echo "--- 2) CPU ---"
lscpu 2>/dev/null | grep -E 'Architecture|Model name|CPU\(s\)|MHz|Cache|Vendor' || cat /proc/cpuinfo | head -30
echo "--- 3) 메모리 ---"
free -h
echo "--- 4) 저장 장치 ---"
lsblk -o NAME,SIZE,TYPE,MOUNTPOINT 2>/dev/null | head -15
echo "--- 5) SoC/디바이스트리 모델명 (임베디드 보드에서만 존재) ---"
if [ -r /proc/device-tree/model ]; then tr -d '\0' </proc/device-tree/model; echo;
else echo "(device-tree 없음: PC급 시스템으로 판정)"; fi
echo "--- 6) 부팅 후 경과·부하 ---"
uptime
echo "--- 7) 온도 (라즈베리파이) ---"
command -v vcgencmd >/dev/null && vcgencmd measure_temp || echo "(vcgencmd 없음)"
echo "=== 끝. 이 파일을 evidence/ 폴더로 복사해 커밋한다 ==="
} | tee "$O"
echo "[OK] 저장: $O"
