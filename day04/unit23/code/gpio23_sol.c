/* 모범답안 (강사용 — 학생 배포 제외) */
#include "gpio_regs.h"
volatile unsigned bcm[16];
volatile unsigned s3c[8];
void bcm_dir(int pin, int out){
    int n = pin / 10, sh = (pin % 10) * 3;
    reg_update(&GPFSEL(n), GENMASK(sh+2, sh), out ? 1u : 0u);
}
void bcm_write(int pin, int v){ if (v) GPSET0 = BIT(pin); else GPCLR0 = BIT(pin); }
int  bcm_read(int pin){ return (int)FIELD_GET(BIT(pin), GPLEV0); }
void s3c_dir(int pin, int out){
    reg_update(&GPGCON, GENMASK(pin*2+1, pin*2), out ? 1u : 0u);
}
void s3c_write(int pin, int v){
    if (v) reg_set_bits(&GPGDAT, BIT(pin)); else reg_clr_bits(&GPGDAT, BIT(pin));
}
int  s3c_read(int pin){ return (int)FIELD_GET(BIT(pin), GPGDAT); }
int edge_detect(int now){
    static int prev = 0;
    int e = (prev == 0 && now == 1);
    prev = now; return e;
}
int debounce(int sample){
    static int last = -2, streak = 0, stable = 0;
    if (sample == last) streak++; else { last = sample; streak = 1; }
    if (streak >= 3) stable = sample;
    return stable;
}
