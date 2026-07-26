@ LAB-08 pipeline_demo.s — 5단 파이프라인의 증거 수집 (종속/독립/PC+8)
    .text
    .global _start
_start:
    mov   r0, #5
@ --- (A) 종속 시퀀스: 앞 결과를 즉시 사용 ---
    add   r1, r0, r0      @ r1 = 10
    add   r2, r1, r1      @ r2 = 20  (r1에 의존)
    add   r3, r2, r2      @ r3 = 40  (r2에 의존)
@ --- (B) 독립 시퀀스: 서로 무관 ---
    mov   r4, #1
    mov   r5, #2
    mov   r6, #3
@ --- (C) PC 관찰: 6차시 재검증 ---
    mov   r7, pc          @ 이 명령 주소 + 8 이 기록된다
here:
    nop
@ --- 종료 (Linux EABI: exit(r3&0xff)) ---
    mov   r0, r3
    mov   r7, #1          @ sys_exit
    svc   #0
