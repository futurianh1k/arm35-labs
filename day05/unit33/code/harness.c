/* LAB-33 하니스 — 7단 시나리오. 실패 수 = exit */
#include <stdio.h>
#include <string.h>
#include "sim_kernel.h"

extern int mychar_probe(struct device *);
static int fails = 0;
static void chk(const char *n, long got, long want){
    int ok = (got == want);
    printf("  %-38s got=%ld want=%ld %s\n", n, got, want, ok?"PASS":"FAIL");
    if (!ok) fails++;
}
int main(void){
    puts("[LAB-33] 시민 탄생식 — 7단");
    static struct driver drv = {"drv-mychar", {"arm35,mychar", 0}, mychar_probe};
    static struct device dev = {"mychar0", "arm35,mychar", 0, 0};
    driver_register(&drv);
    device_register(&dev);
    chk("1) 입주(매칭→probe→개통)", (long)(dev.bound == &drv && the_fops != 0), 1);
    if (!the_fops){ puts("[중단] fops 미개통"); return fails + 6; }
    chk("2) open", the_fops->open(), 0);
    chk("3) write \"arm35\"(5)", the_fops->write("arm35", 5), 5);
    char buf[64] = {0};
    long r = the_fops->read(buf, sizeof buf);
    chk("4) read 회수(5바이트·내용 일치)",
        (long)(r == 5 && memcmp(buf, "arm35", 5) == 0), 1);
    chk("5) ioctl RESET", the_fops->ioctl(0x5201), 0);
    memset(buf, 0, sizeof buf);
    chk("6) RESET 후 read = 0", the_fops->read(buf, sizeof buf), 0);
    chk("7) 미지 cmd -> -EINVAL", the_fops->ioctl(0x9999), -EINVAL);
    printf("[결과] 실패 %d건 -> exit %d %s\n", fails, fails, fails?"":"(시민 탄생)");
    return fails;
}
