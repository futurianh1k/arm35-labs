@ H26 start.s — [제공] 벡터 트램펄린 복사 + 모드 스택 + IRQ 껍데기
    .section .vectors, "ax"
    .global _start
_start:
    b   reset

@ ---- 0번지로 복사될 트램펄린 원본 (명령 8 + 주소 테이블 8 = 16워드) ----
stub_src:
    ldr pc, [pc, #0x18]      @ 0x00 reset
    ldr pc, [pc, #0x18]      @ 0x04 undef
    ldr pc, [pc, #0x18]      @ 0x08 svc
    ldr pc, [pc, #0x18]      @ 0x0C prefetch abort
    ldr pc, [pc, #0x18]      @ 0x10 data abort
    ldr pc, [pc, #0x18]      @ 0x14 (reserved)
    ldr pc, [pc, #0x18]      @ 0x18 IRQ  <- 오늘의 문
    ldr pc, [pc, #0x18]      @ 0x1C FIQ
    .word hang, hang, hang, hang, hang, hang, irq_wrap, hang

reset:
    msr cpsr_c, #0xD2        @ IRQ 모드(I·F 마스크) — 전용 스택 설치
    ldr sp, =0x000e0000
    msr cpsr_c, #0xD3        @ SVC 모드 복귀 — 메인 스택
    ldr sp, =0x000f0000

    ldr r0, =stub_src        @ 트램펄린 16워드 -> PA 0
    mov r1, #0
    mov r2, #16
1:  ldr r3, [r0], #4
    str r3, [r1], #4
    subs r2, r2, #1
    bne 1b

    bl  main
hang:
    b   hang

    .global enable_irq       @ CPSR I비트 해제 (세 번째 문)
enable_irq:
    mrs r0, cpsr
    bic r0, r0, #0x80
    msr cpsr_c, r0
    bx  lr

irq_wrap:                    @ IRQ 껍데기 — 계약의 무대
    sub   lr, lr, #4         @ 복귀점 보정 (PC 선행의 귀결)
    stmfd sp!, {r0-r3, r12, lr}
    bl    irq_handler        @ C 본문 (오늘의 TODO)
    ldmfd sp!, {r0-r3, r12, pc}^   @ ^: SPSR->CPSR 복원까지 한 방
