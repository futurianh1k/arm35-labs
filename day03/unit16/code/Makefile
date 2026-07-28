# LAB-16: 베어메탈 MMU 점화 (versatilepb / ARM926EJ-S)
CROSS  := $(shell command -v arm-none-eabi-gcc >/dev/null 2>&1 && echo arm-none-eabi- || echo arm-linux-gnueabihf-)
CC      = $(CROSS)gcc
CFLAGS  = -marm -mcpu=arm926ej-s -O1 -ffreestanding -nostdlib -Wall
ELF     = mmu926.elf

$(ELF): start.s mmu926.c linker.ld
	$(CC) $(CFLAGS) -Wl,--build-id=none -T linker.ld start.s mmu926.c -o $@

run: $(ELF)              ## 대화형 실행 (종료: Ctrl+A 다음 X)
	@echo "[QEMU] 종료는 Ctrl-A 다음 X"
	qemu-system-arm -M versatilepb -nographic -audio none -kernel $(ELF)

check: $(ELF)            ## 자동 판정: ALIAS OK 문자열 -> exit 0
	@timeout 5 qemu-system-arm -M versatilepb -nographic -audio none -kernel $(ELF) > .out.txt 2>&1 || true
	@cat .out.txt
	@grep -q "ALIAS OK" .out.txt && grep -q "MMU ON" .out.txt \
	  && echo "[판정] PASS -> exit 0" || (echo "[판정] FAIL"; exit 1)

clean:
	rm -f $(ELF) .out.txt
