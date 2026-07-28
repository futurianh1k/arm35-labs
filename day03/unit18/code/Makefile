# LAB-18: 가상 도시의 지도 복원 — dtb / dts / check
QEMU=qemu-system-aarch64
DTB=virt.dtb
DTS=virt.dts

dtb:                     ## 배선 명세 덤프(부팅 없이 즉시 종료)
	$(QEMU) -M virt,dumpdtb=$(DTB) -cpu cortex-a72
	@echo "[OK] $(DTB) 생성"

dts: dtb                 ## 사람이 읽는 형태로 역컴파일
	dtc -I dtb -O dts $(DTB) -o $(DTS)
	@wc -l $(DTS)

check: dts               ## 4구역(uart·intc·rtc·virtio) 자동 판정 -> exit 0
	@ok=0; \
	grep -q "pl011@9000000"      $(DTS) && ok=$$((ok+1)) || echo "MISS: uart(pl011)"; \
	grep -q "intc@8000000"       $(DTS) && ok=$$((ok+1)) || echo "MISS: intc(GIC)"; \
	grep -q "pl031@9010000"      $(DTS) && ok=$$((ok+1)) || echo "MISS: rtc(pl031)"; \
	grep -q "virtio_mmio@a000000" $(DTS) && ok=$$((ok+1)) || echo "MISS: virtio"; \
	echo "발견 구역: $$ok / 4"; \
	[ $$ok -eq 4 ] && echo "[판정] PASS -> exit 0" || (echo "[판정] FAIL"; exit 1)

clean:
	rm -f $(DTB) $(DTS)
