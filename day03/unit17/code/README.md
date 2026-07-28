# LAB-17 · 두 VA, 한 물리
- `make run` : A/B 두 주소·동일 내용·PAGESIZE=4096 → exit 17
- `make maps`: /proc/self/maps에서 memfd 매핑 2줄 확인
- `make ro`  : B를 PROT_READ로 매핑 후 쓰기 → SIGSEGV(139)가 정상 관측. "권한은 매핑(엔트리) 단위"의 증거.
memfd_create가 없는 구형 환경은 shm_open("/alias17",O_CREAT|O_RDWR,0600)+shm_unlink로 대체한다.
