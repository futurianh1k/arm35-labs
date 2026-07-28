# H34 · 통합 PBL — 세 미션, 백 점
- 규정: 2~3인 팀 · 오픈북 6장 + 닷새의 내 코드 · 팀 간 코드 공유 금지
- 배점: M1 이중 IRQ 30 / M2 GETCOUNT 30 / M3 goodbye 레시피 40 — 부분 점수 없음
- 판정: ./grader.sh (각 미션 make check exit만 신뢰, 회귀/신규 분리 표기)
- 제출: grader 리포트 전문 + 커밋 로그(미션별 담당 m1:/m2:/m3: 접두) + 관측 한 줄×3
- 명세의 최종 권위는 각 missions/*/README.md 다. 스펙의 침묵(M2 RESET-카운터)은
  팀이 정의하고 근거를 Evidence에 남긴다.
강사용: ./grader.sh --sol (3/3·100 확인) · 각 미션의 *sol* 파일은 학생 배포본에서 제거.
