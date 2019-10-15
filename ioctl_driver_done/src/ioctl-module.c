#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include <ioctl_cmds.h>

static int Device_Open = 0;
static char Message[BUF_LEN];
static char *Message_Ptr;


static int device_open(struct inode *inode, struct file *file)
{
	if (Device_Open)
		return -EBUSY;

	Device_Open++;

	Message_Ptr = Message;
	try_module_get(THIS_MODULE);
	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--;

	module_put(THIS_MODULE);
	return SUCCESS;
}

static ssize_t device_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset)
{
	int bytes_read = 0;

	if (*Message_Ptr == 0)
		return 0;

	while (length && *Message_Ptr) {
		put_user(*(Message_Ptr++), buffer++);
		--length;
		++bytes_read;
	}

	return bytes_read;
}

static ssize_t device_write(struct file *filp, const char __user * buffer, size_t length, loff_t * offset)
{
	int i;

	for (i = 0; i < length && i < BUF_LEN; i++)
		get_user(Message[i], buffer + i);

	Message_Ptr = Message;

	return i;
}

long int ioctl_handler(struct file *filp, unsigned int ioctl_num, unsigned long ioctl_param)
{
	int i;
	char *temp;
	char ch;

	switch (ioctl_num) {
	case IOCTL_SET_MSG:
		temp = (char *)ioctl_param;
		if (temp)
			printk(KERN_INFO "\n\nOOOOOOOOOOOOOOO\n\n");

		get_user(ch, temp);
		for (i = 0; ch && i < BUF_LEN; i++, temp++)
			get_user(ch, temp);

		device_write(filp, (char *)ioctl_param, i, 0);
		break;

	case IOCTL_GET_MSG:
		i = device_read(filp, (char *)ioctl_param, 99, 0);

		put_user('\0', (char *)ioctl_param + i);
		break;

	case IOCTL_GET_NTH_BYTE:
		return Message[ioctl_param];
	}

	return SUCCESS;
}

struct file_operations Fops = {
	.read = device_read,
	.write = device_write,
	.unlocked_ioctl = ioctl_handler,
	.open = device_open,
	.release = device_release,
};

static int __init cdev_init(void)
{
	int ret_val;

	ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);
	if (ret_val < 0) {
		printk(KERN_ALERT "%s failed with %d\n",
		       "Sorry, registering the character device ", ret_val);
		return ret_val;
	}

	printk(KERN_INFO "Run: sudo mknod %s c %d 0\n", DEVICE_FILE_NAME, MAJOR_NUM);
	printk(KERN_INFO "Then: sudo chmod 666 %s\n", DEVICE_FILE_NAME);

	return 0;
}

static void __exit cdev_exit(void)
{
	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
}

module_init(cdev_init);
module_exit(cdev_exit);
MODULE_LICENSE("GPL");
