# H14 실습 코드 — ARM 명령어 종합 실습 (str_stats)
| 파일 | 용도 |
|------|------|
| str_stats.s | 미션 골격 — TODO-1·2·3만 채운다 |
| main.c | 자동 채점 하니스 (exit=실패 수) |
| guard.s | 보존 레지스터(r4/r5/r8) 감시 인프라 — 수정 금지 |
| Makefile | make test(채점) / make gdb(실패 재현) |
| checklist.md | 배점 100 자가 점검표 |
| str_stats_sol.s | 강사용(배포 금지) — make test-sol |

절차: 설계 3분(배역·가설표) → TODO-1 → make test → 커밋 → TODO-2 → TODO-3 → echo $?=0 채증.
판정: `qemu-arm ./str_stats_test ; echo $?` → 0 이 완전 통과.
주의: 골격 그대로는 전 케이스 FAIL(exit=6)이 정상 시작 상태다.
