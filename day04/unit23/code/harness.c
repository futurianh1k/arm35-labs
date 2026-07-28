/* LAB-23 하니스 — 두 도시 + 입력 처리. 실패 수 = exit */
#include <stdio.h>
#include "gpio_regs.h"

static int fails=0;
static void chk(const char*n, long got, long want){
    int ok=(got==want);
    printf("  %-36s got=0x%lX want=0x%lX %s\n",n,got,want,ok?"PASS":"FAIL");
    if(!ok) fails++;
}
static void lev_commit(void){            /* SET/CLR 래치 → LEV 반영(하드웨어 흉내) */
    GPLEV0 = (GPLEV0 | GPSET0) & ~GPCLR0; GPSET0 = 0; GPCLR0 = 0;
}
int main(void){
    puts("[도시 B: BCM2711]");
    GPFSEL(1)=0xAAAAAAAAu;
    bcm_dir(14,1);
    chk("dir(14): FSEL1[14:12]=001",(GPFSEL(1)>>12)&7,1);
    chk("dir(14): 이웃 보존",GPFSEL(1)&~(7u<<12),0xAAAAAAAAu&~(7u<<12));
    GPFSEL(0)=0;GPFSEL(1)=0;GPFSEL(2)=0;
    bcm_dir(9,1);  chk("경계 핀9  → FSEL0 shift27",(GPFSEL(0)>>27)&7,1);
    bcm_dir(10,1); chk("경계 핀10 → FSEL1 shift0",GPFSEL(1)&7,1);
    bcm_dir(19,1); chk("경계 핀19 → FSEL1 shift27",(GPFSEL(1)>>27)&7,1);
    bcm_dir(20,1); chk("경계 핀20 → FSEL2 shift0",GPFSEL(2)&7,1);
    GPLEV0=0;
    bcm_write(5,1); lev_commit(); chk("write(5,1)→LEV bit5",bcm_read(5),1);
    bcm_write(5,0); lev_commit(); chk("write(5,0)→LEV bit5=0",bcm_read(5),0);
    GPLEV0=BIT(7);  chk("read(7) 주입값 반영",bcm_read(7),1);

    puts("[도시 A: S3C2450]");
    GPGCON=0xAAAA0000u; GPGDAT=0;
    s3c_dir(2,1);
    chk("dir(2): CON[5:4]=01",(GPGCON>>4)&3,1);
    chk("dir(2): 이웃 보존",GPGCON&~(3u<<4),0xAAAA0000u&~(3u<<4));
    GPGDAT=0xF0u;
    s3c_write(1,1); chk("write(1,1): DAT",GPGDAT,0xF2u);
    s3c_write(4,0); chk("write(4,0): DAT",GPGDAT,0xE2u);
    chk("read(1)",s3c_read(1),1);

    puts("[입력 처리]");
    int seq[]={0,1,1,0,1}, edges=0;
    for(int i=0;i<5;i++) edges+=edge_detect(seq[i]);
    chk("edge: 0,1,1,0,1 → 상승 2회",edges,2);
    int db[]={0,1,0,1,1,1,0,0,1,1,1}, last=0;
    for(int i=0;i<11;i++) last=debounce(db[i]);
    chk("debounce: 튐 후 1 확정",last,1);

    printf("[결과] 실패 %d건 -> exit %d %s\n",fails,fails,fails?"":"(전체 통과)");
    return fails;
}
