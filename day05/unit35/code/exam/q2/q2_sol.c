/* Q2 문자의 길(H24 축) — 4막 초기화는 제공. 폴링 송신 putc/puts 를 완성하라. */
#define BIT(n) (1u<<(n))
#define UART0 0x101f1000
#define DR   (*(volatile unsigned*)(UART0+0x00))
#define FR   (*(volatile unsigned*)(UART0+0x18))
#define IBRD (*(volatile unsigned*)(UART0+0x24))
#define FBRD (*(volatile unsigned*)(UART0+0x28))
#define LCRH (*(volatile unsigned*)(UART0+0x2C))
#define CR   (*(volatile unsigned*)(UART0+0x30))
#define TXFF BIT(5)

static void uart_init(void){            /* 제공: 4막 시퀀스 */
    CR=0; IBRD=13; FBRD=1; LCRH=(3u<<5)|BIT(4); CR=BIT(0)|BIT(8)|BIT(9);
}
static void putc_(char c){
    while (FR & TXFF);
    DR = (unsigned)c;
}
static void puts_(const char *s){
    while (*s) putc_(*s++);
}
int main(void){
    uart_init();
    puts_("EXAM Q2 PL011 OK\r\n");      /* check의 grep 표적 */
    for(;;);
}
