/**
 * There are two important events:
 * 1. When the module is loaded into the kernel - module_init
 * 2. When the module is remove from the kernel - module-exit
 * For these two events when need to implemenet
 * callback functions.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL"); //GNU General Purpose License
MODULE_AUTHOR("Francisco");
MODULE_DESCRIPTION("Example module");
MODULE_VERSION("0.1");

// __init and __exit are just for readbility
static int __init hello_init(void) {
    printk(KERN_INFO "Hello from the kernel\n");
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye from the kernel\n");
}

module_init(hello_init);
module_exit(hello_exit);

