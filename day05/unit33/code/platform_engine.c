/* 28차시 매칭 엔진 — 완성본 동봉(공용 부품). 오늘의 손은 mychar.c다. */
#include <string.h>
#include "sim.h"
static struct device *devs[MAXN]; static int ndev;
static struct driver *drvs[MAXN]; static int ndrv;
static void try_bind(struct device *d, struct driver *v){
    if (d->bound) return;
    for (int i = 0; v->match[i]; i++)
        if (strcmp(v->match[i], d->compat) == 0){
            int ret = v->probe(d);
            if (ret == 0) d->bound = v;
            else if (ret == -EPROBE_DEFER) d->deferred = 1;
            return;
        }
}
static void try_match_device(struct device *d){
    for (int i = 0; i < ndrv; i++) try_bind(d, drvs[i]);
}
int device_register(struct device *d){
    d->bound = 0; d->deferred = 0;
    devs[ndev++] = d;
    try_match_device(d);
    return 0;
}
int driver_register(struct driver *v){
    drvs[ndrv++] = v;
    for (int i = 0; i < ndev; i++) try_bind(devs[i], v);
    return 0;
}
void retry_deferred(void){
    for (int i = 0; i < ndev; i++)
        if (devs[i]->deferred && !devs[i]->bound){
            devs[i]->deferred = 0;
            try_match_device(devs[i]);
        }
}
