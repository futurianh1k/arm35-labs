/* M1 — 이중 소스 IRQ 모범답안 (강사용)
 * 제공: 타이머 경로 전체(H26 완성 그대로) — 회귀 표적 "IRQ x5 OK"
 * TODO 3곳: UART 수신 손님을 같은 문으로 받아라 — 신규 표적 "K2" */
#define BIT(n) (1u<<(n))
#define UART0 0x101f1000
#define DR   (*(volatile unsigned*)(UART0+0x00))
#define FR   (*(volatile unsigned*)(UART0+0x18))
#define IBRD (*(volatile unsigned*)(UART0+0x24))
#define FBRD (*(volatile unsigned*)(UART0+0x28))
#define LCRH (*(volatile unsigned*)(UART0+0x2C))
#define CR   (*(volatile unsigned*)(UART0+0x30))
#define IMSC (*(volatile unsigned*)(UART0+0x38))   /* 24차시에 잠들어 있던 창구 */

#define T0 0x101e2000
#define T0_LOAD   (*(volatile unsigned*)(T0+0x00))
#define T0_CTRL   (*(volatile unsigned*)(T0+0x08))
#define T0_INTCLR (*(volatile unsigned*)(T0+0x0C))

#define VIC 0x10140000
#define VIC_IRQSTATUS (*(volatile unsigned*)(VIC+0x00))
#define VIC_INTENABLE (*(volatile unsigned*)(VIC+0x10))

extern void enable_irq(void);

static void uart_init(void){
    CR=0; IBRD=13; FBRD=1; LCRH=(3u<<5)|BIT(4); CR=BIT(0)|BIT(8)|BIT(9);
    IMSC = BIT(4);                    /* RXIM 개방 */
}
static void putc_(char c){ while (FR & BIT(5)); DR=(unsigned)c; }
static void puts_(const char*s){ while(*s) putc_(*s++); }

static void timer_init(void){
    T0_CTRL=0; T0_LOAD=200000; T0_INTCLR=1;
    T0_CTRL=BIT(7)|BIT(6)|BIT(5)|BIT(1);
}

volatile unsigned ticks = 0;
volatile unsigned rx    = 0;

void irq_handler(void){
    unsigned st = VIC_IRQSTATUS;              /* 손님 명부를 한 번 읽는다 */
    if (st & BIT(4)) {                        /* 손님 1: 타이머 (제공) */
        T0_INTCLR = 1;
        ticks++;
    }
    if (st & BIT(12)) {                   /* 손님 2: UART 수신 */
        (void)DR;                         /* 읽기 = 소비 = 원인 제거 */
        rx++;
    }
}

int main(void){
    uart_init(); timer_init();
    puts_("IRQ34 START\r\n");
    VIC_INTENABLE = BIT(4);
    VIC_INTENABLE = BIT(12);          /* 두 번째 문 개방 */
    enable_irq();
    unsigned seen=0, kseen=0;
    while (seen < 5){
        if (ticks != seen){ seen=ticks; putc_('0'+(char)seen); puts_(" irq\r\n"); }
        if (rx != kseen){ kseen=rx; putc_('K'); putc_('0'+(char)kseen); puts_("\r\n"); }
    }
    puts_("IRQ x5 OK\r\n");
    for(;;);
}
