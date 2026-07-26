/* LAB-04 hello.c — 하나의 소스, 세 개의 바이너리
 * 목표: 같은 C 코드가 호스트/AArch64/ARM32 세 표적으로 컴파일되는 과정을 관찰한다.
 * make          : 3종 빌드
 * make run      : QEMU 사용자 모드로 크로스 바이너리 실행
 * make inspect  : file 명령으로 3종 바이너리 정체 확인
 */
#include <stdio.h>
int main(void){
#if defined(__aarch64__)
    const char *arch = "AArch64 (ARMv8-A/9-A, 64-bit)";
#elif defined(__arm__)
    const char *arch = "ARM 32-bit (A32/T32)";
#else
    const char *arch = "Host (x86_64 등)";
#endif
    printf("Hello, ARM 35H! 나는 %s 로 빌드되었다.\n", arch);
    printf("포인터 크기: %zu bytes\n", sizeof(void*));
    return 0;
}
