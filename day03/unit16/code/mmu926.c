/* LAB-16 mmu926.c — ARM926(versatilepb)에서 L1 테이블 제작·MMU 점화·앨리어스 실증
 * UART: PL011 @0x101f1000  /  L1 테이블: 0x00004000(16KB 정렬)
 * 앨리어스: VA 0x40000000 -> PA 0x00000000  (매직은 PA 0x8000에 기록) */
#define UARTDR (*(volatile unsigned *)0x101f1000)
#define UARTFR (*(volatile unsigned *)0x101f1018)

static void putc_(char c){ while(UARTFR & (1u<<5)); UARTDR = c; }
static void puts_(const char *s){ while(*s) putc_(*s++); }
static void puthex(unsigned v){
    puts_("0x");
    for(int i=28;i>=0;i-=4){ unsigned d=(v>>i)&0xF; putc_(d<10?'0'+d:'A'+d-10); }
}

volatile unsigned *L1 = (unsigned *)0x00004000;   /* 16KB 정렬 */

static void mmu_on(void){
    for (unsigned i = 0; i < 4096; i++)
        L1[i] = (i << 20) | 0xC02;                /* 항등: 섹션, AP=11, dom0 */
    L1[0x400] = (0u << 20) | 0xC02;               /* 앨리어스: 0x40000000 -> PA 0 */

    asm volatile(
        "mcr p15,0,%0,c2,c0,0\n"                  /* TTBR  <- 테이블         */
        "mcr p15,0,%1,c3,c0,0\n"                  /* DACR  <- dom0=client(01)*/
        "mcr p15,0,%2,c8,c7,0\n"                  /* TLB 전체 무효화         */
        "mrc p15,0,r0,c1,c0,0\n"
        "orr r0,r0,#1\n"                          /* SCTLR.M = 1             */
        "mcr p15,0,r0,c1,c0,0\n"
        :: "r"(L1), "r"(1), "r"(0) : "r0","memory");
}

int main(void){
    unsigned midr;
    asm volatile("mrc p15,0,%0,c0,c0,0" : "=r"(midr));
    puts_("MIDR="); puthex(midr); puts_("\r\n");

    *(volatile unsigned *)0x8000 = 0xCAFE2450;    /* MMU OFF: PA에 매직 기록 */
    puts_("MMU OFF: wrote magic @PA 0x00008000\r\n");

    mmu_on();
    puts_("MMU ON\r\n");

    unsigned v = *(volatile unsigned *)0x40008000; /* 앨리어스 VA로 읽기 */
    puts_("read @VA 0x40008000 = "); puthex(v); puts_("\r\n");
    puts_(v == 0xCAFE2450 ? "ALIAS OK\r\n" : "ALIAS FAIL\r\n");
    return 0;                                      /* start.s가 wfi로 대기 */
}
