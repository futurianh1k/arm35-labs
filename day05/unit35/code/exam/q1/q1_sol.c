/* Q1 비트의 손(H22 축) — FIELD 연산 두 함수 완성. 괄호 규율이 채점이다. */
#include <stdio.h>
static unsigned field_shift(unsigned m){ return (unsigned)__builtin_ctz(m); }

unsigned field_prep(unsigned mask, unsigned val){
    return (val << field_shift(mask)) & mask;
}
unsigned field_get(unsigned mask, unsigned reg){
    return (reg & mask) >> field_shift(mask);
}
int main(void){
    struct { unsigned m,v,reg,prep,get; } t[]={
        {0x000000F0u, 0x5u, 0x000003A5u, 0x50u, 0xAu},
        {0x00000038u, 0x6u, 0x00000000u, 0x30u, 0x0u},
        {0xF0000000u, 0xFFu,0x8BADF00Du, 0xF0000000u, 0x8u},
    };
    int fails=0;
    for (unsigned i=0;i<3;i++){
        unsigned p=field_prep(t[i].m,t[i].v), g=field_get(t[i].m,t[i].reg);
        if(p!=t[i].prep){ printf("FAIL prep 케이스 %u — 기대 0x%X 관측 0x%X\n",i+1,t[i].prep,p); fails++; }
        if(g!=t[i].get){  printf("FAIL get  케이스 %u — 기대 0x%X 관측 0x%X\n",i+1,t[i].get,g);  fails++; }
    }
    if(!fails) puts("Q1 PASS");
    return fails;
}
