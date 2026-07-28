# LAB-22: asm(사고 관찰) / test(하니스) / test-sol
CC=arm-linux-gnueabihf-gcc
CFLAGS=-O2 -static -Wall

asm: poll_demo.c              ## volatile 유무 objdump 대조
	@$(CC) -O2 -c poll_demo.c -o poll_demo.o
	@arm-linux-gnueabihf-objdump -d poll_demo.o > poll_demo.objdump
	@echo "== poll_novol (읽기 실종/1회 hoist를 찾아라) =="
	@sed -n '/<poll_novol>:/,/^$$/p' poll_demo.objdump
	@echo "== poll_vol (루프 안 ldr 유지 확인) =="
	@sed -n '/<poll_vol>:/,/^$$/p' poll_demo.objdump

test: hal.h hal_lab.c         ## 실패 수 = exit, 완성 시 0
	@$(CC) $(CFLAGS) -o hal_test hal_lab.c
	@qemu-arm ./hal_test; echo "[판정] echo \$$? → $$?  (완성 기준 0)"

test-sol: hal_sol.h hal_lab.c
	@$(CC) $(CFLAGS) -DUSE_SOL -o hal_test_sol hal_lab.c
	@qemu-arm ./hal_test_sol; echo "[판정] echo \$$? → $$?  (기대값 0)"

clean:
	rm -f hal_test hal_test_sol poll_demo.o poll_demo.objdump
