# LAB-33 · 시민 탄생식 (28차시 엔진 + 오늘의 드라이버)
- 제공: platform_engine.c(28 완성본)·sim_kernel.h(경계표 포함)·open 패턴
- TODO 4: read/write/ioctl(RESET·-EINVAL)/probe(입주식) — 반환·-EFAULT 계약 준수
- `make test` 7단: 입주→open→write→read→RESET→빈 read→미지 cmd(-22). 실패수=exit.
- 심화: GETLEN(klen 조회) ioctl + 자작 케이스 — 34차시 미션 2의 예행.
- realko_template/: 실기 브리지(obj-m·절차 주석) — 빌드·적재는 T-14 실보드 세션.
강사용: mychar_sol.c 제거.
