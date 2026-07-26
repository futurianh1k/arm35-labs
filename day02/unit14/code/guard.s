@ LAB-14 guard.s — 채점 인프라: 보존 레지스터(r4/r5/r8) 감시 호출
    .text
    .global guard_call
    .type   guard_call, %function
@ int guard_call(const char* s, int* len, int* upper)
@ 반환: 0=계약 준수, bit0=r4 파괴, bit1=r5 파괴, bit2=r8 파괴
guard_call:
    push  {r4-r8, lr}
    ldr   r4, =0x44444444
    ldr   r5, =0x55555555
    ldr   r8, =0x88888888
    bl    str_stats
    mov   r3, #0
    ldr   ip, =0x44444444
    cmp   r4, ip
    orrne r3, r3, #1
    ldr   ip, =0x55555555
    cmp   r5, ip
    orrne r3, r3, #2
    ldr   ip, =0x88888888
    cmp   r8, ip
    orrne r3, r3, #4
    mov   r0, r3
    pop   {r4-r8, pc}
