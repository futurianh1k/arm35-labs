/* LAB-24 uart24.c — PL011 정식 초기화 + 폴링 송수신 에코 */
#define BIT(n) (1u<<(n))
#define UART0 0x101f1000
#define DR   (*(volatile unsigned*)(UART0+0x00))
#define FR   (*(volatile unsigned*)(UART0+0x18))
#define IBRD (*(volatile unsigned*)(UART0+0x24))
#define FBRD (*(volatile unsigned*)(UART0+0x28))
#define LCRH (*(volatile unsigned*)(UART0+0x2C))
#define CR   (*(volatile unsigned*)(UART0+0x30))
#define TXFF BIT(5)
#define RXFE BIT(4)

static void uart_init(void){
    CR   = 0;                        /* 1막: 정지                 */
    IBRD = 13; FBRD = 1;             /* 2막: 24MHz -> 115200      */
    LCRH = (3u<<5) | BIT(4);         /* 3막: 8N1 + FIFO (분주 굳힘)*/
    CR   = BIT(0)|BIT(8)|BIT(9);     /* 4막: UARTEN|TXE|RXE       */
}
static void putc_(char c){ while (FR & TXFF); DR = (unsigned)c; }
static void puts_(const char *s){ while (*s) putc_(*s++); }
static char getc_(void){ while (FR & RXFE); return (char)DR; }

int main(void){
    uart_init();
    puts_("UART24 READY\r\n");
    for (;;){
        char c = getc_();
        putc_('['); putc_(c); putc_(']');   /* 에코 형식 = check 표적 */
    }
}
