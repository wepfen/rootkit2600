#include <linux/kprobes.h>
#include <linux/dirent.h>
#include <linux/uaccess.h>

// Define the kprobe structure
static struct kprobe kp = 
{
    .symbol_name = "filldir64"
};
/*
struct kprobe {
	struct hlist_node hlist;

	// list of kprobes for multi-handler support
	struct list_head list;

	// count the number of times this probe was temporarily disarmed 
	unsigned long nmissed;

	// location of the probe point 
	kprobe_opcode_t *addr;

	// Allow user to indicate symbol name of the probe point 
	const char *symbol_name;

	// Offset into the symbol 
	unsigned int offset;

	// Called before addr is executed. 
	kprobe_pre_handler_t pre_handler;

	// Called after addr is executed, unless... 
	kprobe_post_handler_t post_handler;

	// Saved opcode (which has been replaced with breakpoint) 
	kprobe_opcode_t opcode;

	//copy of the original instruction 
	struct arch_specific_insn ainsn;
   
    //Indicates various status flags.
	//Protected by kprobe_mutex after this kprobe is registered.
	 
	u32 flags;
*/

// Pre-handler: Executes before the probed function is called
static int __kprobes handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    
	char *filename = (char *)regs->si;

    int ret;
    
    /*
	pr_err("<%s> p->addr = 0x%p, ip = %lx, rdi=%lx, rsi=%s, rdx=namlen=%d,flags = 0x%lx, rax=%lu offset=%lu\n",
		p->symbol_name, p->addr, regs->ip, regs->di, (char *)regs->si, (int)regs->dx,
        regs->flags, regs->ax, regs->r10);

    pr_err("filename : %s\n", filename);
    */
    //mettre un offset de 512 à la struct précédente ?
    if ((ret = strcmp(filename, "test")) == 0){
        regs->dx = 0;
    }
	return 0;

}
/*
// appelé après l'éxecution
static void __kprobes handler_post(struct kprobe *p, struct pt_regs *regs,
				unsigned long flags)
{
    	char *filename = (char *)regs->si;

    //int ret;
    
    pr_info("handler_pre\n");
	pr_info(
		"<%s> p->addr = 0x%p, ip = %lx, rdi=%lx, rsi=%s ,flags = 0x%lx, rax=%lu\n",
		p->symbol_name, p->addr, regs->ip, regs->di, (char *)regs->si,
		regs->flags, regs->ax);

    pr_info("filename : %s", filename);       
}
*/
static int __init kprobe_init(void)
{
	int ret;
	kp.pre_handler = handler_pre;

	ret = register_kprobe(&kp);
	if (ret < 0) {
		pr_info("register_kprobe failed, returned %d\n", ret);
		return ret;
	}
	pr_info("filldir64: %px\n", kp.addr);
	return 0;
}


// Module cleanup
static void __exit kprobe_exit(void)
{
    unregister_kprobe(&kp);
    pr_info("kprobe unregistered\n");
}

module_init(kprobe_init);
module_exit(kprobe_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kprobe example for getdents64 syscall");
