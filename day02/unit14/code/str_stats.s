@ LAB-14 str_stats.s — 종합 미션 골격 (TODO 세 개가 전부다)
    .text
    .global str_stats
    .type   str_stats, %function
@ void str_stats(const char* s, int* len, int* upper)
@ r0=s, r1=&len, r2=&upper
str_stats:
    push  {r4, r5, lr}      @ 계약: r4·r5 사용 예정
    mov   r4, #0            @ r4 = len
    mov   r5, #0            @ r5 = upper
loop:
    ldrb  r3, [r0], #1      @ 한 글자 읽고 전진
    cmp   r3, #0
    beq   done
    @ TODO-1: 길이 증가 (r4)
    @ TODO-2: 대문자 판정 — 'A'<= r3 <= 'Z' 이면 r5+1
    @         힌트: sub r6? 아니면 cmp 2회 + 조건부 가산
    b     loop
done:
    @ TODO-3: 결과 저장 — str r4,[r1] / str r5,[r2]
    pop   {r4, r5, pc}
