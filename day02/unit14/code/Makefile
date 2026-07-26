# LAB-14 Makefile — 종합 미션 자동 채점
CC   = arm-linux-gnueabihf-gcc
CFLAGS = -g -static -marm -O0
BIN  = str_stats_test

$(BIN): main.c guard.s str_stats.s
	$(CC) $(CFLAGS) -o $@ main.c guard.s str_stats.s

test: $(BIN)
	@qemu-arm ./$(BIN); echo "[판정] echo \$$? → $$?  (0 = 완전 통과)"

sol:
	$(CC) $(CFLAGS) -o $(BIN)_sol main.c guard.s str_stats_sol.s

test-sol: sol
	@qemu-arm ./$(BIN)_sol; echo "[판정·솔루션] echo \$$? → $$?  (기대값 0)"

debug: $(BIN)
	@echo "[QEMU] gdb 접속 대기 중 (포트 1234) — 다른 터미널에서 make gdb"
	qemu-arm -g 1234 ./$(BIN)

gdb: $(BIN)
	gdb-multiarch -q ./$(BIN) -x gdb_init.txt

clean:
	rm -f $(BIN) $(BIN)_sol
