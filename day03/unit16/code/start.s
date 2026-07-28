@ H16 start.s — 최소 스타트업: 벡터, 스택, main
    .section .vectors, "ax"
    .global _start
_start:
    b   reset
reset:
    ldr sp, =0x000f0000     @ 스택: RAM 하부 안전 지대
    bl  main
hang:
    b   hang            @ v5: wfi 없음 - 대기 루프
