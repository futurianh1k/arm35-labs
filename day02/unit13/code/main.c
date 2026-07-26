/* LAB-13 main.c — 계약서의 C쪽 서명 */
int asm_max(int a, int b);      /* 계약서의 C쪽 서명 */

int c_add1(int a){ return a + 1; }   /* 심화(역방향 호출)용 helper */

int main(void){
    return asm_max(3, 9) + asm_max(7, 2) - 9; /* 9+7-9=7 */
}
