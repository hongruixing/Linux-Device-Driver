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
#define BUFFSIZE 100
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vishal Verma");
MODULE_DESCRIPTION("Single Character Driver");

char kernelbuff[BUFFSIZE];
//=========================================================
struct cdev *my_cdev;
dev_t dev;
char data;
char cache=1;
int flag = 0;
//=========================================================
int datto_open(struct inode *ip,struct file *fmychar)
{
	printk(KERN_ALERT"i am in driver open");
	return 0;
}
//-----------------------------------------------------------------------------------------------------
int datto_release(struct inode *ip,struct file *fmychar)
{
	printk(KERN_ALERT"i am in driver release ");
	return 0;
}

//----------------------------------------------------------------------------------------------------

ssize_t datto_read(struct file* filptr, char __user *buffer, size_t count, loff_t *offset){
int result;
	
 result = copy_to_user(buffer,kernelbuff,count);
    if(result>=0)
	{
	printk(KERN_INFO"Return value of copy to user  is %d \n",result);
	//printk(KERN_INFO"successfully data sent to user space %s of size %d\n ",kernelbuffer,(int)count);
	return count;
	}
	else
	{
	printk(KERN_ERR"failed to read................");
	return -EFAULT;
	}
}

//-------------------------------------------------------------------------------------------------------
static long  datto_ioctl(struct file *filp,unsigned int cmd, unsigned long arg)
{
int retval,i ;
switch(cmd)
{


case IOC_WR:
	retval=	get_user(data,(char *)arg);
	printk(KERN_ALERT"Writing Data..........%c\n",data);
	i= 0;
	while(i< BUFFSIZE){
	kernelbuff[i] = data;
	i++;}
	break;
default:
	return -ENOTTY;
}

return retval;

}


struct file_operations fops={
	.owner=THIS_MODULE,
	.read=datto_read,
	.unlocked_ioctl=datto_ioctl,
	.open=datto_open,
	.release=datto_release,
};




//================================================================================================
static int __init datto_init(void)
{
	int ret;
	dev = MKDEV(major,minor);
	
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops; 
	my_cdev->owner = THIS_MODULE;

	cdev_init(my_cdev, &fops);
	
	ret =cdev_add(my_cdev,dev,1);


	if(ret<0)
		printk(KERN_ERR"FAILED TO register the char device\n");

	printk(KERN_INFO"Character deivce successfully registered in the kernel");
	printk(KERN_INFO "REGISTERED MAJOR NUMBER %d\n", MAJOR(dev));
	printk(KERN_INFO "REGISTERED MINOR NUMBER %d\n",MINOR(dev));

	return 0;
}
//------------------------------------------------------------------------------------------------
static void  __exit datto_exit(void)
{

	cdev_del(my_cdev);
	printk(KERN_INFO"Cdev structure deleted from the kernel");
	printk(KERN_INFO "REMOVING MODULE");		
          
}
//--------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
module_init(datto_init);
module_exit(datto_exit);
//-------------------------------------------------------------------------------------------------------

