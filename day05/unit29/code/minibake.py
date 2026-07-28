#!/usr/bin/env python3
"""minibake — LAB-29 골격: TODO 두 심장(toposort·stamp)을 이식하라"""
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
    """TODO 1 — 위상정렬: DEPENDS의 대상들이 먼저 오도록 순서를 계산하라.
    힌트: 방문(DFS) 중 표식으로 순환도 감지할 수 있다.
    (골격 임시 동작: 이름 글롭 순서 그대로 — 의존을 무시하므로 check 1부가 잡는다)"""
    return sorted(rs)

def stamp_path(name, task): return f"stamps/{name}.{task}"

def stamp_fresh(r, name, task):
    """TODO 2 — 도장 계약: 도장이 존재하고 입력(SRC·레시피·append)이
    도장보다 새롭지 않으면 True(스킵). (골격 임시 동작: 항상 재실행)"""
    return False

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
