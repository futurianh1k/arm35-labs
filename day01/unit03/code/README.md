# H03 실습 코드 — 프로세서·레지스터·버스·메모리
| 파일 | 용도 | 실행 |
|------|------|------|
| meminfo.c | code/data/heap/stack 주소 지도 관찰 | gcc -O0 -o meminfo meminfo.c && ./meminfo |
| survey.sh | 캐시·메모리 구성 실측 | bash survey.sh |
| hierarchy_table.md | 계층표·서술형 워크시트 | 실측값으로 작성 |

완료 기준: 32/64비트 meminfo 출력 2종 + 계층표 완성본 커밋.
