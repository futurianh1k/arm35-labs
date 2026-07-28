#!/usr/bin/env python3
"""폴백 검증기 — 3부작 필수 키 + ExecStart 절대경로. (systemd-analyze 보조)"""
import sys, re
p = sys.argv[1]; txt = open(p, encoding="utf-8").read()
errs = []
for sec in ("[Unit]", "[Service]", "[Install]"):
    if sec not in txt: errs.append(f"섹션 누락: {sec}")
def key(sec, k):
    m = re.search(rf"\[{sec}\](.*?)(\n\[|\Z)", txt, re.S)
    return re.search(rf"^{k}\s*=\s*(\S.*)$", m.group(1), re.M) if m else None
if not key("Unit", "Description") or "TODO" in (key("Unit","Description").group(1) if key("Unit","Description") else "TODO"):
    errs.append("Description 미기재")
es = key("Service", "ExecStart")
if not es: errs.append("ExecStart 누락")
elif not es.group(1).startswith("/"): errs.append(f"ExecStart 절대경로 위반: {es.group(1)}")
if not key("Install", "WantedBy"): errs.append("WantedBy 누락")
for e in errs: print("  UNIT:", e)
sys.exit(len(errs))
