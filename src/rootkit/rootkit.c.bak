/* myModuleHello */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

void hello(char *msg);

void hello(char *msg){
	if (!msg){
		printk(KERN_INFO "Hello World\n");
    } else {
		printk(KERN_INFO "%s\n", msg);
    }
}


static void goodbye(void){
	printk(KERN_INFO "Goodbye, cruel world\n");
}

static __init int hello_init(void)
{
	hello(NULL);
	return 0;
}

static __exit void hello_exit(void)
{
	goodbye();
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("myModulehello 1, print hello at insertion and goodby at removal");
MODULE_AUTHOR("developpeur noyau");
EXPORT_SYMBOL(hello);

