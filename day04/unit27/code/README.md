# LAB-27 · 측정기 제작과 분기의 극장
- 1부 `make check`: bench.h의 TODO A(stats_of: 정렬·med는 s[n/2] 상위중앙)·TODO B(예열+수집)
  완성 → 결정적 유닛테스트 exit 0. 측정기를 먼저 검증한다(함정 0).
- 2부 `make run` : sorted vs random의 ns/elem·ratio 실측(관측 — 판정 아님).
  배수의 절대값은 호스트·TCG 의존이며, 해석 한 줄(분기 예측)이 채점 중심이다.
- demo.cmm      : 독해 지문 — 여섯 문장의 목적을 표로 재구성한다(오픈북 5호 지참).
강사용: bench_sol.h는 학생 배포본에서 제거한다.
