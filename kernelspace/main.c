#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init kern_mod_init(void) {
	printk("%s module loaded \n", __func__);
	return 0;

}

static void __exit kern_mod_exit(void) {
	printk("%s module unloaded \n", __func__);
}

module_init(kern_mod_init);
module_exit(kern_mod_exit);
