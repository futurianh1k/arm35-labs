# LAB-12 Makefile — 배열 복사·리터럴 풀 채증
AS   = arm-linux-gnueabihf-as
LD   = arm-linux-gnueabihf-ld
OBJD = arm-linux-gnueabihf-objdump
BIN  = copy8

$(BIN): copy8.s
	$(AS) -march=armv5te -g -o $(BIN).o $<
	$(LD) -o $@ $(BIN).o

run: $(BIN)
	@qemu-arm ./$(BIN); echo "[판정] echo \$$? → $$?  (기대값 36)"

dis: $(BIN)
	$(OBJD) -d $(BIN) | sed -n '/<_start>:/,/^$$/p'
	@echo "--- 미션: ldr rX,[pc,#..] 와 리터럴 풀 .word(src/dst 주소)를 찾아라 ---"

debug: $(BIN)
	@echo "[QEMU] gdb 접속 대기 중 (포트 1234) — 다른 터미널에서 make gdb"
	qemu-arm -g 1234 ./$(BIN)

gdb: $(BIN)
	gdb-multiarch -q ./$(BIN) -x gdb_init.txt

clean:
	rm -f $(BIN) $(BIN).o
