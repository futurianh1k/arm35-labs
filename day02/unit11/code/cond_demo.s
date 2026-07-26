@ LAB-11 cond_demo.s — NZCV 관찰점 A~D (가설표 먼저, 관측은 그다음)
    .text
    .global _start
_start:
    mov   r0, #7
    mov   r1, #9
@ --- (1) 비교와 부호 있는 조건 ---
    cmp   r0, r1          @ 7-9 → N=1, Z=0 (관찰점 A)
    movge r2, r0          @ 실행 안 됨
    movlt r2, r1          @ r2=9
@ --- (2) 같음: Z와 C를 함께 본다 ---
    cmp   r0, r0          @ 7-7 → Z=1, C=1 (관찰점 B)
@ --- (3) 부호의 두 얼굴 ---
    mvn   r3, #0          @ r3 = 0xFFFFFFFF
    cmp   r3, #1          @ (관찰점 C)
    movhi r4, #1          @ 부호 없음: 크다 → r4=1
    movlt r5, #1          @ 부호 있음: -1<1 → r5=1
@ --- (4) S 접미사 ---
    subs  r6, r0, r0      @ 0 → Z=1 (관찰점 D)
@ --- 종료: exit(r2) = 9 ---
    mov   r0, r2
    mov   r7, #1
    svc   #0
