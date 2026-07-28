# LAB-19 · 운명표 조작 — GPG LED 4핀 (SFR 시뮬레이터)
- `make test` : 골격 상태의 실패 수를 먼저 채증(출발선) → TODO 4개를 채워 exit 0
- 채점 포인트: ① CON 하위 8비트 0x55 ② 상위 비트 보존(RMW) ③ active-low on/off ④ toggle 왕복
- 심화: GPF 버튼 입력(CON 00 + DAT 읽기 + GPxUDP 풀 설정)을 케이스로 확장해 본다
강사용: led_sim_sol.c(모범답안)는 학생 배포본에서 제거한다. make test-sol로 채점 기준 확인.
