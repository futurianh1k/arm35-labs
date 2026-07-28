# LAB-21 · 새벽 관측 — 명세서와 실측의 일치
- `make inspect`: readelf Entry + objdump 첫 명령들 → boot_report.txt
- `make run`    : UART에 B, T 출력 확인 (종료 Ctrl+A, X)
- `make trace`  : QEMU -d in_asm 으로 실제 첫 실행 명령 로그 → trace.log
- `make check`  : Entry(0x10000)와 첫 실행 주소의 일치 자동 판정 → echo $? = 0
심화: _start 앞(벡터 최상단)에 nop 하나를 넣고 inspect/trace/check를 재실행 —
      명세와 실측이 함께 이동함을 표로 기록하고 원상복구한다.
주의: trace.log는 커질 수 있어 timeout 3초 + head 열람이 표준 절차다.
      대기 루프 설계라 QEMU가 스스로 끝나지 않는 것이 정상이다.
