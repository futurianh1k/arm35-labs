/* bench_sol.h — 모범답안 (강사용, 학생 배포 제외) */
#ifndef BENCH_H
#define BENCH_H
#include <time.h>
#include <stdlib.h>
#define MAXN 64
typedef struct { double med, min, max; } stat_t;
static volatile long bench_sink;
static double now_ms(void){
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts);
    return ts.tv_sec*1000.0 + ts.tv_nsec/1e6;
}
static double once_ms(void (*fn)(void)){ double t0=now_ms(); fn(); return now_ms()-t0; }
static int cmp_d(const void*a,const void*b){
    double x=*(const double*)a,y=*(const double*)b; return (x>y)-(x<y);
}
static stat_t stats_of(double *s, int n){
    qsort(s, n, sizeof(double), cmp_d);
    stat_t r = { s[n/2], s[0], s[n-1] };
    return r;
}
static stat_t bench(void (*fn)(void), int warm, int n){
    double s[MAXN];
    for (int i=0;i<warm;i++) (void)once_ms(fn);      /* 예열: 버림 */
    for (int i=0;i<n;i++)    s[i]=once_ms(fn);       /* 본측정: 수집 */
    return stats_of(s, n);
}
#endif
