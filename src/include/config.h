/**
 * @file config.h
 * 
 * @brief Configuration file for the rootkit
 * 
 * This file contains the configuration options for the rootkit. By changing
 * the values in this file, the behavior of the rootkit can be modified.
 */

#ifndef _RK_CONFIG_H
#define _RK_CONFIG_H

/**
 * @brief Enable or disable debugging
 * 
 * This macro enables or disables debugging messages in the rootkit.
 */
#define RK_DEBUG 1

#define RK_NAME "maxiproutkit"

/**
 * @brief The name of the rootkit device driver
 * 
 * This macro defines the name of the rootkit device driver.
 */
#define RK_DRIVER "maxiproutkit"

/**
 * @brief The command to escalate privileges
 * 
 * This macro defines the command that will be used to escalate privileges.
 * 
 * @note This command needs to be sent to the rootkit device driver to escalate
 */
#define RK_PRIVESC "skibidi root"

/**
 * @brief The command to hide the rootkit
 * 
 * This macro defines the command that will be used to hide the rootkit.
 * 
 * @note This command needs to be sent to the rootkit device driver to hide the
 * rootkit from the kernel module list
 */
#define RK_HIDE "disparition no jutsu"

/**
 * @brief The command to reveal the rootkit
 * 
 * This macro defines the command that will be used to reveal the rootkit.
 * 
 * @note This command needs to be sent to the rootkit device driver to reveal the
 * rootkit in the kernel module list
 */
#define RK_REVEAL "omg face reveal irl live en stream ce soir 21h"

#endif // RK_CONFIG_H