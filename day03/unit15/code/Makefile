# LAB-15: 지역성 실측 — run / sweep / stride
CC=arm-linux-gnueabihf-gcc
CFLAGS=-O1 -static -Wall
BIN=cache_lab

all: $(BIN)
$(BIN): cache_lab.c
	$(CC) $(CFLAGS) -o $@ $<

run: $(BIN)              ## 기본 N=2048 실측 + 판정(exit 15)
	@qemu-arm ./$(BIN); echo "[판정] echo \$$? → $$?  (기대값 15)"

sweep:                   ## N=1024/2048/4096 비율 스윕
	@for n in 1024 2048 4096; do \
	  $(CC) $(CFLAGS) -DN=$$n -o $(BIN)_$$n cache_lab.c; \
	  qemu-arm ./$(BIN)_$$n | head -1; done

stride:                  ## 보폭 스캔으로 라인 크기 역산
	@$(CC) $(CFLAGS) -DSTRIDE -o $(BIN)_st cache_lab.c
	@qemu-arm ./$(BIN)_st; echo "[판정] echo \$$? → $$?  (기대값 15)"

clean:
	rm -f $(BIN) $(BIN)_* 
