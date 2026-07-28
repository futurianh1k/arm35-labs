/* LAB-19 하니스 — 함수 호출 후 레지스터 비트패턴을 검증한다. 실패 수 = exit */
#include <stdio.h>
#include "s3c2450_gpio.h"

static int fails = 0;
static void chk(const char *name, unsigned got, unsigned want){
    int ok = (got == want);
    printf("  %-28s got=0x%08X want=0x%08X  %s\n", name, got, want, ok?"PASS":"FAIL");
    if(!ok) fails++;
}

int main(void){
    puts("[LAB-19] GPG LED 시뮬레이터 검증");

    GPGCON = 0xAAAA0000u;                 /* 상위 비트에 선주민을 심는다 */
    GPGDAT = 0x0u;
    led_init();
    chk("init: 하위 8비트=0x55(출력)", GPGCON & 0xFFu, 0x55u);
    chk("init: 상위 비트 보존(RMW)",   GPGCON & 0xFFFF0000u, 0xAAAA0000u);

    GPGDAT = 0xFu;                        /* 전부 소등(1) 상태에서 */
    led_on(2);
    chk("on(2): bit2=0 (active-low)",   GPGDAT & 0xFu, 0xBu);
    led_off(2);
    chk("off(2): bit2=1",               GPGDAT & 0xFu, 0xFu);
    led_toggle(1);
    chk("toggle(1) 1회: bit1=0",        GPGDAT & 0xFu, 0xDu);
    led_toggle(1);
    chk("toggle(1) 2회: 복귀",          GPGDAT & 0xFu, 0xFu);

    printf("[결과] 실패 %d건 -> exit %d %s\n", fails, fails, fails?"":"(전체 통과)");
    return fails;
}
