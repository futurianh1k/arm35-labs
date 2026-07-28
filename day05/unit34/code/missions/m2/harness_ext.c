/* M2 확장 하니스 — [회귀] 7단 + [신규] GETCOUNT 3단. 실패수=exit */
#include <stdio.h>
#include <string.h>
#include "sim_kernel.h"
extern int mychar_probe(struct device *);
static int fails=0;
static void chk(const char*n,long got,long want){
    int ok=(got==want);
    printf("  %-38s got=%ld want=%ld %s\n",n,got,want,ok?"PASS":"FAIL");
    if(!ok) fails++;
}
int main(void){
    static struct driver drv={"drv-mychar",{"arm35,mychar",0},mychar_probe};
    static struct device dev={"mychar0","arm35,mychar",0,0};
    driver_register(&drv); device_register(&dev);
    puts("[회귀 — H33 7단]");
    chk("1) 입주",(long)(dev.bound==&drv && the_fops!=0),1);
    if(!the_fops) return fails+9;
    chk("2) open",the_fops->open(),0);
    chk("3) write \"arm35\"(5)",the_fops->write("arm35",5),5);
    char b[64]={0}; long r=the_fops->read(b,sizeof b);
    chk("4) read 회수",(long)(r==5&&!memcmp(b,"arm35",5)),1);
    chk("5) RESET",the_fops->ioctl(0x5201),0);
    memset(b,0,sizeof b);
    chk("6) RESET 후 read=0",the_fops->read(b,sizeof b),0);
    chk("7) 미지 cmd -EINVAL",the_fops->ioctl(0x9999),-EINVAL);
    puts("[신규 — GETCOUNT]");
    long c0=the_fops->ioctl(0x5202);
    chk("8) GETCOUNT 유효(>=0, not -22)",(long)(c0>=0),1);
    the_fops->write("x",1);
    chk("9) write 후 +1",the_fops->ioctl(0x5202),c0+1);
    the_fops->write("yz",2);
    chk("10) write 후 +2",the_fops->ioctl(0x5202),c0+2);
    printf("[결과] 실패 %d건 -> exit %d\n",fails,fails);
    return fails;
}
