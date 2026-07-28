# LAB-27: check(측정기 자기검증) / run(분기 실측) / *-sol
CC=arm-linux-gnueabihf-gcc
CFLAGS=-O2 -static -Wall

check: selfcheck.c bench.h            ## 골격 실패 -> TODO 완성 후 exit 0
	@$(CC) $(CFLAGS) -o selfcheck selfcheck.c
	@qemu-arm ./selfcheck; echo "[판정] echo \$$? → $$?  (완성 기준 0)"

check-sol: selfcheck.c bench_sol.h
	@$(CC) $(CFLAGS) -DUSE_SOL -o selfcheck_sol selfcheck.c
	@qemu-arm ./selfcheck_sol; echo "[판정] echo \$$? → $$?  (기대값 0)"

run: branch_lab.c bench.h             ## 완성된 bench로 실측(관측)
	@$(CC) $(CFLAGS) -o branch_lab branch_lab.c
	@qemu-arm ./branch_lab

run-sol: branch_lab.c bench_sol.h
	@$(CC) $(CFLAGS) -DUSE_SOL -o branch_lab_sol branch_lab.c
	@qemu-arm ./branch_lab_sol

clean:
	rm -f selfcheck selfcheck_sol branch_lab branch_lab_sol
