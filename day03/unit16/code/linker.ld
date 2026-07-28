/* H16 linker.ld — versatilepb: -kernel 적재 주소 0x10000 */
ENTRY(_start)
SECTIONS {
  . = 0x10000;
  .vectors : { *(.vectors) }
  .text    : { *(.text*) }
  .rodata  : { *(.rodata*) }
  .data    : { *(.data*) }
  .bss     : { *(.bss*) *(COMMON) }
}
