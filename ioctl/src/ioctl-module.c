// SPDX_License_Identifier: GPL

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#include <../includes/ioctl_cmds.h>

volatile static int is_open = 0;
static char message[BUF_LEN] = {0};
static int num_bytes = 0;
static int devnum = 0;

static ssize_t hello_read(struct file *filp, char __user *outb, size_t nbytes, loff_t *offset)
{
	int bytes_read = 0;

	if (*offset >= num_bytes)
		return 0;

	while ((bytes_read < nbytes) && (*offset < num_bytes)) {
		put_user(message[*offset], &outb[bytes_read]);
		*offset = *offset + 1;
		bytes_read++;
	}

	return bytes_read;
}

ssize_t hello_write(struct file *filp, const char __user *inpb, size_t nbytes, loff_t *offset)
{
	int bytes_write = 0;

	if (offset == NULL)
		return -EINVAL;

	if (*offset >= BUF_LEN - 1)
		return -EINVAL;

	while ((bytes_write < nbytes) && (*offset < BUF_LEN - 1)) {
		get_user(message[*offset], &inpb[bytes_write]);
		*offset = *offset + 1;
		bytes_write++;
	}
	num_bytes = *offset;
	return bytes_write;
}

int hello_open(struct inode *inodep, struct file *filep)
{
	if (is_open == 1)
		return -EBUSY;

	is_open = 1;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

int hello_release(struct inode *inodep, struct file *filep)
{
	if (!is_open) {
		printk(KERN_INFO "Device wasn't busy...\n");
		return -EBUSY;
	}
	is_open = 0;
	module_put(THIS_MODULE);
}
/**
 * @brief this function is going to handle all IOCTL 
 * process call.
 *
 * @param inode: additional param that describes device
 * @param filp: additional param that describes device
 * @param ioctl_num: IOCTL command group number
 * @param ioctl_param: IOCTL parameters given to called function
 * @return int
 */
long ioctl_handler(struct file *filp, unsigned int ioctl_num, unsigned long ioctl_param)
{
	int i; /*! index in for loop */
	char *temp; /*! pointer to mesage for user */
	char ch; /*! we're gonna write our messages char by char */

	/**
	 * @brief switching according to the IOCTL command number
	 */
	switch (ioctl_num) {
	case IOCTL_SET_MSG:
		if ((char *)ioctl_param) {
			printk(KERN_INFO "There's no msg?\n");
			break;
		}

		temp = (char *)ioctl_param;
		get_user(ch, temp);
		for (i = 0; ch && i < BUF_LEN; ++i, ++temp)
			get_user(ch, temp);

		hello_write(filp, message, i, 0);
		break;
	case IOCTL_GET_MSG:
		i = hello_read(filp, message, BUF_LEN, 0);
		put_user('\0', message + i);
		break;
	case IOCTL_GET_NTH_BYTE:
		return message[ioctl_param];
	default:
		printk(KERN_INFO "Wrong IOCTL command ID...\n");
	}

	return SUCCESS;
}

struct file_operations fops = {
	.read = hello_read,
	.write = hello_write,
	.unlocked_ioctl = ioctl_handler,
	.open = hello_open,
	.release = hello_release,
};

static int __init ioctl_init(void)
{
	printk(KERN_INFO "Hello from init\n");
	num_bytes = strlen(message);

	devnum = register_chrdev(0, DEVICE_FILE_NAME, &fops);
	if (devnum < 0) {
		printk(KERN_INFO "Cannot register device...\n");
		return -EINVAL;
	}

	printk(KERN_INFO "Major number is: %d\nDevice file name is: %s\n", devnum, DEVICE_FILE_NAME);
	printk(KERN_INFO "sudo mknod %s c %d 0\n", DEVICE_FILE_NAME, devnum);

	return 0;
}

static void __exit ioctl_exit(void)
{
	printk(KERN_INFO "%s\n", __func__);
	unregister_chrdev(devnum,  DEVICE_FILE_NAME);
}

module_init(ioctl_init);
module_exit(ioctl_exit);

MODULE_LICENSE("GPL");
