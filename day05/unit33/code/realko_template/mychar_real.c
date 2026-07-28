/* 실기 절차 주석 — 오늘 미니어처의 물리 번역 지도.
 * 1) module_init/exit + MODULE_LICENSE("GPL")
 * 2) file_operations: .read/.write/.unlocked_ioctl — 오늘 함수명 그대로 이식
 * 3) copy_to_user/copy_from_user 로 *_sim 치환 (반환·-EFAULT 계약 동일)
 * 4) register_chrdev / class_create / device_create 로 /dev/mychar 개통
 * 5) sudo insmod ./mychar_real.ko && dmesg | tail
 * 6) echo hi > /dev/mychar && cat /dev/mychar
 * (전체 코드는 실보드 세션에서 강사와 함께 완성한다 — 논리는 이미 오늘 검증됨) */
