# LAB-23: 두 도시 공용 GPIO — test / test-sol
CC=arm-linux-gnueabihf-gcc
CFLAGS=-O1 -static -Wall

test: gpio23.c harness.c gpio_regs.h hal.h
	@$(CC) $(CFLAGS) -o gpio_test gpio23.c harness.c
	@qemu-arm ./gpio_test; echo "[판정] echo \$$? → $$?  (완성 기준 0)"

test-sol: gpio23_sol.c harness.c
	@$(CC) $(CFLAGS) -o gpio_test_sol gpio23_sol.c harness.c
	@qemu-arm ./gpio_test_sol; echo "[판정] echo \$$? → $$?  (기대값 0)"

clean:
	rm -f gpio_test gpio_test_sol
