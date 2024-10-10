#ifndef RK_DBG_H
#define RK_DBG_H

#include "config.h"

#include <linux/kernel.h>

#if defined(ROOTKIT_DEBUG) && ROOTKIT_DEBUG == 1
#define DEBUG(fmt, ...) printk(KERN_DEBUG fmt, ##__VA_ARGS__)
#else
#define DEBUG(...)
#endif

#endif