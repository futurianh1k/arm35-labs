/* LAB-22 실습 A — volatile 유무의 objdump 대조 표본
 * 두 함수는 소스가 같고 포인터 자격만 다르다. -O2에서 운명이 갈린다. */
unsigned poll_novol(unsigned *fr){          /* 비volatile: hoist 표적 */
    unsigned spin=0;
    while(!(*fr & (1u<<5))) spin++;
    return spin;
}
unsigned poll_vol(volatile unsigned *fr){   /* volatile: 매회 접근 유지 */
    unsigned spin=0;
    while(!(*fr & (1u<<5))) spin++;
    return spin;
}
