# H09 실습 코드 — AArch64 첫 관찰
| 파일 | 용도 |
|------|------|
| regs64.s | 3주소·w뷰·adr·xzr·exit(93) 관찰용 |
| Makefile | make run(판정 12) / make debug → make gdb |
| gdb_init.txt | aarch64 수동 설정 포함 자동 접속 |
| gdb_cheat.txt | 필수 5명령 + 채집 미션 |

직접 판정: `qemu-aarch64 ./regs64 ; echo $?` → 12
완료 기준: w/x 관계·SP/PC 분리 로그 커밋. RPi4 lscpu는 가능 시 첨부(불가 시 "직접 실행 못함" 명기).
