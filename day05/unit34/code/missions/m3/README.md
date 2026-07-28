# M3 · 화물 탑재 (40점) — 명세
- 요구: goodbye_1.0 레시피 신설 — DEPENDS 없이 독립, $CC 크로스 -static,
  image/usr/bin/goodbye 설치, 실행 출력 "GOODBYE from recipe".
- 회귀: 기존 3레시피의 의존 순서·app 실행이 그대로 통과해야 한다.
- 신규: goodbye 빌드·실행 + 2차 실행 시 전 태스크 [skip] 12/12(스탬프 계약 준수).
- 작성 파일 2개: src/goodbye.c, recipes/goodbye.mb.
