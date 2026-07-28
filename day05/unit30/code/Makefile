# LAB-30: 화물칸 조립 — init / check(3부) / check-sol / fetch
DTC=dtc

init:                      ## 뼈대 트리 + 실 DTB 사본 + 자리표시
	@mkdir -p boot/overlays
	@cp -n templates/config.txt  boot/config.txt  || true
	@cp -n templates/cmdline.txt boot/cmdline.txt || true
	@cp vendor/bcm2711-rpi-4-b.dtb boot/
	@touch boot/kernel8.img
	@echo "[init] boot/ 준비 — TODO를 채워라"

fetch:                     ## (선택) 배포 DTB 갱신
	curl -sL -o vendor/bcm2711-rpi-4-b.dtb \
	  https://raw.githubusercontent.com/raspberrypi/firmware/master/boot/bcm2711-rpi-4-b.dtb

boot/overlays/i2c1-on.dtbo: overlays/i2c1-on.dts
	@mkdir -p boot/overlays
	$(DTC) -@ -I dts -O dtb -o $@ $<

check: init boot/overlays/i2c1-on.dtbo   ## [1부]승객·선언문 [2부]실물 라운드트립 [3부]병합
	@ok=1; \
	for f in boot/config.txt boot/cmdline.txt boot/kernel8.img boot/bcm2711-rpi-4-b.dtb boot/overlays/i2c1-on.dtbo; do \
	  [ -e $$f ] || { echo "  MISS: $$f"; ok=0; }; done; \
	for k in "^enable_uart=1" "^kernel=kernel8.img" "^arm_64bit=1" "^dtoverlay=" "^dtparam="; do \
	  grep -q "$$k" boot/config.txt || { echo "  config 필수키 미달: $$k"; ok=0; }; done; \
	[ $$(wc -l < boot/cmdline.txt) -le 1 ] || { echo "  cmdline: 한 줄 규칙 위반"; ok=0; }; \
	grep -q "console=serial0,115200" boot/cmdline.txt || { echo "  cmdline: console 조각 미달"; ok=0; }; \
	grep -q "root=/dev/mmcblk0p2" boot/cmdline.txt || { echo "  cmdline: root 조각 미달"; ok=0; }; \
	grep -q "rootwait" boot/cmdline.txt || { echo "  cmdline: rootwait 미달"; ok=0; }; \
	[ $$ok -eq 1 ] && echo "[1부] 승객·선언문 PASS" || { echo "[1부] FAIL"; exit 1; }
	@$(DTC) -I dtb -O dts boot/bcm2711-rpi-4-b.dtb -o .rt.dts 2>/dev/null \
	  && $(DTC) -I dts -O dtb .rt.dts -o .rt.dtb 2>/dev/null \
	  && echo "[2부] 실물 라운드트립 PASS" || { echo "[2부] FAIL"; exit 1; }
	@fdtoverlay -i boot/bcm2711-rpi-4-b.dtb -o .merged.dtb boot/overlays/i2c1-on.dtbo \
	  && $(DTC) -I dtb -O dts .merged.dtb 2>/dev/null | grep -A8 "i2c@7e804000" | grep -q '"okay"' \
	  && echo "[3부] 실물 병합(disabled→okay) PASS" || { echo "[3부] FAIL"; exit 1; }
	@echo "[판정] PASS -> exit 0"

check-sol:
	@rm -rf boot; $(MAKE) -s init >/dev/null
	@cp sol/config.txt sol/cmdline.txt boot/
	@$(DTC) -@ -I dts -O dtb -o boot/overlays/i2c1-on.dtbo sol/i2c1-on.dts
	@$(MAKE) -s check

clean:
	rm -rf boot .rt.dts .rt.dtb .merged.dtb
