# LAB-24: PL011 에코 — run(대화형) / check(파이프 자동) / check2(대문자 개조 후)
CROSS  := $(shell command -v arm-none-eabi-gcc >/dev/null 2>&1 && echo arm-none-eabi- || echo arm-linux-gnueabihf-)
CC      = $(CROSS)gcc
CFLAGS  = -marm -mcpu=arm926ej-s -O1 -ffreestanding -nostdlib -Wall
ELF     = uart24.elf
QEMU    = qemu-system-arm -M versatilepb -nographic -audio none -kernel $(ELF)

$(ELF): start.s uart24.c linker.ld
	$(CC) $(CFLAGS) -Wl,--build-id=none -T linker.ld start.s uart24.c -o $@

run: $(ELF)              ## 타이핑 에코 (종료 Ctrl+A, X)
	@echo "[QEMU] 종료는 Ctrl-A 다음 X"
	$(QEMU)

check: $(ELF)            ## 'OK' 주입 -> [O][K] 판정 -> exit 0
	@printf 'OK' | timeout 3 $(QEMU) > .out.txt 2>&1 || true
	@cat .out.txt
	@grep -q "UART24 READY" .out.txt && grep -q "\[O\]\[K\]" .out.txt \
	  && echo "[판정] PASS -> exit 0" || (echo "[판정] FAIL"; exit 1)

check2: $(ELF)           ## 대문자 개조 후 통과 대상: 'ok' -> [O][K]
	@printf 'ok' | timeout 3 $(QEMU) > .out2.txt 2>&1 || true
	@grep -q "\[O\]\[K\]" .out2.txt \
	  && echo "[판정] PASS(개조 완료) -> exit 0" || (echo "[판정] 아직 소문자 에코 -> FAIL"; exit 1)

clean:
	rm -f $(ELF) .out.txt .out2.txt
