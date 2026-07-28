# LAB-28 · 구청 개청 — 매칭 엔진 미니어처
제공: 명부 구조·장치 등록 경로(try_match_device)·지연 재시도. TODO 2개:
- TODO 1 driver_register — 기존 장치 명부 대조(순서 독립의 반쪽)
- TODO 2 try_bind — strcmp 대조 → probe → 0=결합 / -EPROBE_DEFER=재시도 표식
`make test`: 4시나리오(결합·미결합·후등록 결합·defer 재시도) 실패 수=exit → 완성 시 0.
시나리오 S3 단독 실패는 TODO 1 미완의 지문이다.
미니어처 원칙: 논리 등가·공학 축약(락·참조계수·전원관리 생략 — 슬라이드 경계표 참조).
강사용: platform_sim_sol.c는 학생 배포본에서 제거한다.
