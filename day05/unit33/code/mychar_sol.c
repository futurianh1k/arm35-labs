/* LAB-33 mychar.c — 모범답안 (강사용 — 학생 배포 제외) */
#include "sim_kernel.h"

struct file_operations *the_fops = 0;
int sim_fault_next = 0;

static char kbuf[64];
static long klen = 0;

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
    return n;
}
#define MYCHAR_RESET 0x5201
static long mychar_ioctl(unsigned cmd){
    if (cmd == MYCHAR_RESET){ klen = 0; return 0; }
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
