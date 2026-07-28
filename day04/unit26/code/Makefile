# LAB-26: IRQ 틱 — check(학생본) / check-sol(강사 확인)
CROSS  := $(shell command -v arm-none-eabi-gcc >/dev/null 2>&1 && echo arm-none-eabi- || echo arm-linux-gnueabihf-)
CC      = $(CROSS)gcc
CFLAGS  = -marm -mcpu=arm926ej-s -O1 -ffreestanding -nostdlib -Wall
QEMU    = qemu-system-arm -M versatilepb -nographic -audio none -kernel

irq26.elf: start.s irq26.c linker.ld
	$(CC) $(CFLAGS) -Wl,--build-id=none -T linker.ld start.s irq26.c -o $@
irq26_sol.elf: start.s irq26_sol.c linker.ld
	$(CC) $(CFLAGS) -Wl,--build-id=none -T linker.ld start.s irq26_sol.c -o $@

run: irq26.elf           ## 대화형 (종료 Ctrl+A, X)
	$(QEMU) irq26.elf

check: irq26.elf         ## IRQ x5 OK 판정 -> exit 0 (골격은 타임아웃 FAIL이 정상)
	@timeout 6 $(QEMU) irq26.elf > .out.txt 2>&1 || true
	@cat .out.txt
	@grep -q "IRQ x5 OK" .out.txt \
	  && echo "[판정] PASS -> exit 0" || (echo "[판정] FAIL (골격이면 정상 — 핸들러 완성 후 재실행)"; exit 1)

check-sol: irq26_sol.elf
	@timeout 6 $(QEMU) irq26_sol.elf > .out2.txt 2>&1 || true
	@tail -3 .out2.txt
	@grep -q "IRQ x5 OK" .out2.txt && echo "[판정] PASS -> exit 0"

clean:
	rm -f irq26.elf irq26_sol.elf .out.txt .out2.txt
