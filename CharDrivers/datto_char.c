/////////////////////////////////////////////////////////////////////
//  datto_char.c - Single Character Driver which accepts the a     //
//                 single character and outputs the character the  //
//		   buffer length times                             //
//  version - 1.0                                                  //
//  Author - Vishal Verma , Syracuse University, vvverma@syr.edu   //
/////////////////////////////////////////////////////////////////////





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
#define BUFFSIZE 128

//==============Function prototype==============================================
int datto_open(struct inode*,struct file*);
int datto_release(struct inode*,struct file*);
ssize_t datto_read(struct file* filptr, char __user *buffer,
				 size_t count, loff_t *offset);
static long  datto_ioctl(struct file *filp,unsigned int cmd,
					 unsigned long arg);
void copy_to_buffer(char tchar);
static int __init datto_init(void);
static void  __exit datto_exit(void);
				 
//==============Required Structures for character driver implementation=========

struct cdev *my_cdev;

struct file_operations fops={
	.owner=THIS_MODULE,
	.read=datto_read,
	.unlocked_ioctl=datto_ioctl,
	.open=datto_open,
	.release=datto_release,
};

//=====================Global Variable==========================================

char kernelbuff[BUFFSIZE];
dev_t dev;
char data = -1; // -1 is the senitel value




//=============== Functionalities of Character Driver ========================== 

//-------------Called for open system call--------------------------------------
int datto_open(struct inode *ip,struct file *filptr){
	printk(KERN_INFO"Character Driver is open");
	return 0;
}

//-------------Called for close system call-------------------------------------
int datto_release(struct inode *ip,struct file *filptr){
	printk(KERN_ALERT"Driver released");
	return 0;
}




//-------------Called for read system call------------------------------------
ssize_t datto_read(struct file* filptr, char __user *buffer,
				 size_t count, loff_t *offset){
				 
				
int result;
//check for content initialized in data
 if (data == -1)
	return -EINVAL;
	
 result = copy_to_user(buffer,kernelbuff,count);
    if(result>=0){
	printk(KERN_INFO"Return value of copy to user  is %d \n",result);
	printk(KERN_INFO"successfully data sent to user space %c of size %d\n",
							data,(int)count-result);
	return result;
	}
	else{
	printk(KERN_ERR"failed to copy data to userspace");
	return -EFAULT;
	}
}


//-------------Function to copy data to the kernel buffer-----------------------
void copy_to_buffer(char tchar){
	int i =0;

	memset(kernelbuff,0,BUFFSIZE);
	while(i<BUFFSIZE){
		kernelbuff[i] = tchar;
		i++;
	}
	printk(KERN_INFO "Copy Successful");
}

//----------------Call for ioctl system call ----------------------------------
static long  datto_ioctl(struct file *filp,unsigned int cmd,
					 unsigned long arg){
int retval;

switch(cmd){

case IOC_WR:
	retval=get_user(data,(char *)arg);
	printk(KERN_ALERT"Data from the userspace%c\n",data);
	copy_to_buffer(data);
	break;	

default:
	return -ENOTTY;
}

return retval;
}


//------------------------Calls when module is loaded into the kernel-----------
static int __init datto_init(void){

	dev = MKDEV(major,minor); //Allocating Device number
	my_cdev = cdev_alloc(); //Registering character driver
	my_cdev->ops = &fops; 
	my_cdev->owner = THIS_MODULE;

	cdev_init(my_cdev, &fops);//Initializing driver
	
	 // notifying the kernel
	if(cdev_add(my_cdev,dev,1));
		printk(KERN_ERR"Failed to register the char device\n");

	printk(KERN_INFO"Character deivce successfully registered in the kernel");
	printk(KERN_INFO "REGISTERED MAJOR NUMBER %d\n", MAJOR(dev));
	printk(KERN_INFO "REGISTERED MINOR NUMBER %d\n",MINOR(dev));

	return 0;
}
//------------Calls when module is unloaded from kernel;------------------------
static void  __exit datto_exit(void){

	cdev_del(my_cdev); //free up cdev structure
	printk(KERN_INFO"Cdev structure deleted from the kernel");
	printk(KERN_INFO "REMOVING THIS MODULE");		
          
}



//-----------Macro to init and exit module--------------------------------------
module_init(datto_init);
module_exit(datto_exit);

//====================MODULE-LICENSE,AUTHOR,DESCRIPTION=========================
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vishal Verma");
MODULE_DESCRIPTION("Single Character Driver");

