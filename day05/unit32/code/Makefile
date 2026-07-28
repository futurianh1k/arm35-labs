# LAB-32: 형상 검증기 + 실물 서명 — check(2부) / check-sol
PY?=python3
KC?=minikconfig.py
OV?=overlays/h32-marker.dts
DTC=dtc

check:                      ## [1부] 검증기 유닛(4케이스) [2부] 실물 마커 병합
	@f=0; \
	$(PY) $(KC) Kconfig.mini configs/good.config > .g 2>&1; g=$$?; \
	grep -q "TTY_CORE=y" .g && [ $$g -eq 0 ] \
	  && echo "  [good] 위반0+select 견인 PASS" || { echo "  [good] FAIL"; f=$$((f+1)); }; \
	$(PY) $(KC) Kconfig.mini configs/bad1.config > .b1 2>&1; b1=$$?; \
	[ $$b1 -ge 1 ] && grep -q "SERIAL_CONSOLE" .b1 && grep -q "SERIAL_PL011" .b1 \
	  && echo "  [bad1] 위반 검출·진단 PASS" || { echo "  [bad1] FAIL(검출 $$b1건)"; f=$$((f+1)); }; \
	$(PY) $(KC) Kconfig.mini configs/bad2.config > .b2 2>&1; b2=$$?; \
	[ $$b2 -ge 1 ] && grep -q "NET_DRV" .b2 && grep -q "NET_CORE" .b2 \
	  && echo "  [bad2] 위반 검출·진단 PASS" || { echo "  [bad2] FAIL(검출 $$b2건)"; f=$$((f+1)); }; \
	[ $$f -eq 0 ] && echo "[1부] 검증기 PASS" || { echo "[1부] FAIL($$f)"; exit $$f; }
	@$(DTC) -@ -I dts -O dtb -o .marker.dtbo $(OV) 2>/dev/null \
	  && fdtoverlay -i vendor/bcm2711-rpi-4-b.dtb -o .signed.dtb .marker.dtbo \
	  && $(DTC) -I dtb -O dts .signed.dtb 2>/dev/null | grep -q 'arm35,marker = "h32"' \
	  && echo "[2부] 실물 서명(uart0 marker) PASS" || { echo "[2부] FAIL"; exit 1; }
	@echo "[판정] PASS -> exit 0"

check-sol:
	@$(MAKE) -s check KC=minikconfig_sol.py OV=sol/h32-marker.dts

clean:
	rm -f .g .b1 .b2 .marker.dtbo .signed.dtb
