#ifndef RK_DBG_H
#define RK_DBG_H

/**
 * @file debug.h
 * 
 * @brief Debugging macros for the rootkit
 * 
 * This file contains the debugging macros for the rootkit. By enabling the
 * ROOTKIT_DEBUG macro in the configuration file, debug messages can be printed
 * to the kernel log.
 */

#include "config.h"

#include <linux/kernel.h>

/**
 * @brief Print a debug message to the kernel log
 * 
 * This macro prints a debug message to the kernel log if the ROOTKIT_DEBUG
 * macro is enabled in the configuration file.
 * 
 * @param fmt The format string
 * @param ... The arguments to format
 */
#if defined(ROOTKIT_DEBUG) && ROOTKIT_DEBUG == 1
#define RK_DEBUG(fmt, ...) printk(KERN_DEBUG fmt, ##__VA_ARGS__)
#else
#define RK_DEBUG(...)
#endif

#endif