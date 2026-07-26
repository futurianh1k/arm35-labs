# H06 실습 코드 — ARMv5TE Programmer's Model
| 파일 | 용도 |
|------|------|
| regs_demo.s | 관찰용 어셈블리 (3장면: 산술 / CPSR / PC+8) |
| Makefile | make debug(창1) → make gdb(창2) |
| gdb_init.txt | gdb 자동 접속 스크립트 |
| gdb_cheat.txt | 필수 5명령 + 채집 미션 |

완료 기준: 3장면 로그(레지스터 덤프) evidence 커밋 + "왜 +8인가" 1문장 답.
안전 수칙: 실제 보드가 아닌 QEMU 사용자 모드이므로 마음껏 실패해도 된다.
