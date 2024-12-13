/**
 * @file client.h
 * 
 * @brief Definitions for the client
 * 
 * This file contains the definitions for the client.
 */

#ifndef _C_CLIENT_H
#define _C_CLIENT_H

/**
 * @brief Check if the rootkit driver is present
 *
 * This function checks if the rootkit driver is present on the system.
 *
 * @param driver The path to the rootkit device driver
 *
 * @return 0 if the driver is present, -1 if the driver is not present
 */
int check_driver(char *driver);

#endif // _C_CLIENT_H