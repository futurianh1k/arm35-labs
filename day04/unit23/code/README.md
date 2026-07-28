# LAB-23 · 두 도시 공용 GPIO 계층
- hal.h는 H22 완성본 동봉(공용 부품). 제공: BCM2711 구현(산수·전용창구의 완성본).
- TODO 5개: 2450 dir/write/read(HAL 관용구 필수) + edge_detect + debounce.
- `make test`: 골격 실패 수 채증 → 완성 후 exit 0. FSEL 경계(핀 9/10/19/20) 케이스 포함 —
  실패 시 나눗셈·나머지를 먼저 의심한다.
- 하니스의 lev_commit()은 SET/CLR 래치를 LEV로 반영하는 하드웨어 흉내다.
강사용: gpio23_sol.c는 학생 배포본에서 제거한다.
