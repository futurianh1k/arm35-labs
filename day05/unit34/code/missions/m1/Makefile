# M1: 이중 IRQ — check / check-sol  (회귀: IRQ x5 OK · 신규: K2)
CROSS  := $(shell command -v arm-none-eabi-gcc >/dev/null 2>&1 && echo arm-none-eabi- || echo arm-linux-gnueabihf-)
CC      = $(CROSS)gcc
CFLAGS  = -marm -mcpu=arm926ej-s -O1 -ffreestanding -nostdlib -Wall
QEMU    = qemu-system-arm -M versatilepb -nographic -audio none -kernel
SRC    ?= irq34.c

irq34.elf: start.s $(SRC) linker.ld
	$(CC) $(CFLAGS) -Wl,--build-id=none -T linker.ld start.s $(SRC) -o $@

check: irq34.elf
	@printf 'kk' | timeout 6 $(QEMU) irq34.elf > .out 2>&1 || true
	@grep -q "IRQ x5 OK" .out && echo "  회귀(IRQ x5 OK) PASS" || { echo "  회귀 FAIL"; exit 1; }
	@grep -q "K2" .out && echo "  신규(K2 표시)   PASS" || { echo "  신규(K2) FAIL — TODO A/B/C 확인"; exit 1; }
	@echo "[판정] M1 PASS -> exit 0"

check-sol:
	@rm -f irq34.elf; $(MAKE) -s check SRC=irq34_sol.c

clean:
	rm -f irq34.elf .out
