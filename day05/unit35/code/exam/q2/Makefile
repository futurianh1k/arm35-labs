CROSS := $(shell command -v arm-none-eabi-gcc >/dev/null 2>&1 && echo arm-none-eabi- || echo arm-linux-gnueabihf-)
CC=$(CROSS)gcc
CFLAGS=-marm -mcpu=arm926ej-s -O1 -ffreestanding -nostdlib -Wall
SRC?=q2.c
check:
	@$(CC) $(CFLAGS) -Wl,--build-id=none -T linker.ld start.s $(SRC) -o q2.elf 2>/dev/null
	@timeout 3 qemu-system-arm -M versatilepb -nographic -audio none -kernel q2.elf > .out 2>&1 || true
	@if grep -q "EXAM Q2 PL011 OK" .out; then echo "Q2 PASS"; \
	 else echo "FAIL — 기대 \"EXAM Q2 PL011 OK\" 관측 없음"; exit 1; fi
check-sol:
	@rm -f q2.elf; $(MAKE) -s check SRC=q2_sol.c
clean:
	rm -f q2.elf .out
