# LAB-25: SP804 알람 — run / check
CROSS  := $(shell command -v arm-none-eabi-gcc >/dev/null 2>&1 && echo arm-none-eabi- || echo arm-linux-gnueabihf-)
CC      = $(CROSS)gcc
CFLAGS  = -marm -mcpu=arm926ej-s -O1 -ffreestanding -nostdlib -Wall
ELF     = timer25.elf
QEMU    = qemu-system-arm -M versatilepb -nographic -audio none -kernel $(ELF)

$(ELF): start.s timer25.c linker.ld
	$(CC) $(CFLAGS) -Wl,--build-id=none -T linker.ld start.s timer25.c -o $@

run: $(ELF)              ## 0.2초 간격 5틱 관찰 (종료 Ctrl+A, X)
	@echo "[QEMU] 종료는 Ctrl-A 다음 X"
	$(QEMU)

check: $(ELF)            ## DONE(5 ticks) 판정 -> exit 0
	@timeout 5 $(QEMU) > .out.txt 2>&1 || true
	@cat .out.txt
	@grep -q "DONE(5 ticks)" .out.txt \
	  && echo "[판정] PASS -> exit 0" || (echo "[판정] FAIL"; exit 1)

clean:
	rm -f $(ELF) .out.txt
