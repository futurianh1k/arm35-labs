# LAB-09 Makefile — AArch64 첫 관찰 (qemu-aarch64 + gdbstub)
AS   = aarch64-linux-gnu-as
LD   = aarch64-linux-gnu-ld
BIN  = regs64

$(BIN): regs64.s
	$(AS) -g -o $(BIN).o $<
	$(LD) -o $@ $(BIN).o

run: $(BIN)
	@qemu-aarch64 ./$(BIN); echo "[판정] echo \$$? → $$?  (기대값 12)"

debug: $(BIN)
	@echo "[QEMU] gdb 접속 대기 중 (포트 1234) — 다른 터미널에서 make gdb"
	qemu-aarch64 -g 1234 ./$(BIN)

gdb: $(BIN)
	gdb-multiarch -q ./$(BIN) -x gdb_init.txt

clean:
	rm -f $(BIN) $(BIN).o
