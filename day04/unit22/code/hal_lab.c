/* LAB-22 하니스 — 12케이스, 실패 수 = exit (완성 시 0) */
#include <stdio.h>
#ifdef USE_SOL
#include "hal_sol.h"
#else
#include "hal.h"
#endif

static int fails=0;
static void chk(const char*name, unsigned got, unsigned want){
    int ok=(got==want);
    printf("  %-34s got=0x%08X want=0x%08X %s\n",name,got,want,ok?"PASS":"FAIL");
    if(!ok) fails++;
}
int main(void){
    puts("[LAB-22] mini-HAL 12케이스");
    chk("BIT(5)",BIT(5),0x20);
    int n=3; chk("BIT 괄호 함정: BIT(n)<<1",BIT(n)<<1,0x10);
    chk("GENMASK(7,4)",GENMASK(7,4),0xF0);
    chk("GENMASK(31,28) 상단 경계",GENMASK(31,28),0xF0000000);
    chk("GENMASK(5,3)",GENMASK(5,3),0x38);
    chk("FIELD_PREP(GENMASK(5,3),6)",FIELD_PREP(GENMASK(5,3),6),0x30);
    chk("FIELD_PREP 넘침 절단",FIELD_PREP(GENMASK(5,3),0xFF),0x38);
    chk("FIELD_GET(GENMASK(9,4),0x3A5)",FIELD_GET(GENMASK(9,4),0x3A5),0x3A);
    volatile unsigned r=0xAAAA5555u;
    reg_set_bits(&r,0x0F00u);  chk("set_bits 결과",r,0xAAAA5F55u);
    reg_clr_bits(&r,0x00F0u);  chk("clr_bits 결과",r,0xAAAA5F05u);
    r=0x12345678u; reg_update(&r,GENMASK(15,8),0xAB);
    chk("update 필드 교체",r,0x1234AB78u);
    chk("update 이웃 보존",r&0xFFFF00FFu,0x12340078u);
    printf("[결과] 실패 %d건 -> exit %d %s\n",fails,fails,fails?"":"(전체 통과)");
    return fails;
}
