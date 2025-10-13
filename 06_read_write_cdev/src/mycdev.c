#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

/**
 * We want a text buffer to be accesible from user space to read/write.
 * 1) Read: copy from text to user.
 * 2) Write: copy from uset to text.
 */

static int major;
static char text[64];

/**
 * @param file *filp: represents an opened file in the linux kernel.
 * @param char *user_buf: holds the data that being read from text to user space.
 * @param size_t len: length of the user_buf. 
 * @param loff_t *off: current position within the file.
 * return: amount of bytes that has been read successfuly.
 */
static ssize_t my_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off) {
    int not_copied, delta, to_copy = (len + *off) < sizeof(text) ? len : (sizeof(text) - *off);

    printk(KERN_INFO "hello_cdev - Read is called, we want to read %ld bytes, but actually only coping %d bytes. The offset is %lld\n", len, to_copy, *off);

    if (*off >= sizeof(text))
        return 0;
    
    // return the number of bytes that has not been copied successfully.
    not_copied = copy_to_user(user_buf, &text[*off], to_copy);
    delta = to_copy - not_copied;
    if (not_copied)
        printk(KERN_WARNING "hello_cdev - Could only copy %d bytes\n", delta);

    *off += delta;

    return delta;
}

static ssize_t my_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off) {
    int not_copied, delta, to_copy = (len + *off) < sizeof(text) ? len : (sizeof(text) - *off);

    printk(KERN_INFO "hello_cdev - Write is called, we want to write %ld bytes, but actually only coping %d bytes. The offset is %lld\n", len, to_copy, *off);

    if (*off >= sizeof(text))
        return 0;
    
    // return the number of bytes that has not been copied successfully.
    not_copied = copy_from_user(&text[*off], user_buf, to_copy);
    delta = to_copy - not_copied;
    if (not_copied)
        printk(KERN_WARNING "hello_cdev - Could only copy %d bytes\n", delta);

    *off += delta;

    return delta;
}

static struct file_operations fops = {
    .read = my_read,
    .write = my_write
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
