ENTRY(_start)
SECTIONS {
  . = 0x10000;              /* versatilepb -kernel 적재 주소 */
  .vectors : { *(.vectors) }
  .text    : { *(.text*) }
}
