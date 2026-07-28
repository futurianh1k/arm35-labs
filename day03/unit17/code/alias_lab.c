/* LAB-17 alias_lab: 두 VA, 한 물리 — 번역의 실증 (AArch64 사용자 공간)
 * 판정: A!=B && 내용 일치 && PAGESIZE==4096 -> exit 17
 * 모드:  (없음)=기본 / maps=/proc/self/maps 발췌 / ro=B를 읽기전용으로 -> 쓰기 SIGSEGV 관측 */
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char **argv){
    int fd = memfd_create("alias", 0);           /* 익명 물리 페이지 확보 */
    if (fd < 0) { perror("memfd_create"); return 1; }
    ftruncate(fd, 4096);

    char *A = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    int roB = (argc > 1 && strcmp(argv[1], "ro") == 0);
    char *B = mmap(NULL, 4096, roB ? PROT_READ : PROT_READ|PROT_WRITE,
                   MAP_SHARED, fd, 0);
    if (A == MAP_FAILED || B == MAP_FAILED) { perror("mmap"); return 1; }

    printf("VA A=%p\nVA B=%p  (서로 다른 두 창)\n", (void*)A, (void*)B);
    strcpy(A, "written-via-A");
    printf("read via B: %s   (같은 물리의 증거)\n", B);

    long ps = sysconf(_SC_PAGESIZE);
    printf("PAGESIZE=%ld  (9·9·9·9·12의 마지막 12)\n", ps);

    if (argc > 1 && strcmp(argv[1], "maps") == 0){
        puts("---- /proc/self/maps 중 memfd 매핑 ----");
        FILE *f = fopen("/proc/self/maps", "r");
        char line[256];
        while (f && fgets(line, sizeof line, f))
            if (strstr(line, "memfd")) fputs(line, stdout);
        if (f) fclose(f);
    }
    if (roB){
        puts("[ro] B는 PROT_READ 전용 — 지금 B에 쓰면 SIGSEGV가 정상이다:");
        B[0] = '!';                               /* 여기서 죽는 것이 관측 목표 */
        puts("(이 줄이 보이면 실패)");
    }
    int ok = (A != B) && strcmp(B, "written-via-A") == 0 && ps == 4096;
    printf("[판정] %s\n", ok ? "PASS -> exit 17" : "FAIL");
    return ok ? 17 : 1;
}
