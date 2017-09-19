/*
*FileName: helloDriver.c
*Author: Vishal Verma
*Purpose: This program is a bsic implementation of the device driver or linux loadable kernel module  
*         
*/
#include<linux/init.h>
#include<linux/module.h>
#include<linux/sched.h>

int initHello(void){
printk("Hello, I am loaded in the kernel");
return 0;
}

module_init(initHello);
void exitHello(void){
printk("Bye, I am leaving the kernel");
}

module_exit(exitHello);
MODULE_LICENSE("GPL");


