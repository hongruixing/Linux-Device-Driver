#include<linux/fs.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/types.h> // for dev_t

MODULE_AUTHOR("Vishal Verma");
MODULE_DESCRIPTION("Registering and un registering the device numbers statically");
MODULE_LICENSE("GPL");
dev_t dev;


static int __init devicestatic(void){
	//statiscally assigning device number
	 dev = MKDEV(242,0);

	//to obtain the device number
	int ret = register_chrdev_region(dev, 1,"devicenumber");
	if(ret <0)
		printk(KERN_ERR"FAILED TO ALLOCATE THE REQUESTED DEVICE NUMBER\n");

	printk(KERN_INFO "REGISTERED MAJOR NUMBER %d\n", MAJOR(dev));
	printk(KERN_INFO "REGISTERED MINOR NUMBER %d\n", MINOR(dev));
return 0;
}


static void __exit exit_devicestatic(void){
	unregister_chrdev_region(dev,1);
	//if(ret<0)
	//	printk(KERN_ERR "FAILED TO UNREGISTER THE DEVICE NUMBERS");
	printk(KERN_INFO "REMOVING MODULE");

}





module_init(devicestatic);
module_exit(exit_devicestatic);
