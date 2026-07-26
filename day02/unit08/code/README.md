# H08 실습 코드 — 5단 파이프라인 증거 수집
| 파일 | 용도 |
|------|------|
| pipeline_demo.s | (A)종속 / (B)독립 / (C)PC+8 관찰용 |
| Makefile | make run(판정 40) / make debug(창1) → make gdb(창2) |
| gdb_init.txt | 자동 접속 + here 브레이크 |
| gdb_cheat.txt | 필수 5명령 + 채집 미션 |

직접 판정: `qemu-arm ./pipeline_demo ; echo $?` → 40
완료 기준: r1·r2·r3 단계 로그 + (+8 산술 근거) evidence 커밋.
안전 수칙: QEMU 사용자모드 — 타이밍은 흉내 내지 않으며 값 정확성만 검증한다.
