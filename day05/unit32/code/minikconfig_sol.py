#!/usr/bin/env python3
"""minikconfig — menuconfig의 심장(의존 검사·select 견인) 미니어처 (모범답안)"""
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
    """켜진 심볼의 select 대상을 y로 — 전이(연쇄)까지 견인한다."""
    changed = True
    while changed:
        changed = False
        for s, meta in syms.items():
            if cfg.get(s) == "y":
                for t in meta["select"]:
                    if cfg.get(t) != "y":
                        cfg[t] = "y"; changed = True
    return cfg

def check_depends(syms, cfg):
    """켜진 심볼의 모든 전제가 y인지 — 위반 목록[(sym, missing)] 반환."""
    v = []
    for s, meta in syms.items():
        if cfg.get(s) == "y":
            for d in meta["depends"]:
                if cfg.get(d) != "y":
                    v.append((s, d))
    return v

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
