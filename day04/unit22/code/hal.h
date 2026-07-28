/* hal.h — 이번 주 공용 부품 (LAB-22에서 완성)
 * TODO 6개: GENMASK / FIELD_PREP / FIELD_GET / reg_set_bits / reg_clr_bits / reg_update */
#ifndef HAL_H
#define HAL_H

#define BIT(n)          (1u << (n))

/* TODO 1: h..l 연속 1 마스크 — 예: GENMASK(7,4)=0xF0
 * 힌트: (0xFFFFFFFFu >> (31-(h))) 와 하위 절단의 조합, 괄호 규율! */
#define GENMASK(h, l)   (0u /* TODO */)

#define FIELD_SHIFT(m)  ((unsigned)__builtin_ctz(m))

/* TODO 2: 값을 필드 자리로 — ((v) << shift) & (m) */
#define FIELD_PREP(m,v) (0u /* TODO */)

/* TODO 3: 필드 값 추출 — ((r) & (m)) >> shift */
#define FIELD_GET(m,r)  (0u /* TODO */)

/* TODO 4~6: RMW 3형제 */
static inline void reg_set_bits(volatile unsigned *r, unsigned m){
    (void)r; (void)m; /* TODO 4 */
}
static inline void reg_clr_bits(volatile unsigned *r, unsigned m){
    (void)r; (void)m; /* TODO 5 */
}
static inline void reg_update(volatile unsigned *r, unsigned m, unsigned v){
    (void)r; (void)m; (void)v; /* TODO 6: (읽고 & ~m) | FIELD_PREP */
}
#endif
