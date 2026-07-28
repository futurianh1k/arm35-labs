# LAB-22 · 사고 재연과 계층 제작 (mini-HAL)
- `make asm` : -O2에서 volatile 유무 두 폴링 함수의 objdump 대조 — 비volatile 쪽 루프에서
               읽기(ldr)가 사라지거나 루프 밖 1회로 hoist된 증거를 캡처한다.
- `make test`: hal.h의 TODO 6개를 완성해 12케이스 exit 0 — 괄호 함정·경계(31,28)·넘침 절단 포함.
- 강사용: hal_sol.h(모범답안)는 학생 배포본에서 제거. make test-sol로 채점 기준 확인.
주의: 실습 A는 -O2가 전제다(O0에서는 사고가 재연되지 않음 — 그것 자체가 "범인=최적화"의 반증).
