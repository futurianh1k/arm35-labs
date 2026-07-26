@ LAB-12 copy8.s — 포스트인덱스 복사 + 자기검증(합 36) + 리터럴 풀 채증
    .data
src:  .word 1,2,3,4,5,6,7,8
dst:  .space 32
    .text
    .global _start
_start:
    ldr   r0, =src        @ 리터럴 풀 사용(디스어셈블서 확인)
    ldr   r1, =dst
    mov   r2, #8          @ 원소 수
loop:
    ldr   r3, [r0], #4    @ 읽고 전진 (포스트인덱스)
    str   r3, [r1], #4    @ 쓰고 전진
    subs  r2, r2, #1      @ 카운트-1, 플래그 갱신(11차시)
    bne   loop
@ --- 검증: dst 합 = 36 을 종료코드로 ---
    ldr   r1, =dst
    mov   r2, #8
    mov   r0, #0
sum:
    ldr   r3, [r1], #4
    add   r0, r0, r3
    subs  r2, r2, #1
    bne   sum
    mov   r7, #1          @ exit(r0)=36
    svc   #0
