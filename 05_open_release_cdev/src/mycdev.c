#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>


static int major;

static int my_open(struct inode *pinode, struct file *pfile) {
    printk(KERN_INFO "hello_cdev - Major: %d, Minor: %d\n", imajor(pinode), iminor(pinode));

    printk(KERN_INFO "hello-cdev - pfile->f_pos: %lld\n", pfile->f_pos);
    printk(KERN_INFO "hello-cdev - pfile->f_mode: 0x%x\n", pfile->f_mode);
    printk(KERN_INFO "hello-cdev - pfile->f_flags: 0x%x\n", pfile->f_flags);

    return 0;
}


static int my_release(struct inode *pinode, struct file *pfile) {
    pr_info("hello-cdev - File is closed\n");
    return 0;
}

static struct file_operations fops = {
    .open = my_open,
    .release = my_release,    
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
