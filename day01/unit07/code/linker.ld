/* LAB-07 linker.ld — 개념: "벡터는 주소 0". QEMU -kernel은 0x10000에 적재하므로
 * 링크 기준을 0x10000으로 잡고, startup.s의 Reset이 벡터 블록을 0x0으로 복사한다.
 * 상세 링커 문법은 21차시(Cross Dev·Boot)에서 다룬다 — 오늘은 3가지만:
 *   ① 시작 주소  ② .vectors가 맨 앞  ③ 그다음 .text
 */
ENTRY(_vectors)
SECTIONS
{
    . = 0x10000;
    .vectors : { *(.vectors) }
    .text    : { *(.text*) }
    .rodata  : { *(.rodata*) }
    .data    : { *(.data*) }
    .bss     : { *(.bss*) *(COMMON) }
}
