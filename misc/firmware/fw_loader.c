/*
*FileName: helloDriver.c
*Author: Vishal Verma
*Purpose: This program is about loading a firmware from /lib/firmware directory and printing the information
* 	  regarding the firmware.
*         
*/
#include<linux/init.h>
#include<linux/module.h>
#include<linux/device.h>
#include<linux/firmware.h>
#define FW_FILE    "a300_pfp.fw"   //"  iwlwifi-8000C-13.ucode" //"ath3k-1.fw"
const struct firmware *fw;

void release_driver(struct device *dd){
 printk(KERN_INFO "Device  released\n");
}

 struct device dd = {
	.release= release_driver,
};

 int init_device(void){
	//register a device;
	dev_set_name(&dd,"firmware_loader");
	device_register(&dd);

	printk(KERN_INFO "Device for firmware created\n");

	//registering a firmware and checking if loaded
	if(request_firmware(&fw,FW_FILE,&dd)){
	printk(KERN_ERR "firmware failed to load\n");
	device_unregister(&dd);	
	return -1;
	}
 
printk(KERN_INFO "Device for firmware created\t Firmware size = %d \n Firmware Content= %s\n",(int)fw->size,fw->data);
return 0;
}

 void  exit_device(void)
{
	release_firmware(fw);
	device_unregister(&dd);
	printk(KERN_INFO "Device   unregistered and firmware released\n");


}

module_exit(exit_device);
module_init(init_device);
MODULE_LICENSE("GPL");


