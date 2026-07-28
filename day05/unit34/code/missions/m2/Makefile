# M2: 시민의 임무 — check(회귀+신규) / check-sol
CC=arm-linux-gnueabihf-gcc
CFLAGS=-O1 -static -Wall -I.
SRC?=mychar.c

check: $(SRC) harness_ext.c platform_engine.c
	@$(CC) $(CFLAGS) -o m2_test $(SRC) platform_engine.c harness_ext.c
	@qemu-arm ./m2_test; e=$$?; \
	 [ $$e -eq 0 ] && echo "[판정] M2 PASS -> exit 0" || { echo "[판정] M2 FAIL(실패 $$e)"; exit $$e; }

check-sol:
	@$(MAKE) -s check SRC=mychar_sol.c

clean:
	rm -f m2_test
