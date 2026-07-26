# LAB-08 Makefile — 파이프라인 증거 수집 (QEMU 사용자모드 + gdbstub)
AS   = arm-linux-gnueabihf-as
LD   = arm-linux-gnueabihf-ld
BIN  = pipeline_demo

$(BIN): pipeline_demo.s
	$(AS) -march=armv5te -g -o $(BIN).o $<
	$(LD) -o $@ $(BIN).o

run: $(BIN)
	@qemu-arm ./$(BIN); echo "[판정] echo \$$? → $$?  (기대값 40)"

debug: $(BIN)
	@echo "[QEMU] gdb 접속 대기 중 (포트 1234) — 다른 터미널에서 make gdb"
	qemu-arm -g 1234 ./$(BIN)

gdb: $(BIN)
	gdb-multiarch -q ./$(BIN) -x gdb_init.txt

clean:
	rm -f $(BIN) $(BIN).o
