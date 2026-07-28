/* LAB-15 cache_lab: 지역성의 가격 실측
 * 판정: 두 합이 일치하고 기대값(N*N)이면 exit 15
 * 시간: clock_gettime(CLOCK_MONOTONIC), 2회 측정 후 2회차 채택 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef N
#define N 2048                     /* N x N int = 16MB(기본) */
#endif
static int a[N][N];
static volatile long sink;         /* 최적화로 루프가 접히는 것 방지 */

static double now_ms(void){
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts);
    return ts.tv_sec*1000.0 + ts.tv_nsec/1e6;
}
static long sum_row(void){         /* 행 우선 — 라인의 결을 따라 */
    long s=0;
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) s+=a[i][j];
    sink=s; return s;
}
static long sum_col(void){         /* 열 우선 — 결을 거슬러 */
    long s=0;
    for(int j=0;j<N;j++) for(int i=0;i<N;i++) s+=a[i][j];
    sink=s; return s;
}
#ifdef STRIDE                      /* make stride: 보폭 스캔 */
static double walk_ns(int stride_b){          /* 접근 1회당 ns */
    char *p=(char*)a; long bytes=(long)N*N*sizeof(int);
    long acc=0; double t0=now_ms(); long s=0;
    for(int r=0;r<4;r++) for(long i=0;i<bytes;i+=stride_b){ s+=p[i]; acc++; }
    sink=s; return (now_ms()-t0)*1e6/acc;
}
#endif
int main(void){
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) a[i][j]=1;
#ifdef STRIDE
    int st[]={4,16,64,256};
    printf("[stride] N=%d, 접근 1회당 비용(ns)\n",N);
    for(int k=0;k<4;k++) printf("  stride %3dB : %6.2f ns/access\n",st[k],walk_ns(st[k]));
    puts("[해석] 보폭<=라인이면 미스 비용이 여러 접근에 분산되어 싸고,");
    puts("       보폭이 라인을 넘어서면 매 접근이 새 라인 미스 -> 비용이 뛰고 평평해진다.");
    puts("       비용이 급등해 포화하는 경계 ~= 캐시 라인 크기");
    return 15;
#else
    long r1,r2,c1,c2; double t;
    t=now_ms(); r1=sum_row(); (void)r1; t=now_ms()-t;      /* 1회차: 워밍업 */
    t=now_ms(); r2=sum_row(); double trow=now_ms()-t;
    t=now_ms(); c1=sum_col(); (void)c1; t=now_ms()-t;
    t=now_ms(); c2=sum_col(); double tcol=now_ms()-t;
    long expect=(long)N*N;
    printf("[N=%d] row=%.1fms col=%.1fms ratio=%.2f\n",N,trow,tcol,trow>0?tcol/trow:0);
    printf("[검증] row_sum=%ld col_sum=%ld expect=%ld\n",r2,c2,expect);
    if(r2==c2 && r2==expect){ puts("[판정] PASS -> exit 15"); return 15; }
    puts("[판정] FAIL"); return 1;
#endif
}
