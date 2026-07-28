# LAB-19: SFR 시뮬레이터 — test(골격) / test-sol(강사 확인용)
CC=arm-linux-gnueabihf-gcc
CFLAGS=-O1 -static -Wall

test: led_sim.c harness.c s3c2450_gpio.h        ## 실패 수 = exit, 완성 시 0
	@$(CC) $(CFLAGS) -o led_test led_sim.c harness.c
	@qemu-arm ./led_test; echo "[판정] echo \$$? → $$?  (완성 기준 0)"

test-sol: led_sim_sol.c harness.c s3c2450_gpio.h
	@$(CC) $(CFLAGS) -o led_test_sol led_sim_sol.c harness.c
	@qemu-arm ./led_test_sol; echo "[판정] echo \$$? → $$?  (기대값 0)"

clean:
	rm -f led_test led_test_sol
