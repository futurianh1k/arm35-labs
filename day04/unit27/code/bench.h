/* bench.h — 속지 않는 측정기 (LAB-27에서 완성) */
#ifndef BENCH_H
#define BENCH_H
#include <time.h>
#include <stdlib.h>
#define MAXN 64
typedef struct { double med, min, max; } stat_t;
static volatile long bench_sink;                 /* 증발 방지 안전핀 */

static double now_ms(void){
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts);
    return ts.tv_sec*1000.0 + ts.tv_nsec/1e6;
}
static double once_ms(void (*fn)(void)){         /* 제공: 1회 측정 */
    double t0 = now_ms(); fn(); return now_ms()-t0;
}
static int cmp_d(const void*a,const void*b){
    double x=*(const double*)a, y=*(const double*)b;
    return (x>y)-(x<y);
}

/* TODO A — 표본 배열의 통계: 오름차순 정렬(qsort) 후
   min=s[0], max=s[n-1], med=s[n/2] (짝수면 상위 중앙 규약) */
static stat_t stats_of(double *s, int n){
    (void)s; (void)n;
    stat_t r = { -1, -1, -1 };   /* TODO */
    return r;
}

/* TODO B — 예열 warm회(버림) + 본측정 n회(수집) 후 stats_of 반환 */
static stat_t bench(void (*fn)(void), int warm, int n){
    (void)fn; (void)warm; (void)n;
    stat_t r = { -1, -1, -1 };   /* TODO: once_ms를 warm+n회 호출 */
    return r;
}
#endif
