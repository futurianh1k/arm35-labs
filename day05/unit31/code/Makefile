# LAB-31: 싣고 깨우기 — check / check-sol
PY?=python3
UNIT?=hello.service

check:                     ## [1부] 크로스 빌드·실행 [2부] 유닛 검증(폴백+analyze)
	@rm -rf stamps out image; mkdir -p out image/usr/bin
	@$(PY) minibake.py >/dev/null 2>&1 || true
	@test -x image/usr/bin/hello \
	  && qemu-aarch64 image/usr/bin/hello | tee .run | grep -q "HELLO from recipe" \
	  && echo "[1부] 레시피 빌드·실행 PASS ($$(cat .run))" \
	  || { echo "[1부] FAIL — 레시피 TODO를 확인하라"; exit 1; }
	@$(PY) unit_check.py $(UNIT) && echo "[2부a] 폴백 검증 PASS" || { echo "[2부a] FAIL"; exit 1; }
	@if command -v systemd-analyze >/dev/null; then \
	  mkdir -p .verify && sed "s|^ExecStart=.*|ExecStart=$(CURDIR)/image/usr/bin/hello|" $(UNIT) > .verify/hello.service; \
	  if systemd-analyze verify .verify/hello.service 2> .an.log && [ ! -s .an.log ]; then \
	    echo "[2부b] systemd-analyze verify PASS"; \
	  else echo "[2부b] systemd-analyze 지적:"; sed 's/^/    /' .an.log; exit 1; fi; \
	else echo "[2부b] systemd-analyze 미설치 — 폴백만 적용"; fi
	@echo "[판정] PASS -> exit 0"

check-sol:                 ## 강사용: sol을 임시 치환해 표준 check 재사용
	@cp recipes/hello.mb .bak.mb
	@cp sol/hello.mb recipes/hello.mb
	@$(MAKE) -s check UNIT=sol/hello.service; s=$$?; \
	 mv .bak.mb recipes/hello.mb; exit $$s

clean:
	rm -rf stamps out image .run .verify .an.log .bak.mb
