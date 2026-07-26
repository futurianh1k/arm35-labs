# H11 실습 코드 — NZCV 플래그 추적
| 파일 | 용도 |
|------|------|
| cond_demo.s | 관찰점 A~D (비교/같음/부호 두 얼굴/S접미사) |
| Makefile | make run(판정 9) / make debug → make gdb |
| gdb_init.txt | 자동 접속 + display/x $cpsr |
| gdb_cheat.txt | CPSR 판독법 + 채집 미션 |

직접 판정: `qemu-arm ./cond_demo ; echo $?` → 9
완료 기준: 가설 vs 관측 표(A~D) + HI·LT 동시 참 해석 커밋.
