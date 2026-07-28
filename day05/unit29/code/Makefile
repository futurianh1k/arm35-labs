# LAB-29: minibake — check(골격) / check-sol(강사)
PY?=python3
BAKE?=minibake.py

build:
	@mkdir -p image/usr/bin out
	@$(PY) $(BAKE) | tee .log

check:                      ## 3부: 의존 순서 / 산출물·실행 / 2차 스킵
	@$(MAKE) -s clean-state build BAKE=$(BAKE)
	@a=$$(grep -n "\[lib-a\] compile" .log | cut -d: -f1); \
	 b=$$(grep -n "\[lib-b\] compile" .log | cut -d: -f1); \
	 c=$$(grep -n "\[app\] compile"   .log | cut -d: -f1); \
	 [ -n "$$a" ] && [ -n "$$b" ] && [ -n "$$c" ] && [ $$a -lt $$b ] && [ $$b -lt $$c ] \
	   && echo "[1부] 의존 순서 PASS" || { echo "[1부] 의존 순서 FAIL (a=$$a b=$$b c=$$c)"; exit 1; }
	@test -x image/usr/bin/app && qemu-aarch64 image/usr/bin/app | grep -q "APP ok" \
	   && echo "[2부] 산출물·실행 PASS" || { echo "[2부] FAIL"; exit 1; }
	@$(PY) $(BAKE) | tee .log2 >/dev/null; \
	 n=$$(grep -c "\[skip\]" .log2); \
	 [ $$n -eq 9 ] && echo "[3부] 2차 스킵(9/9) PASS" || { echo "[3부] 스킵 $$n/9 FAIL"; exit 1; }
	@echo "[판정] PASS -> exit 0"

check-sol:
	@$(MAKE) -s check BAKE=minibake_sol.py

clean-state:
	@rm -rf stamps out image .log .log2
clean: clean-state
