# H12 실습 코드 — Load/Store·주소지정·리터럴 풀
| 파일 | 용도 |
|------|------|
| copy8.s | 포스트인덱스 복사 루프 + 자기검증(합 36) |
| Makefile | make run(판정 36) / make dis(리터럴 풀) / make debug → make gdb |
| gdb_init.txt | loop 브레이크 자동 설정 |
| gdb_cheat.txt | 덤프·대조 미션 |

직접 판정: `qemu-arm ./copy8 ; echo $?` → 36
완료 기준: 전진 로그 + dst 대조 + 리터럴 풀 채증([pc,#..]·.word) 커밋.
심화: 본 루프를 LDMIA/STMIA {r3-r6} 4개 단위로 개조해 같은 36 재검증.
