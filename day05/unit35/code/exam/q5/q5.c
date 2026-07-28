/* Q5 시민의 문(H33 축) — read 한 문: 한도·경계 통로·반환 관례. */
#include <stdio.h>
#include <string.h>
static int fault_next=0;
static long copy_to_user_sim(char*u,const char*k,long n){
    if(fault_next){fault_next=0;return 3;} memcpy(u,k,n); return 0;
}
#define EFAULT 14

long my_read(const char *kbuf, long klen, char *ubuf, long n){
    /* TODO: min(n,klen) 만큼 경계 통로로 복사 — 실패 -EFAULT, 성공 시 옮긴 수 */
    (void)kbuf; (void)klen; (void)ubuf; (void)n; return -99;
}
int main(void){
    char u[16]; int fails=0; long r;
    r=my_read("arm35",5,u,16);
    if(!(r==5&&!memcmp(u,"arm35",5))){ printf("FAIL 전체읽기 — 기대 5 관측 %ld\n",r); fails++; }
    r=my_read("arm35",5,u,3);
    if(!(r==3&&!memcmp(u,"arm",3))){ printf("FAIL 부분읽기 — 기대 3 관측 %ld\n",r); fails++; }
    fault_next=1; r=my_read("arm35",5,u,5);
    if(r!=-EFAULT){ printf("FAIL 경계실패 — 기대 -14 관측 %ld\n",r); fails++; }
    if(!fails) puts("Q5 PASS");
    return fails;
}
