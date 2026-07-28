/* hal_sol.h — 모범답안 (강사용, 학생 배포 제외) */
#ifndef HAL_H
#define HAL_H
#define BIT(n)          (1u << (n))
#define GENMASK(h, l)   (((0xFFFFFFFFu) >> (31u-(h))) & ~(((1u)<<(l))-1u))
#define FIELD_SHIFT(m)  ((unsigned)__builtin_ctz(m))
#define FIELD_PREP(m,v) (((unsigned)(v) << FIELD_SHIFT(m)) & (m))
#define FIELD_GET(m,r)  (((unsigned)(r) & (m)) >> FIELD_SHIFT(m))
static inline void reg_set_bits(volatile unsigned *r, unsigned m){ *r = *r | m; }
static inline void reg_clr_bits(volatile unsigned *r, unsigned m){ *r = *r & ~m; }
static inline void reg_update(volatile unsigned *r, unsigned m, unsigned v){
    *r = (*r & ~m) | FIELD_PREP(m, v);
}
#endif
