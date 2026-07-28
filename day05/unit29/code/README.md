# LAB-29 · 엔진의 심장 이식 — minibake
- TODO 2개: toposort(의존 위상정렬)·stamp_fresh(도장 계약: 존재 + 입력이 더 새롭지 않음)
- `make check` 3부: ①의존 순서(lib-a→lib-b→app compile 등장 순서) ②산출물·qemu-aarch64 실행
  ③2차 실행 전 태스크 [skip] 9/9
- 골격 임시 동작: 글롭 순서(app 먼저) + 항상 재실행 → 1·3부가 실패하는 출발선이 정상이다.
- 심화: SRC를 touch 후 재실행 — 해당 레시피만 재빌드(도장 계약의 입력 조항) 관측.
강사용: minibake_sol.py는 학생 배포본에서 제거한다. 표준 라이브러리만 사용.
