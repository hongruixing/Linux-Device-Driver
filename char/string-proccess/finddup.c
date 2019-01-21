#include<linux/init.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/types.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>
#include"magic.h"
#define major 242
#define minor 1

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vishal Verma");
MODULE_DESCRIPTION("Single Character Driver");


//=========================================================
struct cdev *my_cdev;
dev_t dev;
char data;
char cache=1;
int flag = 0;

//=========================================================
int finddup_open(struct inode *ip,struct file *fmychar) {
	printk(KERN_ALERT"i am in driver open");
	return 0;
}
//-----------------------------------------------------------------------------------------------------
int finddup_release(struct inode *ip,struct file *fmychar) {
	printk(KERN_ALERT"i am in driver release ");
	return 0;
}


//-------------------------------------------------------------------------------------------------------
static long  finddup_ioctl(struct file *filp,unsigned int cmd, unsigned long arg){
	int retval;
	switch(cmd) {
		case IOC_NOP:
									printk(KERN_ALERT"You have given the NOP command\n");
									return 0;
									break;

		case IOC_RD:
									if(data == NULL) {
										return -EINVAL;
									}
									if(flag) {
										data = '@';
										flag = 0;
										printk(KERN_ALERT"Reading");
									}
									retval=put_user(data,(char *)arg);
									printk(KERN_ALERT"Reading Data.........%c\n",data);
									break;

		case IOC_WR:
									retval=	get_user(data,(char *)arg);
									if(cache == data) {
										flag = 1;
										printk(KERN_ALERT"cache == data");
									}
									else {
										cache = data;
									}
									printk(KERN_ALERT"Writing Data..........%c\n",data);
									break;
		default:
									return -ENOTTY;
  }

	return retval;
}
