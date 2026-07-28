/* M2 시작점 — H33 완성본(회귀 대상) 모범답안 (강사용)
 * 규약: 새 ioctl MYCHAR_GETCOUNT 0x5202 · 카운터는 write "성공" 시에만 증가
 * 회귀: 기존 7단(RESET 의미·-EINVAL 포함) 전부 유지 — 확장 하니스가 함께 판정한다 */
#include "sim_kernel.h"

struct file_operations *the_fops = 0;
int sim_fault_next = 0;

static char kbuf[64];
static long klen = 0;
static long write_count = 0;      /* TODO 1: write 성공 시 ++ (아래 write에서) */

static int mychar_open(void){ dev_info("open\n"); return 0; }

static long mychar_read(char *ubuf, long n){
    long m = (n < klen) ? n : klen;
    if (copy_to_user_sim(ubuf, kbuf, m)) return -EFAULT;
    return m;
}
static long mychar_write(const char *ubuf, long n){
    if (n > (long)sizeof(kbuf)) n = sizeof(kbuf);
    if (copy_from_user_sim(kbuf, ubuf, n)) return -EFAULT;
    klen = n;
    write_count++;
    return n;
}
#define MYCHAR_RESET    0x5201
#define MYCHAR_GETCOUNT 0x5202   /* 신규 명령 — 값은 반환값으로 직접(축약 규약) */
static long mychar_ioctl(unsigned cmd){
    if (cmd == MYCHAR_RESET){ klen = 0; return 0; }
    if (cmd == MYCHAR_GETCOUNT) return write_count;
    return -EINVAL;
}
static struct file_operations fops = {
    .open = mychar_open, .read = mychar_read,
    .write = mychar_write, .ioctl = mychar_ioctl,
};

int mychar_probe(struct device *d){
    dev_info("probe: %s\n", d->name);
    return register_chrdev_sim("mychar", &fops);
}
