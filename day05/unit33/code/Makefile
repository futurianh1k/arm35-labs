# LAB-33: 시민 탄생식 — test / test-sol
CC=arm-linux-gnueabihf-gcc
CFLAGS=-O1 -static -Wall -I.

test: mychar.c harness.c platform_engine.c sim_kernel.h sim.h
	@$(CC) $(CFLAGS) -o mychar_test mychar.c platform_engine.c harness.c
	@qemu-arm ./mychar_test; echo "[판정] echo \$$? → $$?  (완성 기준 0)"

test-sol: mychar_sol.c harness.c platform_engine.c
	@$(CC) $(CFLAGS) -o mychar_test_sol mychar_sol.c platform_engine.c harness.c
	@qemu-arm ./mychar_test_sol; echo "[판정] echo \$$? → $$?  (기대값 0)"

clean:
	rm -f mychar_test mychar_test_sol
