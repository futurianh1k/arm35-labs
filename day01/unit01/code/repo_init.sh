#!/usr/bin/env bash
# LAB-01 개인 저장소 초기화 — Evidence Pack의 시작점
# 사용법: bash repo_init.sh 학번_이름   (예: bash repo_init.sh 2026123_홍길동)
set -eu
[ $# -ge 1 ] || { echo "사용법: bash repo_init.sh 학번_이름"; exit 1; }
D="arm35-$1"
mkdir -p "$D"/{day1,day2,day3,day4,day5,evidence}
cd "$D"
git init -b main >/dev/null
cp ../env_report.txt evidence/ 2>/dev/null || true
cat > README.md <<MD
# ARM Processor 35H — $1
- 훈련 기간: 5일 35시간
- 장비: MDS2450(ARM926EJ-S, ARMv5TE) + Raspberry Pi 4(Cortex-A72, ARMv8-A)
- 규칙: 모든 실습은 [가설-명령-관측-판정-복구/커밋] 5단계로 기록한다.

## Evidence Pack 목록
| Day | 산출물 | 위치 |
|-----|--------|------|
| 1 | env_report.txt, hello 크로스 빌드 로그 | day1/ |
MD
git add -A && git commit -m "chore: init evidence repo (LAB-01)" >/dev/null
echo "[OK] 저장소 생성: $D  (커밋 1건)"
echo "다음: GitHub에 비공개 저장소를 만들고 git remote add origin <URL> && git push -u origin main"
