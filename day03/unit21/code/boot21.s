@ LAB-21 boot21.s — 최소 새벽: 벡터, 인사(B,T), 대기
    .section .vectors, "ax"
    .global _start
_start:
    b   reset               @ 리셋 벡터 = 이 이미지의 첫 명령
reset:
    ldr r0, =0x101f1000     @ PL011 DR (versatilepb)
    mov r1, #66             @ 'B'
    str r1, [r0]
    mov r1, #84             @ 'T'
    str r1, [r0]
hang:
    b   hang                @ v5: wfi 없음 - 대기 루프
