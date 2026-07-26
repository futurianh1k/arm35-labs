# LAB-13 Makefile — C↔어셈 상호호출 (AAPCS 계약 검증)
CC   = arm-linux-gnueabihf-gcc
BIN  = abi_demo
CFLAGS = -g -static -marm -O0

$(BIN): main.c asm_max.s
	$(CC) $(CFLAGS) -o $@ main.c asm_max.s

run: $(BIN)
	@qemu-arm ./$(BIN); echo "[판정] echo \$$? → $$?  (기대값 7)"

run-o2: main.c asm_max.s
	$(CC) -g -static -marm -O2 -o $(BIN)_o2 main.c asm_max.s
	@qemu-arm ./$(BIN)_o2; echo "[판정 -O2] echo \$$? → $$?  (위반 실험 대조용)"

debug: $(BIN)
	@echo "[QEMU] gdb 접속 대기 중 (포트 1234) — 다른 터미널에서 make gdb"
	qemu-arm -g 1234 ./$(BIN)

gdb: $(BIN)
	gdb-multiarch -q ./$(BIN) -x gdb_init.txt

clean:
	rm -f $(BIN) $(BIN)_o2
