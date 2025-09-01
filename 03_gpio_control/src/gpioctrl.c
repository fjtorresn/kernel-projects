#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>

#define IO_LED 16
#define IO_BUTTON 23

#define IO_OFFSET 512

// This is most likely to work on raspberry, not sure in other architectures
static struct gpio_desc *led, *button;

static int __init my_init(void) {
    
    int status;
    led = gpio_to_desc(IO_LED + IO_OFFSET);
    if (!led) {
        printk(KERN_ERR "gpioctrl - Error getting pin 16\n");
        return -ENODEV;
    } 
    button = gpio_to_desc(IO_BUTTON + IO_OFFSET);
    if (!button) {
        printk(KERN_ERR "gpioctrl - Error getting pin 23\n");
        return -ENODEV;
    }

    status = gpiod_direction_output(led, 0);
    if (status) {
        printk(KERN_ERR "gpioctrl - Error setting pin 16 to output\n");
        return status;
    }

    status = gpiod_direction_input(button);
    if (status) {
        printk(KERN_ERR "gpioctrl - Error setting pin 23 to input\n");
        return status;
    }
    gpiod_set_value(led, 1);
    printk(KERN_INFO "gpioctrl - Button is %spressed\n", gpiod_get_value(button) ? "not " : "");

    return 0;
}

static void __exit my_exit(void) {
    gpiod_set_value(led, 0);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Francisco");
MODULE_DESCRIPTION("GPIOs without the device tree");
