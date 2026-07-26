@ LAB-13 asm_max.s — AAPCS32 계약 이행 (leaf 함수)
    .text
    .global asm_max
    .type   asm_max, %function
asm_max:                 @ int asm_max(int a, int b)
    cmp   r0, r1         @ a ? b   (11차시 플래그)
    movlt r0, r1         @ a<b면 r0=b — 반환은 r0 조항
    bx    lr             @ 표준 복귀

@ ---- (참고) 중첩 버전이라면 ----
@ asm_max2: push {r4, lr}   @ 계약: r4·LR 대피
@           ...  bl helper ...
@           pop  {r4, pc}   @ 복원+복귀 한 번에

@ ---- (심화 골격) 어셈이 C를 부른다: LR 대피가 필수가 되는 순간 ----
@     .global asm_twice_plus1        @ int asm_twice_plus1(int a)
@ asm_twice_plus1:
@     push {lr}            @ TODO: 왜 필수인가 — bl이 LR을 덮는다
@     bl   c_add1          @ C 함수 호출 (main.c에 정의)
@     add  r0, r0, r0
@     pop  {pc}
