#!/usr/bin/env bash
# LAB-03 메모리 계층 실측 보조 — 캐시·메모리 정보 수집
set -u
O=mem_survey_$(hostname).txt
{
echo "=== 메모리 계층 조사 · $(hostname) ==="
echo "--- 캐시 구성 (lscpu) ---"
lscpu 2>/dev/null | grep -i cache || true
echo "--- 캐시 구성 (sysfs) ---"
for d in /sys/devices/system/cpu/cpu0/cache/index*; do
  [ -d "$d" ] || continue
  echo "$(cat $d/level 2>/dev/null)단계 $(cat $d/type 2>/dev/null) $(cat $d/size 2>/dev/null) (line $(cat $d/coherency_line_size 2>/dev/null)B)"
done
echo "--- 주 메모리 ---"
free -h
echo "--- 스왑 ---"
swapon --show 2>/dev/null || echo "(스왑 없음)"
} | tee "$O"
echo "[OK] 저장: $O — hierarchy_table.md의 표를 채우는 근거로 쓴다"
