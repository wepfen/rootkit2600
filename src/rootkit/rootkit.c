/* myModuleHello */
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

// int misc_register(struct miscdevice *misc)

/*
struct miscdevice mymisc;
mymisc->name = "test misc device";
mymisc->minor = MISC_DYNAMIC_MINOR; // defined in miscdevice.h
*/

static int      __init mymisc_init(void);
static void     __exit mymisc_exit(void);
static int 		mymisc_open(struct inode *i, struct file *f);
static int 		mymisc_release(struct inode *i, struct file *f);
static ssize_t	mymisc_read(struct file *file, char __user *buf, size_t count, loff_t *off);
//static ssize_t	mymisc_write(struct file *file, const char __user *buf, size_t count, loff_t *off);
static long 	mymisc_ioctl(struct file *file, unsigned int request, unsigned long arg);


static struct file_operations fops =
{
    .owner      	= THIS_MODULE,
    .read       	= mymisc_read,
//	.write			= mymisc_write,
    .open       	= mymisc_open,
    .release    	= mymisc_release,
	.unlocked_ioctl = mymisc_ioctl
};

///*
struct miscdevice mymisc = {
    .name = "bissap",
    .minor = MISC_DYNAMIC_MINOR,
	.fops = &fops 
};
//*/
//https://github.com/torvalds/linux/blob/master/include/linux/miscdevice.h#L79

static int mymisc_open(struct inode *i, struct file *f)
{
        pr_info("Device File Opened...!!!\n");
        return 0;
}

/*
** This function will be called when we close the Device file
*/

//release
static int mymisc_release(struct inode *i, struct file *f)
{
        pr_info("Device File Closed...!!!\n");
        return 0;
}

//read
static ssize_t	mymisc_read(struct file *file, char __user *buf, size_t count, loff_t *off)
{
        pr_info("Device have been read...!!!\n");
        return 0;
}

/*
//write
static ssize_t	mymisc_write(struct file *file, const char __user *buf, size_t count, loff_t *off)
{
        pr_info("Device have been written...!!!\n");
        return 0;
}
*/

//ioctl
static long 	mymisc_ioctl(struct file *file, unsigned int request, unsigned long arg)
{
	
        pr_info("Device with ioctl...!!!\n");
        return 0;
}

static int __init mymisc_init(void)
{

	int r;
	r = misc_register(&mymisc);
	if (r < 0) {
		pr_warn("misc_register() failed: %d\n", r);
		return r;
	}
	pr_info("device register succeeded\n");
	return 0;
}


static void __exit mymisc_exit(void)
{
    misc_deregister(&mymisc);
    pr_info("misc_register exit done !!!\n");
}

module_init(mymisc_init)
module_exit(mymisc_exit)

MODULE_LICENSE("MIT");
MODULE_AUTHOR("jsp frr j'essaye de rootkiter");
MODULE_DESCRIPTION("simple misc device");
MODULE_VERSION("");
