# LAB-32 · 검증기 이식과 서명 의식
- TODO: minikconfig.py 의 check_depends(위반 [(sym,missing)] + 진단 출력은 main 제공)와
        apply_select(전이 포함 견인) / overlays/h32-marker.dts 의 마커 속성 한 줄
- `make check` 2부: [1부] good/bad1/bad2 4케이스(위반 검출·진단 문구·select 견인)
                    [2부] 실물 RPi4 DTB에 fdtoverlay 병합 → arm35,marker="h32" grep
- 골격 출발선: good은 TTY_CORE 미견인, bad*는 위반 미검출 → [1부] FAIL이 정상.
실트리 항해(menuconfig / savedefconfig) 명령 시트는 T-14 캐시 환경 실습 안내를 따른다.
강사용: minikconfig_sol.py, sol/ 제거.
