/* LAB-33 mychar.c — 골격: TODO 4개(3문 + 입주식). open은 패턴 제공. */
#include "sim_kernel.h"

struct file_operations *the_fops = 0;
int sim_fault_next = 0;

static char kbuf[64];
static long klen = 0;

static int mychar_open(void){ dev_info("open\n"); return 0; }

static long mychar_read(char *ubuf, long n){
    /* TODO 1: klen 한도(n과 비교), copy_to_user_sim, 실패 시 -EFAULT,
       성공 시 옮긴 바이트 수 반환(축약 관례). */
    (void)ubuf; (void)n; return -1;
}
static long mychar_write(const char *ubuf, long n){
    /* TODO 2: 버퍼 한도(sizeof kbuf) 검사, copy_from_user_sim,
       실패 -EFAULT, 성공 시 klen 갱신 + 옮긴 수 반환. */
    (void)ubuf; (void)n; return -1;
}
#define MYCHAR_RESET 0x5201
static long mychar_ioctl(unsigned cmd){
    /* TODO 3: RESET -> klen=0, 0 반환. 미지의 cmd -> -EINVAL. */
    (void)cmd; return -1;
}
static struct file_operations fops = {
    .open = mychar_open, .read = mychar_read,
    .write = mychar_write, .ioctl = mychar_ioctl,
};

int mychar_probe(struct device *d){
    /* TODO 4: 입주식 — dev_info로 "probe: %s\n" 보고 + chrdev 개통(register_chrdev_sim). */
    (void)d; return -1;
}
