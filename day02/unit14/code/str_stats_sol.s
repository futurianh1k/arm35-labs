@ LAB-14 str_stats_sol.s — 강사용 모범답안 (배포 금지)
    .text
    .global str_stats
    .type   str_stats, %function
str_stats:
    push  {r4, r5, lr}
    mov   r4, #0
    mov   r5, #0
loop:
    ldrb  r3, [r0], #1
    cmp   r3, #0
    beq   done
    add   r4, r4, #1        @ TODO-1: 길이 증가
    cmp   r3, #'A'          @ TODO-2: 범위 판정 (분기+조건부 가산판)
    blt   next
    cmp   r3, #'Z'
    addls r5, r5, #1        @ r3<='Z' 이면 대문자
next:
    b     loop
done:
    str   r4, [r1]          @ TODO-3: 결과 저장
    str   r5, [r2]
    pop   {r4, r5, pc}

@ (심화·무분기판 참고) ip(r12)는 caller-saved라 대피 없이 쓸 수 있다
@   sub  ip, r3, #'A'
@   cmp  ip, #25
@   addls r5, r5, #1
