# LAB-20: 잠든 건물에 불 켜기 — dtb / dump / dtbo / check
DTC=dtc

dtb: bcm-mini.dts               ## base 컴파일(-@: 심볼 포함 — 라벨 해석의 열쇠)
	$(DTC) -@ -I dts -O dtb -o bcm-mini.dtb bcm-mini.dts
	@echo "[OK] bcm-mini.dtb"

dump: dtb                       ## 역컴파일로 현재 상태 확인
	$(DTC) -I dtb -O dts bcm-mini.dtb | grep -B1 -A4 "i2c@"

dtbo: overlay-i2c1.dts          ## 오버레이 컴파일
	$(DTC) -@ -I dts -O dtb -o overlay-i2c1.dtbo overlay-i2c1.dts
	@echo "[OK] overlay-i2c1.dtbo"

check: dtb dtbo                 ## 병합 후 i2c1 okay 판정 -> exit 0
	fdtoverlay -i bcm-mini.dtb -o merged.dtb overlay-i2c1.dtbo
	@$(DTC) -I dtb -O dts merged.dtb > merged.dts
	@grep -A4 "i2c@fe804000" merged.dts | grep -q "status = \"okay\"" \
	  && echo "[판정] i2c1 = okay -> PASS (exit 0)" \
	  || (echo "[판정] i2c1이 아직 잠들어 있다 -> FAIL"; exit 1)

check-sol: dtb                  ## 강사용: 모범답안으로 판정 확인
	$(DTC) -@ -I dts -O dtb -o overlay_sol.dtbo overlay-i2c1_sol.dts
	fdtoverlay -i bcm-mini.dtb -o merged_sol.dtb overlay_sol.dtbo
	@$(DTC) -I dtb -O dts merged_sol.dtb | grep -A4 "i2c@fe804000" | grep -q "okay" \
	  && echo "[판정] PASS -> exit 0"

clean:
	rm -f *.dtb *.dtbo merged.dts
