# LAB-10 Makefile — 같은 C, 세 방언(A32/T32/A64) 디스어셈블 + 크기 실측
CC32  = arm-linux-gnueabihf-gcc
CC64  = aarch64-linux-gnu-gcc
OD32  = arm-linux-gnueabihf-objdump
OD64  = aarch64-linux-gnu-objdump
SZ32  = arm-linux-gnueabihf-size
SZ64  = aarch64-linux-gnu-size

all: add5_a32.dis add5_t32.dis add5_a64.dis sizes.txt
	@echo "[완료] 3종 .dis 와 sizes.txt 생성 — make dis 로 나란히 본다"

add5_a32.o: add5.c
	$(CC32) -marm   -O1 -c -o $@ $<
add5_t32.o: add5.c
	$(CC32) -mthumb -O1 -c -o $@ $<
add5_a64.o: add5.c
	$(CC64) -fno-asynchronous-unwind-tables -fno-unwind-tables -O1 -c -o $@ $<

add5_a32.dis: add5_a32.o ; $(OD32) -d $< > $@
add5_t32.dis: add5_t32.o ; $(OD32) -d $< > $@
add5_a64.dis: add5_a64.o ; $(OD64) -d $< > $@

sizes.txt: add5_a32.o add5_t32.o add5_a64.o
	@echo "# 환경: $$($(CC32) --version | head -1) / -O1 / .text 섹션 기준" > $@
	@for f in add5_a32.o add5_t32.o; do \
	  $(SZ32) -A $$f | awk -v F=$$f '$$1==".text"{printf "%-14s .text %5d bytes\n",F,$$2}' >> $@; done
	@$(SZ64) -A add5_a64.o | awk '$$1==".text"{printf "%-14s .text %5d bytes\n","add5_a64.o",$$2}' >> $@
	@cat $@

dis: all
	@for f in add5_a32.dis add5_t32.dis add5_a64.dis; do \
	  echo "===== $$f ====="; sed -n '/<add5>:/,/^$$/p;/<sel>:/,/^$$/p' $$f; done

clean:
	rm -f *.o *.dis sizes.txt
