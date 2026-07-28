/* LAB-19 led_sim.c — 학생 골격: TODO를 채워 make test exit 0을 만든다 */
#include "s3c2450_gpio.h"

volatile unsigned sfr_mem[0x10000/4];

void led_init(void){
    /* TODO 1: 하위 4핀(0~3)을 출력(01)으로.
     * 반드시 RMW — 상위 비트(다른 핀들의 운명)를 보존한다.
     *   unsigned c = GPGCON;
     *   c &= ~...;  c |= ...;  GPGCON = c;                          */
}

void led_on(int n){
    /* TODO 2: active-low 점등 — DAT의 n번 비트를 0으로 */
    (void)n;
}

void led_off(int n){
    /* TODO 3: 소등 — DAT의 n번 비트를 1로 */
    (void)n;
}

void led_toggle(int n){
    /* TODO 4: 반전 — XOR 한 줄 */
    (void)n;
}
