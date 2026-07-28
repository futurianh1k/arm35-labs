/* LAB-19 모범답안 (강사용 — 학생 배포 제외) */
#include "s3c2450_gpio.h"
volatile unsigned sfr_mem[0x10000/4];
void led_init(void){
    unsigned c = GPGCON;
    c &= ~0xFFu;            /* 4핀 x 2비트 청소 */
    c |=  0x55u;            /* 01 01 01 01 = 출력 */
    GPGCON = c;             /* RMW 완성 */
}
void led_on(int n){  GPGDAT &= ~(1u << n); }   /* active-low */
void led_off(int n){ GPGDAT |=  (1u << n); }
void led_toggle(int n){ GPGDAT ^= (1u << n); }
