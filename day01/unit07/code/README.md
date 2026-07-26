# H07 실습 코드 — 동작 모드·예외·Reset (베어메탈 첫 부팅)
| 파일 | 역할 |
|------|------|
| startup.s | 벡터 8행 + Reset(스택·벡터 복사·main 호출) + SWI 핸들러 |
| main.c | PL011 UART 출력(putc/puts), svc #0 발화, msg_swi 정의 |
| linker.ld | 0x10000 링크, .vectors 최우선 배치 (개념: 벡터=0번지) |
| Makefile / run.sh | make run 또는 bash run.sh 로 빌드+부팅 |

기대 출력 3줄: BOOT: bare-metal alive → SWI! handler speaking → BACK: returned from SWI
종료: Ctrl-A 누른 뒤 X. 완료 기준은 학생 워크북 LAB-07 체크리스트를 따른다.

설계 메모: QEMU -kernel은 0x10000에 적재하고 ARM926에는 VBAR가 없으므로,
Reset에서 벡터 블록(명령 8개+리터럴 풀 64바이트)을 0x0으로 복사한다.
슬라이드 발췌에는 이 복사 루프가 생략되어 있다 — 워크북 심화 1번의 소재다.
