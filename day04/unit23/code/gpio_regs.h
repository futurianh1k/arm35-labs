/* gpio_regs.h — 두 도시의 가짜 레지스터 뱅크 (문법 검증용) */
#ifndef GPIO_REGS_H
#define GPIO_REGS_H
#include "hal.h"

/* --- 도시 B: BCM2711 --- */
extern volatile unsigned bcm[16];
#define GPFSEL(n) (bcm[(n)])          /* FSEL0..5   */
#define GPSET0    (bcm[7])            /* 쓰기 래치  */
#define GPCLR0    (bcm[8])
#define GPLEV0    (bcm[9])

/* --- 도시 A: S3C2450 --- */
extern volatile unsigned s3c[8];
#define GPGCON    (s3c[0])
#define GPGDAT    (s3c[1])

/* 공용 API 계약 (구현은 gpio23.c) */
void bcm_dir(int pin, int out);
void bcm_write(int pin, int v);
int  bcm_read(int pin);
void s3c_dir(int pin, int out);       /* GPG 기준, 2비트/핀 */
void s3c_write(int pin, int v);
int  s3c_read(int pin);
int  edge_detect(int now);            /* 0->1 전이만 1     */
int  debounce(int sample);            /* 연속 3회 일치 시 확정값, 그 전엔 직전 확정값 */
#endif
