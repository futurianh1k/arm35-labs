/* LAB-25 timer25.c — SP804 알람 5회 폴링 (2박자: RIS 확인 -> IntClr) */
#define BIT(n) (1u<<(n))
#define UART0 0x101f1000
#define DR   (*(volatile unsigned*)(UART0+0x00))
#define FR   (*(volatile unsigned*)(UART0+0x18))
#define IBRD (*(volatile unsigned*)(UART0+0x24))
#define FBRD (*(volatile unsigned*)(UART0+0x28))
#define LCRH (*(volatile unsigned*)(UART0+0x2C))
#define CR   (*(volatile unsigned*)(UART0+0x30))

#define T0 0x101e2000                       /* SP804 Timer0 */
#define LOAD   (*(volatile unsigned*)(T0+0x00))
#define VALUE  (*(volatile unsigned*)(T0+0x04))
#define CTRL   (*(volatile unsigned*)(T0+0x08))
#define INTCLR (*(volatile unsigned*)(T0+0x0C))   /* W1C */
#define RIS    (*(volatile unsigned*)(T0+0x10))

static void uart_init(void){
    CR=0; IBRD=13; FBRD=1; LCRH=(3u<<5)|BIT(4); CR=BIT(0)|BIT(8)|BIT(9);
}
static void putc_(char c){ while (FR & BIT(5)); DR=(unsigned)c; }
static void puts_(const char*s){ while(*s) putc_(*s++); }

static void timer_init(void){
    CTRL   = 0;                              /* 정지 후 설정 (24차시 규율) */
    LOAD   = 200000;                         /* 0.2s @ 1MHz               */
    INTCLR = 1;                              /* 선청소 — 잔류 깃발 예방    */
    CTRL   = BIT(7)|BIT(6)|BIT(1);           /* EN | Periodic | 32bit     */
}

int main(void){
    uart_init(); timer_init();
    puts_("TIMER25 START\r\n");
    for (int tick=1; tick<=5; tick++){
        while (!(RIS & 1));                  /* 박자 1: 만료 깃발 폴링     */
        INTCLR = 1;                          /* 박자 2: 원인 제거(W1C)     */
        putc_('0'+tick); puts_(" tick\r\n");
    }
    puts_("DONE(5 ticks)\r\n");
    for(;;);
}
