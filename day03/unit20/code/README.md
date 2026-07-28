# LAB-20 · 잠든 건물에 불 켜기 (Device Tree Overlay, 오프라인)
사전 준비: dtc가 없으면 → sudo apt install device-tree-compiler

- `make dtb`  → `make dump` : base 컴파일·역컴파일로 i2c1의 status="disabled" 채증
- overlay-i2c1.dts의 TODO를 채운다: __overlay__ { status = "okay"; }
- `make dtbo` → `make check`: 병합 검증 → echo $? = 0
심화: i2c1 아래에 가상 센서 자식 노드(compatible·reg 포함)를 덧대고 dump로 확인한다.

함정 코너: base를 -@ 없이 컴파일하면 심볼 테이블이 없어 target=<&i2c1> 해석이
"unresolved" 오류로 실패한다 — 일부러 한 번 겪어 보라.
강사용: overlay-i2c1_sol.dts는 학생 배포본에서 제거한다.
