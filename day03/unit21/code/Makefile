# LAB-21: 새벽 관측 — inspect / run / trace / check
CROSS  := $(shell command -v arm-none-eabi-gcc >/dev/null 2>&1 && echo arm-none-eabi- || echo arm-linux-gnueabihf-)
CC      = $(CROSS)gcc
ELF     = boot21.elf

$(ELF): boot21.s linker.ld
	$(CC) -marm -mcpu=arm926ej-s -nostdlib -Wl,--build-id=none -T linker.ld boot21.s -o $@

inspect: $(ELF)          ## 명세서 관점 -> boot_report.txt
	@$(CROSS)readelf -h $(ELF) | grep -E "Entry|Machine"  > boot_report.txt
	@$(CROSS)objdump -d $(ELF) | head -20                >> boot_report.txt
	@cat boot_report.txt

run: $(ELF)              ## 실행: UART에 B,T (종료 Ctrl+A, X)
	@echo "[QEMU] 종료는 Ctrl-A 다음 X"
	qemu-system-arm -M versatilepb -nographic -audio none -kernel $(ELF)

trace: $(ELF)            ## 실측 관점 -> trace.log (첫 실행 명령들)
	@timeout 3 qemu-system-arm -M versatilepb -nographic -audio none \
	  -kernel $(ELF) -d in_asm,nochain -D trace.log || true
	@echo "---- trace.log 상단 ----"; head -8 trace.log

check: inspect trace     ## Entry(명세)와 첫 실행 주소(실측)의 일치 -> exit 0
	@grep -q "0x10000" boot_report.txt \
	  && head -8 trace.log | grep -q "0x00010000" \
	  && echo "[판정] Entry=첫 실행=0x10000 일치 -> PASS (exit 0)" \
	  || (echo "[판정] FAIL"; exit 1)

clean:
	rm -f $(ELF) boot_report.txt trace.log
