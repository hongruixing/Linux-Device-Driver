
// file operations to give functionality to the driver
struct file_operations uppercase = {
	.open = open_uppercase,
	.release = release_uppercase,
	.read = read_uppercase,
	.write = write_uppercase,
};

static struct file_operations nextchar = {
	.open = open_nextchar,
	.release = release_nextchar,
	.read = read_nextchar,
	.write = write_nextchar,
};


struct file_operations finddup={
	.unlocked_ioctl=finddup_ioctl,
	.open=finddup_open,
	.release=finddup_release,
};


int major;

int __init string_process_init(void){
  major = register_chrdev(0, UPPERCASE, &uppercase);
  major = register_chrdev(0, FINDDUP, &finddup);
  major = register_chrdev(0, NEXTCHAR, &nextchar);

	if (major < 0) {
	  printk(KERN_ALERT "Registering char device link_list failed with %d\n", major);
	  return major;
  }

	printk(KERN_INFO " link_list major number %d ", major);
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major);

	return SUCCESS;
}

void __exit string_process_exit(void){
	 unregister_chrdev(major, DEVICE_NAME);
}

module_init(string_process_init);
module_exit(string_process_exit);
