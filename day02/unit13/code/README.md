# H13 실습 코드 — 분기·Stack·AAPCS 계약
| 파일 | 용도 |
|------|------|
| asm_max.s | leaf 계약 이행 + 중첩/역방향 심화 골격(주석) |
| main.c | C쪽 서명 + c_add1(심화 helper) |
| Makefile | make run(판정 7) / make run-o2(위반 실험 대조) / make gdb |
| gdb_init.txt | asm_max·main 브레이크 자동 설정 |

직접 판정: `qemu-arm ./abi_demo ; echo $?` → 7
위반 실험: asm_max에 `mov r4,#0` 한 줄 추가 → -O0/-O2 재실행 비교(증상 유무 기록).
  원칙: 원본 검증 상태 보존 — 주석 토글로 진행하고 실험 후 원상복구한다.
심화: asm_twice_plus1 주석 해제·완성 → 어셈이 C(c_add1)를 부르는 역방향, LR 대피 필수 체험.
