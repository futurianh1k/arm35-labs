@ H25 start.s — 스택·main·대기 루프
    .section .vectors, "ax"
    .global _start
_start:
    b   reset
reset:
    ldr sp, =0x000f0000
    bl  main
hang:
    b   hang
