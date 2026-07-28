/* LAB-28 하니스 — 4시나리오. 실패 수 = exit */
#include <stdio.h>
#include "sim.h"

static int fails=0, probe_calls=0;
static void chk(const char*n, long got, long want){
    int ok=(got==want);
    printf("  %-40s %s\n", n, ok?"PASS":"FAIL");
    if(!ok) fails++;
}
static int probe_ok(struct device *d){ probe_calls++; (void)d; return 0; }
static int defer_once(struct device *d){
    static int first=1; probe_calls++; (void)d;
    if (first){ first=0; return -EPROBE_DEFER; }
    return 0;
}

static struct driver drv_uart={"drv-uart",{"arm,pl011",0},probe_ok};
static struct driver drv_i2c ={"drv-i2c" ,{"brcm,bcm2835-i2c",0},probe_ok};
static struct driver drv_wdt ={"drv-wdt" ,{"arm,sp805",0},defer_once};

static struct device dev_uart={"uart0","arm,pl011",0,0};
static struct device dev_unk ={"mystery","foo,bar",0,0};
static struct device dev_i2c ={"i2c1","brcm,bcm2835-i2c",0,0};
static struct device dev_wdt ={"wdt0","arm,sp805",0,0};

int main(void){
    puts("[LAB-28] 매칭 엔진 4시나리오");
    /* S1: 드라이버 선등록 -> 장치 등록 시 결합 (장치 경로: try_match_device) */
    driver_register(&drv_uart);
    device_register(&dev_uart);
    chk("S1 pl011 결합(장치 후등록 경로)", (long)(dev_uart.bound==&drv_uart), 1);

    /* S2: 아무도 모르는 장치 -> 미결합 유지 */
    device_register(&dev_unk);
    chk("S2 unknown 미결합 유지", (long)(dev_unk.bound==0), 1);

    /* S3: 장치 선등록 -> 드라이버 후등록 시 결합 (TODO 1의 존재 증명) */
    device_register(&dev_i2c);
    driver_register(&drv_i2c);
    chk("S3 i2c 결합(드라이버 후등록 경로)", (long)(dev_i2c.bound==&drv_i2c), 1);

    /* S4: probe가 1회 DEFER -> 재시도로 성사 */
    device_register(&dev_wdt);
    driver_register(&drv_wdt);
    chk("S4a defer 직후엔 미결합", (long)(dev_wdt.bound==0), 1);
    retry_deferred();
    chk("S4b 재시도 후 결합", (long)(dev_wdt.bound==&drv_wdt), 1);
    chk("probe 총 호출 수 = 4 (ok2 + defer2)", probe_calls, 4);

    printf("[결과] 실패 %d건 -> exit %d %s\n",fails,fails,fails?"":"(구청 개청)");
    return fails;
}
