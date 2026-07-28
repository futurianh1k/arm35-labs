/* Q4 결혼의 성사(H28 축) — compatible 대조 한 케이스를 완성하라. */
#include <stdio.h>
#include <string.h>
struct drv { const char *name; const char *match[3]; };
struct dev { const char *name, *compat; const struct drv *bound; };

void try_bind(struct dev *d, const struct drv *v){
    /* TODO: v->match 명단(NULL 종료)에서 d->compat 일치 시 d->bound=v */
    (void)d; (void)v;
}
int main(void){
    static const struct drv uart={"drv-uart",{"arm,pl011","arm,primecell",0}};
    struct dev a={"uart0","arm,pl011",0};
    struct dev b={"mystery","foo,bar",0};
    int fails=0;
    try_bind(&a,&uart); try_bind(&b,&uart);
    if(a.bound!=&uart){ puts("FAIL — 기대 pl011 결합, 관측 미결합"); fails++; }
    if(b.bound!=0){ puts("FAIL — 기대 mystery 미결합, 관측 결합"); fails++; }
    if(!fails) puts("Q4 PASS");
    return fails;
}
