#include<linux/fs.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/types.h> // for dev_t
#include<linux/cdev.h> // cdev struct
#include<linux/uaccess.h>
#include<linux/ctype.h>


#define major 242
#define minor 0
#define DEVICENAME "uppercase"
#define BUFFERSIZE 21


MODULE_AUTHOR("Vishal Verma");
MODULE_DESCRIPTION("Registering and un registering the device numbers statically");
MODULE_LICENSE("GPL");

char kernelbuffer[BUFFERSIZE];
static int actual_count=0;
dev_t  dev;
//struct cdev initailization;
struct cdev *my_cdev;


//open
int open_uppercase(struct inode* inodeptr , struct file* filptr){

	unsigned int num;
	num = iminor(inodeptr);
	printk(KERN_ALERT"I AM IN OPEN %d \n",num );


	printk(KERN_INFO"Device opened Successfully");

	return 0;
}


//read
ssize_t read_uppercase(struct file* filptr, char __user *buffer, size_t count, loff_t *offset){
	int result;

	result = copy_to_user(buffer,kernelbuffer,count);
	if(result>=0){
		printk(KERN_INFO"Return value of copy to user  is %d \n",result);
		printk(KERN_INFO"successfully data sent to user space %s of size %d\n ",kernelbuffer,(int)count);
		return count;
	}
	else{
		printk(KERN_ERR"failed to read................");
		return -EFAULT;
	}
}


//write
ssize_t write_uppercase(struct file* filptr, const char __user *buffer, size_t count, loff_t *offset){
	int result,i,len;
	memset(kernelbuffer,0,BUFFERSIZE);

	result = copy_from_user(kernelbuffer, buffer,(int)count);

	if(result>=0){
		printk(KERN_INFO"Return value of copy from user  is %d \n",result);
		printk(KERN_INFO"data from  user space is %s of size %d \n",kernelbuffer,(int)count);
		i=0;
		len = (int)count;

		while(i<len){
			if(isspace(kernelbuffer[i])){
				printk(KERN_INFO"I AM HERE");
			}
			else{
				kernelbuffer[i]= kernelbuffer[i]-32;
				//printk(KERN_INFO"%c",kernelbuffer[i]);
			}
			i++;
		}
		printk(KERN_INFO"%s",kernelbuffer);
		actual_count = count-result;
		return count;
	}
	else{
		printk(KERN_ERR"failed to read");
		return -EFAULT;
	}
}

//release
int release_uppercase(struct inode* inodeptr, struct file* filptr){
	printk(KERN_INFO "Device Closed Successfully" );

	return 0;
}

// file operations to give functionality to the driver
static struct file_operations fops = {
	.open = open_uppercase,
	.release = release_uppercase,
	.read = read_uppercase,
	.write = write_uppercase,
};


// regstration of the charater device
static int __init uppercase(void){

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

// unregistering the charcter driver
static void __exit exit_uppercase(void){
	cdev_del(my_cdev);
	printk(KERN_INFO"Cdev structure deleted from the kernel");
	printk(KERN_INFO "REMOVING MODULE");

}

module_init(uppercase);
module_exit(exit_uppercase);
