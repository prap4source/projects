#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/ptrace.h>
#include "bitsops.h"

static int __init kern_mod_init(void) {
	printk("%s module loaded %d\n", __func__, current->pid);
	return 0;

}

static void __exit kern_mod_exit(void) {
	printk("%s module unloaded \n", __func__);
}

module_init(kern_mod_init);
module_exit(kern_mod_exit);
