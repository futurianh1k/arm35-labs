# LAB-30 · 화물칸 조립 — 스펙에서 실물까지
- `make init`  : boot/ 뼈대 + 실물 DTB 사본(vendor 동봉, make fetch로 갱신 가능) + kernel8 자리표시
- TODO 3개: boot/config.txt(필수 5키+이유 주석), boot/cmdline.txt(한 줄 3조각),
            overlays/i2c1-on.dts(status="okay")
- `make check` 3부: [1부] 승객·선언문 스펙 [2부] 실물 DTB 라운드트립 [3부] fdtoverlay 병합으로
  i2c@7e804000 이 disabled→okay 로 뒤집혔는지 (배포 기본은 disabled)
- 안전 3원칙: 원본(vendor/) 보존 — 작업은 boot/ 사본에서 · 라운드트립 · 병합 검증
실기(실보드): boot/ 내용을 실제 부팅 파티션에 반영 → 재부팅 → /proc/device-tree/soc/i2c@7e804000/status 확인 (T-14 절차).
강사용: sol/ 은 학생 배포본에서 제거한다.
