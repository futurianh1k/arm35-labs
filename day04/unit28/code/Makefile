# LAB-28: 매칭 엔진 — test / test-sol
CC=arm-linux-gnueabihf-gcc
CFLAGS=-O1 -static -Wall

test: platform_sim.c harness.c sim.h
	@$(CC) $(CFLAGS) -o sim_test platform_sim.c harness.c
	@qemu-arm ./sim_test; echo "[판정] echo \$$? → $$?  (완성 기준 0)"

test-sol: platform_sim_sol.c harness.c
	@$(CC) $(CFLAGS) -o sim_test_sol platform_sim_sol.c harness.c
	@qemu-arm ./sim_test_sol; echo "[판정] echo \$$? → $$?  (기대값 0)"

clean:
	rm -f sim_test sim_test_sol
