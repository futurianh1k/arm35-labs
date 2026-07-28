# M3: 화물 탑재 — check(회귀+신규) / check-sol
PY?=python3

build:
	@mkdir -p out image/usr/bin
	@$(PY) minibake.py | tee .log

check:
	@rm -rf stamps out image .log .log2
	@$(MAKE) -s build
	@a=$$(grep -n "\[lib-a\] compile" .log|cut -d: -f1); b=$$(grep -n "\[lib-b\] compile" .log|cut -d: -f1); \
	 c=$$(grep -n "\[app\] compile" .log|cut -d: -f1); \
	 [ -n "$$a" ]&&[ -n "$$b" ]&&[ -n "$$c" ]&&[ $$a -lt $$b ]&&[ $$b -lt $$c ] \
	 && qemu-aarch64 image/usr/bin/app | grep -q "APP ok" \
	 && echo "  회귀(순서·산출물) PASS" || { echo "  회귀 FAIL"; exit 1; }
	@test -x image/usr/bin/goodbye \
	 && qemu-aarch64 image/usr/bin/goodbye | grep -q "GOODBYE from recipe" \
	 && echo "  신규(goodbye 실행) PASS" || { echo "  신규 FAIL — recipes/goodbye.mb·src/goodbye.c"; exit 1; }
	@$(PY) minibake.py > .log2; n=$$(grep -c "\[skip\]" .log2); \
	 [ $$n -eq 12 ] && echo "  신규(2차 스킵 12/12) PASS" || { echo "  스킵 $$n/12 FAIL"; exit 1; }
	@echo "[판정] M3 PASS -> exit 0"

check-sol:
	@cp sol/goodbye.c src/goodbye.c; cp sol/goodbye.mb recipes/goodbye.mb
	@$(MAKE) -s check; s=$$?; rm -f src/goodbye.c recipes/goodbye.mb; exit $$s

clean:
	rm -rf stamps out image .log .log2 src/goodbye.c recipes/goodbye.mb
