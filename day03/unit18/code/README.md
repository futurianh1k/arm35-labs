# LAB-18 · 가상 도시의 지도 복원 (QEMU virt Device Tree)
사전 준비: dtc가 없으면 → sudo apt install device-tree-compiler

- `make dtb`  : 게스트 부팅 없이 배선 명세(DTB)만 덤프
- `make dts`  : dtc로 역컴파일 — 전체를 한 번 스크롤해 도시 규모를 감각한다
- 미션        : uart(pl011)·intc(GIC)·rtc(pl031)·virtio 4구역의 reg를 찾아
                수기 지도 표(장치|시작|크기|IRQ)를 만든다
- `make check`: 4구역 자동 판정 → echo $? = 0 (수기 지도와 대조)
심화: memory@40000000 노드에서 DRAM 시작을 확인하고 그 의미를 한 줄로 해석한다.
