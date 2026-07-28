CC=arm-linux-gnueabihf-gcc
CFLAGS=-O1 -static -Wall
SRC?=q1.c
check:
	@$(CC) $(CFLAGS) -o q1t $(SRC)
	@qemu-arm ./q1t > .out 2>&1; e=$$?; cat .out; exit $$e
check-sol:
	@$(MAKE) -s check SRC=q1_sol.c
clean:
	rm -f q1t .out
