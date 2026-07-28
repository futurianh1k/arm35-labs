# LAB-17: 이중 매핑 실증 — run / maps / ro
CC=aarch64-linux-gnu-gcc
CFLAGS=-O1 -static -Wall
BIN=alias_lab

$(BIN): alias_lab.c
	$(CC) $(CFLAGS) -o $@ $<

run: $(BIN)              ## 기본 실증 + 판정(exit 17)
	@qemu-aarch64 ./$(BIN); echo "[판정] echo \$$? → $$?  (기대값 17)"

maps: $(BIN)             ## 두 매핑을 /proc/self/maps에서 확인
	@qemu-aarch64 ./$(BIN) maps; echo "[판정] echo \$$? → $$?  (기대값 17)"

ro: $(BIN)               ## B를 읽기전용으로 -> 쓰기 SIGSEGV 관측(139가 정상)
	@qemu-aarch64 ./$(BIN) ro; echo "[관측] echo \$$? → $$?  (SIGSEGV=139가 정상)"

clean:
	rm -f $(BIN)
