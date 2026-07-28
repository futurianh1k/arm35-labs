/* s3c2450_gpio.h — 실주소를 이름으로 "옮겨 적는다"
 * 시뮬레이터: REG(addr)가 가짜 64KB SFR 배열로 매핑된다.
 * 실보드 전환(23차시): 이 매핑을 mmap된 실주소로 바꾸는 것뿐 — 문법 불변. */
#ifndef S3C2450_GPIO_H
#define S3C2450_GPIO_H

#define SFR_BASE   0x56000000u              /* GPIO 패밀리 구역 */
extern volatile unsigned sfr_mem[0x10000/4];/* 64KB 가짜 SFR    */
#define REG(a)     (sfr_mem[((a) - SFR_BASE) / 4])

#define GPGCON     REG(0x56000060)          /* 포트 G 운명표(2비트/핀) */
#define GPGDAT     REG(0x56000064)          /* 포트 G 데이터(1비트/핀) */
#define GPGUDP     REG(0x56000068)          /* 포트 G 풀업/다운(2450)  */

/* 수업 규약: LED는 GPG 하위 4핀, active-low(0=점등).
 * 실보드 극성·핀 배정은 MDS2450 매뉴얼로 T-14에 확인한다. */
void led_init(void);
void led_on(int n);
void led_off(int n);
void led_toggle(int n);

#endif
