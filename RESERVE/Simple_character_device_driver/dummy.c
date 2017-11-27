#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrii Radiuk");

static int dev_open(struct inode *, struct file *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);
static int dev_release(struct inode *inodp, struct file *filp);

static int id = 0;
module_param(id, int, 0);
MODULE_PARM_DESC(id, "dummy id number");

static int			major;
static int			device_open = 0;
static char			device_name[16];
static struct class	*dev_class;
static struct device *dev_device;
static char message[81];

static struct file_operations	fops =
{
	.owner = THIS_MODULE,
	.open = dev_open,
	.write = dev_write,
	.release = dev_release
};

static int	__init dummy_init(void)
{
	sprintf(device_name, "dummy%d", id);
	printk(KERN_CRIT "%s: device has been created\n", device_name);

		//	Registering char device
	if ((major = register_chrdev(0, device_name, &fops)) < 0)
	{
		printk(KERN_CRIT "%s: failed to register a major number\n", device_name);
		return (major);
	}

		//	Creating a class for device
	if ((dev_class = class_create(THIS_MODULE, device_name)) == NULL)
	{
		printk(KERN_CRIT "%s: failed to create a class\n", device_name);
		unregister_chrdev(major, device_name);
		return (-1);
	}

		//	Create and register a device
	if ((dev_device = device_create(dev_class, NULL, MKDEV(major, 0), NULL, device_name)) == NULL)
	{
		printk(KERN_CRIT "%s: failed to create a device\n", device_name);
		class_destroy(dev_class);
		unregister_chrdev(major, device_name);
		return (-1);
	}
	return (0);
}

static void __exit dummy_exit(void)
{
	printk(KERN_CRIT "%s: device has been removed\n", device_name);
	device_destroy(dev_class, MKDEV(major, 0));
	class_destroy(dev_class);
	unregister_chrdev(major, device_name);
}

static int dev_open(struct inode *inode, struct file *file)
{
	device_open++;
	// printk(KERN_INFO "%s: device has been opened %d times\n", device_name, device_open);
	return (0);
}

static ssize_t dev_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	int	bytes_written = 0;
	size_t	msg_size = sizeof(message);

	if (len > msg_size)
	{
		printk(KERN_INFO "%s: message is too long. Try again with a maximum of %zu symbols\n", device_name, msg_size - 1);
		return (-1);
	}

		//	Copies len or sizeof(message) bytes depending on what's smaller
	if (len < msg_size)
	{
		copy_from_user(message, buff, len);
		message[len] = '\0';
		bytes_written = len;
	}
	else
	{
		copy_from_user(message, buff, msg_size - 1);
		message[msg_size - 1] = '\0';
		bytes_written = msg_size - 1;
	}

	printk(KERN_INFO "dummy[%d]: %s", id, message);
	// printk(KERN_INFO "%s: device has written %d bytes\n", device_name, bytes_written);
	return (bytes_written);
}

static int dev_release(struct inode *inodp, struct file *filp)
{
	// printk(KERN_INFO "%s: device has been closed\n", device_name);
	return (0);
}

module_init(dummy_init);
module_exit(dummy_exit);
