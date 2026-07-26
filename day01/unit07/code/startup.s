/* LAB-07 startup.s — 벡터 테이블 · Reset · SWI 핸들러 (ARMv5TE / ARM926EJ-S)
 * 슬라이드 "실습 코드 ①"의 전체판. QEMU versatilepb는 -kernel 이미지를
 * 0x10000에 로드하므로, 링크는 0x10000으로 하고 Reset에서 벡터 블록(명령 8개
 * + 리터럴 풀)을 주소 0x0으로 복사해 "벡터는 반드시 0번지" 규칙을 실현한다.
 * (ARM926에는 VBAR가 없다 — 벡터 위치가 하드웨어 고정이라는 점이 핵심 학습)
 */
    .section .vectors, "ax"
    .global _vectors
_vectors:
    ldr pc, =reset_handler     @ 0x00 Reset
    ldr pc, =hang              @ 0x04 Undefined Instruction
    ldr pc, =swi_handler       @ 0x08 SWI (SVC)
    ldr pc, =hang              @ 0x0C Prefetch Abort
    ldr pc, =hang              @ 0x10 Data Abort
    nop                        @ 0x14 (Reserved)
    ldr pc, =hang              @ 0x18 IRQ
    ldr pc, =hang              @ 0x1C FIQ
    .ltorg                     @ 리터럴 풀을 바로 뒤에 고정(복사 대상에 포함)

    .text
    .global reset_handler
reset_handler:
    ldr sp, =0x00090000        @ SVC 스택 (4대 임무 ②)
    /* 벡터+리터럴 16워드(64B)를 0x0으로 복사 — 슬라이드 발췌에서 생략된 부분 */
    ldr r0, =_vectors
    mov r1, #0
    mov r2, #16
1:  ldr r3, [r0], #4
    str r3, [r1], #4
    subs r2, r2, #1
    bne 1b
    bl  main                   @ C 세계로 (임무 ④; .data/.bss는 오늘 생략=③)
hang:
    b   hang                   @ 미구현 예외의 안전 그물

    .global swi_handler
swi_handler:
    stmfd sp!, {r0-r3, lr}     @ 문맥 보존
    ldr r0, =msg_swi
    bl  uart_puts              @ "SWI!" 출력
    ldmfd sp!, {r0-r3, lr}
    movs pc, lr                @ 복귀: SPSR→CPSR 동시 복원
