#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

/**
 * 1. Register a device number (major and minor),
 *    this can be done by using register_chrdev()
 * 2. Create a chardev and bind it to the registered device number
 */

static int major;

static ssize_t my_read(struct file *f, char __user *u, size_t l, loff_t *o) {
    printk(KERN_INFO "hello_cdev - Read is called\n");
    return 0;
}

static struct file_operations fops = {
    .read = my_read
};

static int __init my_init(void) {
    major = register_chrdev(0, "hello_cdev", &fops);
    if (major < 0) {
        printk(KERN_ERR "hello_cdev - Error registering chrdev\n");
        return major;
    }
    printk(KERN_INFO "hello_cdev -  Major device number: %d\n", major);
    return 0;
}

static void __exit my_exit(void) {
    unregister_chrdev(major, "hello_cdev");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Francisco - Raspberry");
MODULE_DESCRIPTION("An example for registering a character device");
