#!/usr/bin/env python3
"""minibake — BitBake 심장 2개(DAG·스탬프)의 교육용 미니어처 (모범답안, 강사용)"""
import os, re, subprocess, sys, glob

CC = os.environ.get("CC", "aarch64-linux-gnu-gcc")
TASKS = ["fetch", "compile", "install"]

def parse(path):
    r = {"DEPENDS": ""}
    for line in open(path, encoding="utf-8"):
        line = line.split("#")[0].strip()
        m = re.match(r"(\w+)\s*=\s*(.*)", line)
        if m: r[m.group(1)] = m.group(2).strip()
    base = path[:-3] + ".mb.append"          # bbappend 축약: 있으면 덮어쓰기 병합
    if os.path.exists(base):
        for line in open(base, encoding="utf-8"):
            line = line.split("#")[0].strip()
            m = re.match(r"(\w+)\s*=\s*(.*)", line)
            if m: r[m.group(1)] = m.group(2).strip()
    return r

def load_all():
    rs = {}
    for p in sorted(glob.glob("recipes/*.mb")):
        r = parse(p); rs[r["NAME"]] = r
    return rs

def toposort(rs):
    """의존(DEPENDS)을 존중하는 위상정렬 — 사이클이면 오류."""
    order, done, seen = [], set(), set()
    def visit(n):
        if n in done: return
        if n in seen: sys.exit(f"[minibake] 순환 의존: {n}")
        seen.add(n)
        for d in rs[n]["DEPENDS"].split():
            visit(d)
        seen.discard(n); done.add(n); order.append(n)
    for n in sorted(rs): visit(n)
    return order

def stamp_path(name, task): return f"stamps/{name}.{task}"

def stamp_fresh(r, name, task):
    """도장 계약: 도장이 있고, 입력(SRC·레시피)이 도장보다 오래됐으면 신선."""
    sp = stamp_path(name, task)
    if not os.path.exists(sp): return False
    st = os.path.getmtime(sp)
    inputs = [f"recipes/{name}.mb", r.get("SRC", "")]
    ap = f"recipes/{name}.mb.append"
    if os.path.exists(ap): inputs.append(ap)
    return all((not p) or (os.path.getmtime(p) <= st) for p in inputs if p == "" or os.path.exists(p))

def run_task(r, name, task):
    if stamp_fresh(r, name, task):
        print(f"[{name}] {task} [skip]"); return
    print(f"[{name}] {task}")
    if task == "fetch":
        if not os.path.exists(r["SRC"]): sys.exit(f"[minibake] SRC 없음: {r['SRC']}")
    elif task == "compile":
        cmd = r["COMPILE"].replace("$CC", CC).replace("$SRC", r["SRC"])
        subprocess.run(cmd, shell=True, check=True)
    elif task == "install":
        os.makedirs(os.path.dirname(r["INSTALL"].split()[-1]) or ".", exist_ok=True)
        subprocess.run(r["INSTALL"], shell=True, check=True)
    os.makedirs("stamps", exist_ok=True)
    open(stamp_path(name, task), "w").close()

def main():
    rs = load_all()
    for name in toposort(rs):
        os.makedirs("out", exist_ok=True)
        for t in TASKS: run_task(rs[name], name, t)
    print("[minibake] BUILD DONE")

if __name__ == "__main__": main()
