CC=arm-linux-gnueabihf-gcc
CFLAGS=-O1 -static -Wall
SRC?=q4.c
check:
	@$(CC) $(CFLAGS) -o q4t $(SRC)
	@qemu-arm ./q4t > .out 2>&1; e=$$?; cat .out; exit $$e
check-sol:
	@$(MAKE) -s check SRC=q4_sol.c
clean:
	rm -f q4t .out
