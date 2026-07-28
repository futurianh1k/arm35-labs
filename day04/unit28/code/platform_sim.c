/* LAB-28 — [제공] 명부·장치 경로 / [TODO] 드라이버 경로·결합 분기 */
#include <string.h>
#include "sim.h"

static struct device *devs[MAXN]; static int ndev;
static struct driver *drvs[MAXN]; static int ndrv;

/* ===== TODO 2 — 중매의 심장: 대조 -> probe -> 결합/지연 =====
 * 1) d->bound 있으면 즉시 반환(이미 결혼)
 * 2) v->match 명단(NULL 종료)에서 d->compat와 strcmp 일치 탐색
 * 3) 일치 시 ret = v->probe(d);
 *    ret==0            -> d->bound = v;
 *    ret==-EPROBE_DEFER-> d->deferred = 1;  (재시도 명부 표식)   */
static void try_bind(struct device *d, struct driver *v){
    (void)d; (void)v;
    /* TODO 2 */
}

/* 제공 — 새 주민 등록 시: 공무원 명부 전체와 대조 */
static void try_match_device(struct device *d){
    for (int i = 0; i < ndrv; i++) try_bind(d, drvs[i]);
}
int device_register(struct device *d){
    d->bound = 0; d->deferred = 0;
    devs[ndev++] = d;
    try_match_device(d);
    return 0;
}

/* ===== TODO 1 — 순서 독립의 반쪽: 새 공무원 등록 시 기존 주민 대조 ===== */
int driver_register(struct driver *v){
    drvs[ndrv++] = v;
    /* TODO 1: 기존 devs 전체를 훑어 try_bind(devs[i], v) */
    return 0;
}

/* 제공 — 지연 재시도(커널의 defer 재시도를 1회 재주선으로 축약) */
void retry_deferred(void){
    for (int i = 0; i < ndev; i++)
        if (devs[i]->deferred && !devs[i]->bound){
            devs[i]->deferred = 0;
            try_match_device(devs[i]);
        }
}
