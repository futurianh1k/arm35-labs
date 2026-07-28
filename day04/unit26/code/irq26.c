/* LAB-26 irq26.c — [TODO] 핸들러 본문만 완성한다 (계약 3조) */
#define BIT(n) (1u<<(n))
#define UART0 0x101f1000
#define DR   (*(volatile unsigned*)(UART0+0x00))
#define FR   (*(volatile unsigned*)(UART0+0x18))
#define IBRD (*(volatile unsigned*)(UART0+0x24))
#define FBRD (*(volatile unsigned*)(UART0+0x28))
#define LCRH (*(volatile unsigned*)(UART0+0x2C))
#define CR   (*(volatile unsigned*)(UART0+0x30))

#define T0 0x101e2000
#define T0_LOAD   (*(volatile unsigned*)(T0+0x00))
#define T0_CTRL   (*(volatile unsigned*)(T0+0x08))
#define T0_INTCLR (*(volatile unsigned*)(T0+0x0C))     /* W1C */

#define VIC 0x10140000
#define VIC_IRQSTATUS (*(volatile unsigned*)(VIC+0x00))
#define VIC_INTENABLE (*(volatile unsigned*)(VIC+0x10))

extern void enable_irq(void);

static void uart_init(void){
    CR=0; IBRD=13; FBRD=1; LCRH=(3u<<5)|BIT(4); CR=BIT(0)|BIT(8)|BIT(9);
}
static void putc_(char c){ while (FR & BIT(5)); DR=(unsigned)c; }
static void puts_(const char*s){ while(*s) putc_(*s++); }

static void timer_init(void){
    T0_CTRL   = 0;
    T0_LOAD   = 200000;                       /* 0.2s @1MHz */
    T0_INTCLR = 1;                            /* 선청소     */
    T0_CTRL   = BIT(7)|BIT(6)|BIT(5)|BIT(1);  /* EN|Per|IE|32 — 문1 개방 */
}

volatile unsigned ticks = 0;                  /* 제3조: volatile 통신 */

void irq_handler(void){
    /* TODO — 계약 3조 순서대로:
       1) 판별: VIC_IRQSTATUS 의 BIT(4)가 켜졌는가 (Timer0인가)
       2) 원인 제거: T0_INTCLR = 1;  (W1C 한 발 — 제2조)
       3) 접수: ticks++;             (짧게 — 제1조)                */
}

int main(void){
    uart_init(); timer_init();
    puts_("IRQ26 START\r\n");
    VIC_INTENABLE = BIT(4);                   /* 문2: 소스 개방  */
    enable_irq();                             /* 문3: I비트 해제 */
    unsigned seen = 0;
    while (seen < 5){
        if (ticks != seen){                   /* 무거운 일(출력)은 병동에서 */
            seen = ticks;
            putc_('0'+(char)seen); puts_(" irq\r\n");
        }
    }
    puts_("IRQ x5 OK\r\n");                   /* check 표적 */
    for(;;);
}
