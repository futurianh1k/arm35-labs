/* LAB-14 main.c — 자동 채점 하니스: exit(실패 케이스 수), 0=완전 통과 */
#include <stdio.h>
int guard_call(const char *s, int *len, int *upper);  /* guard.s */

struct tc { const char *name, *s; int len, upper; };
static const struct tc T[] = {
    {"빈 문자열",  "",        0, 0},
    {"대표 케이스","Arm",     3, 1},
    {"전부 대문자","HELLO",   5, 5},
    {"혼합·공백",  "a b C!",  6, 1},
    {"경계 0x40/5B","@AZ[",   4, 2},
    {"긴 문자열",  "The Quick Brown Fox Jumps Over The Lazy Dog 0123456789 END!", 59, 12},
};

int main(void){
    int n = sizeof(T)/sizeof(T[0]), pass = 0;
    for (int i = 0; i < n; i++){
        int len = -1, upper = -1;
        int viol = guard_call(T[i].s, &len, &upper);
        int ok = (len == T[i].len) && (upper == T[i].upper) && (viol == 0);
        printf("[%s] %-12s len=%d(기대 %d) upper=%d(기대 %d)%s\n",
               ok ? "PASS" : "FAIL", T[i].name, len, T[i].len, upper, T[i].upper,
               viol ? " [계약 위반: 보존 레지스터 파괴]" : "");
        if (ok) pass++;
    }
    printf("PASS %d/%d\n", pass, n);
    return n - pass;   /* echo $? = 실패 수, 0이면 완전 통과 */
}
