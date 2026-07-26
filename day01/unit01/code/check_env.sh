#!/usr/bin/env bash
# LAB-01 환경 점검 스크립트 — ARM Processor 35H
# 사용법: bash check_env.sh   (결과는 화면과 env_report.txt에 동시 기록)
set -u
R=env_report.txt
: > "$R"
say(){ echo "$1" | tee -a "$R"; }
chk(){ # chk "이름" "명령"
  if command -v "$2" >/dev/null 2>&1; then
    say "[OK ] $1 : $("$2" --version 2>/dev/null | head -1)"
  else
    say "[MISS] $1 : 설치 필요 -> $3"
  fi
}
say "=== ARM 35H 환경 점검 $(date '+%F %T') ==="
say "[INFO] Host  : $(uname -srmo)"
say "[INFO] Distro: $(. /etc/os-release 2>/dev/null; echo ${PRETTY_NAME:-unknown})"
say "[INFO] User  : ${USER:-$(whoami)}  Shell: ${SHELL:-unknown}"
say "---- 필수 도구 ----"
chk gcc            gcc            "sudo apt install build-essential"
chk make           make           "sudo apt install build-essential"
chk git            git            "sudo apt install git"
chk python3        python3        "sudo apt install python3"
chk minicom        minicom        "sudo apt install minicom"
say "---- 크로스 툴체인 (Modern: AArch64) ----"
chk aarch64-linux-gnu-gcc aarch64-linux-gnu-gcc "sudo apt install gcc-aarch64-linux-gnu"
chk qemu-aarch64   qemu-aarch64   "sudo apt install qemu-user"
say "---- 크로스 툴체인 (Legacy: ARM32) ----"
chk arm-linux-gnueabihf-gcc arm-linux-gnueabihf-gcc "sudo apt install gcc-arm-linux-gnueabihf"
chk arm-none-eabi-gcc arm-none-eabi-gcc "sudo apt install gcc-arm-none-eabi"
chk qemu-system-arm qemu-system-arm "sudo apt install qemu-system-arm"
chk gdb-multiarch  gdb-multiarch  "sudo apt install gdb-multiarch"
say "---- 계정·권한 ----"
if git config user.name >/dev/null 2>&1; then
  say "[OK ] git 사용자: $(git config user.name) <$(git config user.email)>"
else
  say "[MISS] git 사용자 미설정 -> git config --global user.name / user.email"
fi
if groups | grep -qw dialout; then say "[OK ] dialout 그룹(시리얼 권한)";
else say "[MISS] dialout 그룹 -> sudo usermod -aG dialout $(whoami) (재로그인 필요)"; fi
say "=== 점검 끝. MISS 항목을 모두 해결한 뒤 다시 실행한다. ==="
