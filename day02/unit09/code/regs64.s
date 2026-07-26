// LAB-09 regs64.s — 첫 AArch64: 3주소·w뷰·SP/PC 분리 관찰
    .text
    .global _start
_start:
    mov   x0, #7
    mov   x1, #5
    add   x2, x0, x1      // x2 = 12  (3주소 형식)
    add   w3, w0, w1      // w = x의 하위 32비트 뷰
    mov   x4, sp          // SP는 범용과 분리된 별도 자원
    adr   x5, _start      // PC 상대 주소 계산(PC 직접 읽기 없음)
    mov   x6, xzr         // 제로 레지스터: 항상 0
// --- 종료: exit(x2) ---
    mov   x0, x2
    mov   x8, #93         // AArch64 리눅스 sys_exit
    svc   #0
