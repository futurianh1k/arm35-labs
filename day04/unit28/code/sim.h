/* sim.h — 커널 디바이스 모델 미니어처의 계약 (논리 등가·공학 축약) */
#ifndef SIM_H
#define SIM_H
#define EPROBE_DEFER 517          /* 커널의 -EPROBE_DEFER 관례 차용 */
#define MAXN 8

struct driver;
struct device {
    const char *name, *compat;    /* 존재의 등록: 이름과 열쇠 */
    struct driver *bound;         /* 결합 상대(행정의 완성)   */
    int deferred;                 /* 재시도 명부 표식         */
};
struct driver {
    const char *name;
    const char *match[4];         /* 자물쇠 명단(of_match_table) */
    int (*probe)(struct device *);/* 입주 절차                  */
};

int  device_register(struct device *d);
int  driver_register(struct driver *v);
void retry_deferred(void);        /* 커널의 지연 재시도를 1회 재주선으로 축약 */
#endif
