# LAB-31 · 싣고, 깨우고, 검증하기
- 엔진: minibake.py = H29 완성본(공용 부품 동봉)
- TODO: recipes/hello.mb 의 COMPILE(크로스 -static)·INSTALL(가짜 루트 image/usr/bin) /
        hello.service 의 3부작 필수 키(절대경로!)
- append 체험: recipes/hello.mb.append 주석 해제 → 원본 불변으로 " (patched)" 배너 확인
- `make check`: [1부] qemu-aarch64 실행 "HELLO from recipe" grep
               [2부] 폴백 검증기 + systemd-analyze verify(경로는 빌드 산출물로 치환해 검사)
실기: enable(링크 생성)·재부팅·status/journalctl 캡처는 실보드 절차(T-14).
강사용: sol/ 제거. 
