/* myModuleHello */
#include <linux/init.h>
#include <linux/printk.h>
#include<linux/miscdevice.h>

// int misc_register(struct miscdevice *misc)

/*
struct miscdevice mymisc;
mymisc->name = "test misc device";
mymisc->minor = MISC_DYNAMIC_MINOR; // defined in miscdevice.h
*/

///*
struct miscdevice mymisc = {
    .name = "bissap",
    .minor = MISC_DYNAMIC_MINOR
};
//*/

static int __init mymisc_init(void)
{

	int r;
	r = misc_register(&mymisc);
	if (r < 0) {
		pr_warn("misc_register() failed: %d\n", r);
		return r;
	}
	pr_info("device register succeeded\n");
	return 0;
}


static void __exit mymisc_exit(void)
{
    misc_deregister(&mymisc);
    pr_info("misc_register exit done !!!\n");
}

module_init(mymisc_init)
module_exit(mymisc_exit)

MODULE_LICENSE("MIT");
MODULE_AUTHOR("jsp frr j'essaye de rootkiter");
MODULE_DESCRIPTION("simple misc device");
MODULE_VERSION("");
