#!/usr/bin/env bash
# LAB-05 아키텍처 기능 판독 — /proc/cpuinfo의 Features 줄을 해석한다
# RPi4(또는 아무 ARM 리눅스)에서 실행. PC에서는 비교용으로 flags를 본다.
set -u
O=features_$(hostname).txt
{
echo "=== CPU 기능 판독 · $(hostname) ==="
if grep -qi '^Features' /proc/cpuinfo 2>/dev/null; then
  echo "--- ARM Features (첫 코어) ---"
  grep -m1 -i '^Features' /proc/cpuinfo
  echo
  echo "--- 판독 사전 (있으면 O 표시) ---"
  F=$(grep -m1 -i '^Features' /proc/cpuinfo)
  for k in fp asimd aes sha1 sha2 crc32 atomics fphp asimdhp cpuid asimddp sve sve2 sme; do
    case " $F " in *" $k "*) m=O;; *) m=-;; esac
    printf "  %-10s %s\n" "$k" "$m"
  done
  echo
  echo "해석 힌트: asimd=NEON(v8 명칭), sve/sve2=가변폭 벡터(v8.2+/v9),"
  echo "          sme=행렬 확장(v9.2+, Lumex C1 세대는 SME2 기본 탑재)"
else
  echo "--- x86 flags 상위 비교용 ---"
  grep -m1 '^flags' /proc/cpuinfo | tr ' ' '\n' | grep -E 'sse|avx' | sort -u | head -12
fi
echo "--- 아키텍처 식별 ---"
uname -m
grep -m1 -iE 'model name|CPU part' /proc/cpuinfo || true
} | tee "$O"
echo "[OK] 저장: $O — lineage_card.md 작성 근거로 쓴다"
