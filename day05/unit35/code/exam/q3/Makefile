CC=arm-linux-gnueabihf-gcc
CFLAGS=-O1 -static -Wall
SRC?=q3.c
check:
	@$(CC) $(CFLAGS) -o q3t $(SRC)
	@qemu-arm ./q3t > .out 2>&1; e=$$?; cat .out; exit $$e
check-sol:
	@$(MAKE) -s check SRC=q3_sol.c
clean:
	rm -f q3t .out
