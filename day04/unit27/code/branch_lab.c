/* LAB-27 2부 — 분기의 극장: 같은 일, 다른 결 (관측용) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef USE_SOL
#include "bench_sol.h"
#else
#include "bench.h"
#endif
#define N 32768
#define REPS 50
static unsigned char a_rand[N], a_sort[N];

static void sum_rand(void){
    long s=0;
    for(int r=0;r<REPS;r++) for(int i=0;i<N;i++) if(a_rand[i]>=128) s+=a_rand[i];
    bench_sink=s;
}
static void sum_sort(void){
    long s=0;
    for(int r=0;r<REPS;r++) for(int i=0;i<N;i++) if(a_sort[i]>=128) s+=a_sort[i];
    bench_sink=s;
}
static int cmp_b(const void*a,const void*b){
    return *(const unsigned char*)a - *(const unsigned char*)b;
}
int main(void){
    srand(42);
    for(int i=0;i<N;i++) a_rand[i]=(unsigned char)(rand()&0xFF);
    memcpy(a_sort,a_rand,N); qsort(a_sort,N,1,cmp_b);

    stat_t S=bench(sum_sort,2,9), R=bench(sum_rand,2,9);
    double ns_s=S.med*1e6/((double)REPS*N), ns_r=R.med*1e6/((double)REPS*N);
    puts("[LAB-27 2부] 조건 합산 — 데이터의 결");
    printf("  정렬   : med=%7.2fms  min=%7.2f  %5.2f ns/elem\n",S.med,S.min,ns_s);
    printf("  무작위 : med=%7.2fms  min=%7.2f  %5.2f ns/elem\n",R.med,R.min,ns_r);
    printf("  ratio(무작위/정렬) = %.2f\n", ns_s>0?ns_r/ns_s:0);
    puts("  해석 과제: 차이(또는 무차이)의 원인을 분기 예측으로 한 줄 설명하라.");
    return 0;
}
