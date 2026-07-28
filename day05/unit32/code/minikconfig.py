#!/usr/bin/env python3
"""minikconfig — menuconfig의 심장(의존 검사·select 견인) 미니어처 — LAB-32 골격: TODO 두 심장을 이식하라"""
import re, sys

def load_kconfig(path):
    syms, cur = {}, None
    for raw in open(path, encoding="utf-8"):
        line = raw.split("#")[0].rstrip()
        m = re.match(r"config\s+(\w+)", line)
        if m:
            cur = m.group(1); syms[cur] = {"depends": [], "select": [], "default": "n"}
        elif cur:
            m = re.match(r"\s+depends on\s+(\w+)", line)
            if m: syms[cur]["depends"].append(m.group(1))
            m = re.match(r"\s+select\s+(\w+)", line)
            if m: syms[cur]["select"].append(m.group(1))
            m = re.match(r"\s+default\s+(\w+)", line)
            if m: syms[cur]["default"] = m.group(1)
    return syms

def load_config(path):
    cfg = {}
    for raw in open(path, encoding="utf-8"):
        m = re.match(r"CONFIG_(\w+)=(\w+)", raw.strip())
        if m: cfg[m.group(1)] = m.group(2)
    return cfg

def apply_defaults(syms, cfg):
    for s, meta in syms.items():
        cfg.setdefault(s, meta["default"])
    return cfg

def apply_select(syms, cfg):
    """TODO 2 — select 견인: 켜진 심볼의 select 대상을 y로(전이 포함).
    (골격: 아무 것도 하지 않음 — good.config의 TTY_CORE가 켜지지 않는다)"""
    return cfg

def check_depends(syms, cfg):
    """TODO 1 — 의존 검사: 켜진 심볼의 depends 전수 검사, 위반 [(sym, missing)].
    (골격: 항상 빈 목록 — bad*.config의 위반을 놓친다)"""
    return []

def main():
    syms = load_kconfig(sys.argv[1])
    cfg = apply_defaults(syms, load_config(sys.argv[2]))
    cfg = apply_select(syms, cfg)
    viol = check_depends(syms, cfg)
    for s, d in viol:
        print(f"  위반: {s}=y 인데 전제 {d} 가 y 아님")
    print(f"[minikconfig] 위반 {len(viol)}건  (TTY_CORE={cfg.get('TTY_CORE')})")
    sys.exit(len(viol))

if __name__ == "__main__": main()
