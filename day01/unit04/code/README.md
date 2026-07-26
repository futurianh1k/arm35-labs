# H04 실습 코드 — Legacy와 Modern 개발환경 설정
| 파일 | 용도 | 실행 |
|------|------|------|
| setup_ubuntu.sh | 툴체인·QEMU 일괄 설치 | bash setup_ubuntu.sh |
| verify_toolchain.sh | 트리플릿·버전 증거 수집 | bash verify_toolchain.sh |
| hello.c + Makefile | 1소스 3표적 크로스 빌드 | make run / make inspect |

완료 기준: make run에서 3종 실행 성공, file_report.txt와 toolchain_report.txt 커밋.
주의: -static을 빼면 qemu-aarch64 실행 시 동적 로더 경로 문제가 생긴다. 왜 그런지 워크북 심화 문항에서 다룬다.
