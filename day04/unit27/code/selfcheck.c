/* LAB-27 1부 — 측정기 자기검증 (결정적 유닛테스트). 실패 수 = exit */
#include <stdio.h>
#ifdef USE_SOL
#include "bench_sol.h"
#else
#include "bench.h"
#endif

static int fails=0;
static void chk(const char*n,double got,double want){
    int ok = (got==want);
    printf("  %-34s got=%g want=%g %s\n",n,got,want,ok?"PASS":"FAIL");
    if(!ok) fails++;
}
static int calls=0;
static void counting_fn(void){ calls++; bench_sink+=calls; }

int main(void){
    puts("[LAB-27 1부] 측정기 자기검증");
    double a[]={3,1,2};
    stat_t r=stats_of(a,3);
    chk("홀수 med {3,1,2}",r.med,2); chk("min",r.min,1); chk("max",r.max,3);
    double b[]={4,1,3,2};
    r=stats_of(b,4);
    chk("짝수 med(상위중앙) {4,1,3,2}",r.med,3); chk("min",r.min,1); chk("max",r.max,4);
    calls=0; r=bench(counting_fn,3,5);
    chk("호출 수 = warm(3)+n(5)",calls,8);
    chk("med>=0 (수집 정상)",(double)(r.med>=0),1);
    printf("[결과] 실패 %d건 -> exit %d %s\n",fails,fails,fails?"":"(측정기 합격)");
    return fails;
}
