# LAB-07 Makefile — 베어메탈 빌드·부팅 (arm-none-eabi 우선, 없으면 gnueabihf로 대체)
CROSS  := $(shell command -v arm-none-eabi-gcc >/dev/null 2>&1 && echo arm-none-eabi- || echo arm-linux-gnueabihf-)
CC      = $(CROSS)gcc
CFLAGS  = -marm -mcpu=arm926ej-s -O0 -ffreestanding -nostdlib -Wall
ELF     = h07.elf

$(ELF): startup.o main.o linker.ld
	$(CC) -nostdlib -T linker.ld startup.o main.o -o $@
	$(CROSS)objdump -d $@ | head -32 > vectors_dump.txt

startup.o: startup.s
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(ELF)
	@echo "[QEMU] 종료는 Ctrl-A 다음 X"
	qemu-system-arm -M versatilepb -nographic -audio none -kernel $(ELF)

clean:
	rm -f *.o $(ELF) vectors_dump.txt
