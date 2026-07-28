# 실기 브리지 — 진짜 커널 모듈 Makefile (T-14 실보드 세션에서 사용)
# 사전: sudo apt install raspberrypi-kernel-headers  (RPi OS 기준)
obj-m := mychar_real.o
KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
