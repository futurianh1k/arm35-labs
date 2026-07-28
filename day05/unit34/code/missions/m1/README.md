# M1 · 이중 소스 IRQ (30점) — 명세
- 요구: 타이머 틱(기존)과 UART 수신을 "한 핸들러"가 판별 처리. 수신 문자마다 K<n> 표시.
- 판정: printf 'kk' 주입 → 출력에 "K2" 와 "IRQ x5 OK" 둘 다(회귀+신규).
- TODO 3곳(A: IMSC RXIM / B: 핸들러 bit12 분기 — 원인 제거=DR 읽기 / C: VIC bit12 개방).
- 함정: UART는 W1C가 아니다 — ICR을 두드려도 깃발은 DR을 읽어야 내려간다(24차시 소비 규약).
- 세 문 진단: 장치 IMSC → VIC EN(bit12) → CPSR I.
