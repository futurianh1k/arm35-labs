/* Q3 시간의 산수(H25 축) — 공리: Load = 시간(ms) x (클럭Hz / 1000) */
#include <stdio.h>
unsigned load_for(unsigned clk_hz, unsigned ms){
    /* TODO: 목표 ms 주기의 Load 값 — 오답 함정: /10 실수는 케이스 2가 잡는다 */
    (void)clk_hz; (void)ms; return 0;
}
int main(void){
    struct { unsigned hz,ms,want; } t[]={
        {1000000u,   1u,    1000u},
        {1000000u,  60u,   60000u},   /* 함정 검산: 6,000이 아니다 */
        {1000000u, 200u,  200000u},
    };
    int fails=0;
    for (unsigned i=0;i<3;i++){
        unsigned g=load_for(t[i].hz,t[i].ms);
        if(g!=t[i].want){ printf("FAIL 케이스 %u — 기대 %u 관측 %u\n",i+1,t[i].want,g); fails++; }
    }
    if(!fails) puts("Q3 PASS");
    return fails;
}
