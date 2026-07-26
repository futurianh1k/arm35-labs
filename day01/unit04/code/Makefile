# LAB-04 Makefile — native / cross(AArch64) / cross(ARM32)
CC_HOST = gcc
CC_A64  = aarch64-linux-gnu-gcc
CC_A32  = arm-linux-gnueabihf-gcc
CFLAGS  = -O2 -Wall

all: hello_host hello_a64 hello_a32

hello_host: hello.c
	$(CC_HOST) $(CFLAGS) -o $@ $<

hello_a64: hello.c
	$(CC_A64) $(CFLAGS) -static -o $@ $<

hello_a32: hello.c
	$(CC_A32) $(CFLAGS) -static -o $@ $<

run: all
	./hello_host
	qemu-aarch64 ./hello_a64
	qemu-arm ./hello_a32

inspect: all
	file hello_host hello_a64 hello_a32 | tee file_report.txt

clean:
	rm -f hello_host hello_a64 hello_a32 file_report.txt
