/* LAB-07 main.c — QEMU versatilepb의 PL011 UART0으로 말하기
 * UART0 데이터 레지스터 주소 0x101f1000 (근거: QEMU versatilepb 보드 문서)
 */
#define UART0_DR (*(volatile unsigned int*)0x101f1000)

void uart_putc(char c){ UART0_DR = c; }
void uart_puts(const char *s){ while(*s) uart_putc(*s++); }

/* SWI 핸들러가 출력할 메시지 — LAB에서 본인 이니셜로 수정한다 */
const char msg_swi[] = "SWI! handler speaking\n";

int main(void){
    uart_puts("BOOT: bare-metal alive\n");
    __asm__ volatile("svc #0");            /* SWI 발생 → 핸들러 */
    uart_puts("BACK: returned from SWI\n");
    for(;;);
    return 0;
}
