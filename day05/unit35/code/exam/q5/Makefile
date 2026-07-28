CC=arm-linux-gnueabihf-gcc
CFLAGS=-O1 -static -Wall
SRC?=q5.c
check:
	@$(CC) $(CFLAGS) -o q5t $(SRC)
	@qemu-arm ./q5t > .out 2>&1; e=$$?; cat .out; exit $$e
check-sol:
	@$(MAKE) -s check SRC=q5_sol.c
clean:
	rm -f q5t .out
