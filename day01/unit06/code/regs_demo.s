/* LAB-06 regs_demo.s — ARMv5TE 레지스터·CPSR·PC+8을 GDB로 직접 관찰
 * 표적: ARM 32-bit (Legacy 트랙과 동일 문법, QEMU 사용자 모드로 안전하게 실험)
 * 빌드/실행: make debug  (창1: QEMU가 1234 포트에서 대기)
 *            make gdb    (창2: gdb-multiarch 접속)
 * 관찰 3장면: (1) MOV/ADD 후 r0~r3 변화 (2) CMP 후 CPSR NZCV 변화 (3) PC 읽기값 = 현재+8
 */
    .global _start
    .text
_start:
    /* 장면 1 — 데이터 이동과 산술 */
    mov   r0, #10          /* r0 = 10                     */
    mov   r1, #3           /* r1 = 3                      */
    add   r2, r0, r1       /* r2 = 13                     */
    sub   r3, r0, r1       /* r3 = 7                      */

    /* 장면 2 — CPSR 플래그: CMP는 결과를 버리고 플래그만 갱신 */
    cmp   r1, r0           /* 3-10 → 음수 → N=1, C=0(빌림) */
    cmp   r0, r0           /* 10-10 → 0  → Z=1, C=1        */

    /* 장면 3 — PC 파이프라인 효과: r4 = 이 명령 주소 + 8 */
    mov   r4, pc           /* v5TE에서 pc 읽기값은 현재+8   */
    nop
    nop

    /* 종료: Linux EABI exit(0) — swi는 v5TE 시절 표기, svc와 동일 인코딩 */
    mov   r0, #0
    mov   r7, #1           /* __NR_exit                    */
    swi   #0
