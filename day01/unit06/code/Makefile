# LAB-06 Makefile — QEMU 사용자모드 + gdbstub로 v5TE 레지스터 관찰
AS   = arm-linux-gnueabihf-as
LD   = arm-linux-gnueabihf-ld
BIN  = regs_demo

$(BIN): regs_demo.s
	$(AS) -march=armv5te -o regs_demo.o $<
	$(LD) -o $@ regs_demo.o

debug: $(BIN)
	@echo "[QEMU] gdb 접속 대기 중 (포트 1234) — 다른 터미널에서 make gdb"
	qemu-arm -g 1234 ./$(BIN)

gdb: $(BIN)
	gdb-multiarch -q ./$(BIN) -x gdb_init.txt

clean:
	rm -f $(BIN) regs_demo.o
