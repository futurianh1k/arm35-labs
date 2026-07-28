/* sim_kernel.h — 커널 API의 논리 등가 축약층 (경계표: 헤더 하단 주석)
 * 등가: fops 배선·chrdev 등록·경계 복사 계약(반환=못 옮긴 수, 실패=-EFAULT)
 * 축약: 동시성·참조계수·실 MMIO(ioremap)·VFS 실배선 — 실기 승급은 realko_template */
#ifndef SIM_KERNEL_H
#define SIM_KERNEL_H
#include <stdio.h>
#include <string.h>
#include "sim.h"                      /* 28차시 엔진의 device/driver */

#define EFAULT 14
#define EINVAL 22

struct file_operations {
    int  (*open)(void);
    long (*read)(char *ubuf, long n);
    long (*write)(const char *ubuf, long n);
    long (*ioctl)(unsigned cmd);
};

extern struct file_operations *the_fops;     /* 개통된 전화선(단일 minor 축약) */
static inline int register_chrdev_sim(const char *name, struct file_operations *f){
    printf("[sim] chrdev \"%s\" 개통 (fops 접수)\n", name);
    the_fops = f; return 0;
}

/* 경계 통로 축약 — fault 주입 스위치로 실패 경로도 검증 가능 */
extern int sim_fault_next;                   /* 1이면 다음 복사에서 3바이트 실패 흉내 */
static inline long copy_to_user_sim(char *u, const char *k, long n){
    if (sim_fault_next){ sim_fault_next=0; return 3; }
    memcpy(u, k, n); return 0;
}
static inline long copy_from_user_sim(char *k, const char *u, long n){
    if (sim_fault_next){ sim_fault_next=0; return 3; }
    memcpy(k, u, n); return 0;
}
#define dev_info(fmt, ...) printf("[mychar] " fmt, ##__VA_ARGS__)
#endif
