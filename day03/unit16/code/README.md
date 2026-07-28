# LAB-16 · 지도 제작과 점화 (ARM926 MMU)
- `make run`  : UART로 MIDR → 매직 기록 → MMU ON → ALIAS OK 확인 (종료 Ctrl+A, X)
- `make check`: 문자열 자동 판정 → echo $? = 0
실험: mmu926.c의 앨리어스 목적지(0u<<20)를 다른 1MB로 바꾸거나 L1[0x400]=0(폴트)로 바꿔 재실행한다.
폴트 실험은 침묵/폭주가 정상 관측이다 — Ctrl+A X로 회수하고 원상복구 후 커밋한다.
