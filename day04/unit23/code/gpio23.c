/* LAB-23 — [제공] BCM2711 구현 / [TODO] 2450 구현 + 입력 처리 */
#include "gpio_regs.h"
volatile unsigned bcm[16];
volatile unsigned s3c[8];

/* ===== 제공: 도시 B (오늘 배운 산수·창구의 완성본) ===== */
void bcm_dir(int pin, int out){
    int n = pin / 10, sh = (pin % 10) * 3;          /* 좌표 산수 */
    reg_update(&GPFSEL(n), GENMASK(sh+2, sh), out ? 1u : 0u);
}
void bcm_write(int pin, int v){
    if (v) GPSET0 = BIT(pin);                        /* RMW 없음 */
    else   GPCLR0 = BIT(pin);
}
int bcm_read(int pin){ return (int)FIELD_GET(BIT(pin), GPLEV0); }

/* ===== TODO: 도시 A (19차시 지식을 HAL 문법으로 재작성) ===== */
void s3c_dir(int pin, int out){
    (void)pin; (void)out;
    /* TODO 1: GPGCON의 pin*2 위치 2비트를 out?01:00 — reg_update 사용 */
}
void s3c_write(int pin, int v){
    (void)pin; (void)v;
    /* TODO 2: GPGDAT RMW — set/clr 프리미티브 사용 */
}
int s3c_read(int pin){
    (void)pin;
    /* TODO 3: GPGDAT에서 FIELD_GET */
    return -1;
}

/* ===== TODO: 입력 처리 ===== */
int edge_detect(int now){
    /* TODO 4: static prev 기억, 0->1일 때만 1 반환 */
    (void)now; return -1;
}
int debounce(int sample){
    /* TODO 5: 직전 표본과 같으면 streak++, 다르면 streak=1.
       streak>=3이면 stable=sample. 반환은 stable(초기 0). */
    (void)sample; return -1;
}
