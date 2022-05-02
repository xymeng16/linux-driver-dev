/* Simple Character Utility for Loading Localities */

#include "scull.h"

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>

dev_t scull_major = SCULL_MAJOR;
dev_t scull_minor = 0;
dev_t scull_nr_devs = SCULL_NR_DEVS;

struct file_operations scull_fops = {
    .owner = THIS_MODULE,
    .llseek = scull_llseek,
    .read = scull_read,
    .write = scull_write,
    .ioctl = scull_ioctl,
    .open = scull_open,
    .release = scull_release,
};

static void scull_setup_cdev(struct scull_dev *dev, int index) {
    int err, devno = MKDEV(scull_major, scull_minor + index);

    cdev_init(&dev->cdev, &scull_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &scull_fops;
    err = cdev_add(&dev->cdev, devno, 1);

    /* Fail gracefully if need be */
    if (err)
        printk(KERN_NOTICE "Error %d adding scull%d\n", err, index);
}

int scull_open(struct inode *inode, struct file *filp) {
    struct scull_dev *dev; /* device information */

    dev = container_of(inode->i_cdev, struct scull_dev, cdev);
    filp->private_data = dev; /* for other methods */

    /* now trim to 0 the length of the device if open was write-only */
    if ((filp->f_flags & O_ACCMODE) == O_WRONLY) {
        scull_trim(dev); /* ignore errors */
    }

    return 0; /* success */
}

int scull_release(struct inode *inode, struct file *filp) {
    return 0;
}

int scull_init(void) {
    int result;
    dev_t dev = 0;

    // Get a major number
    if (scull_major) {
        dev = MKDEV(scull_major, scull_minor);
        register_chrdev_region(dev, scull_nr_devs, "scull");
    } else {
        result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs, "scull");
        scull_major = MAJOR(dev);
    }

    if (result < 0) {
        printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
        return result;
    }

    return 0;
}

void scull_cleanup(void) {
    printk(KERN_INFO "Goodbye Kernel World\n");
}

module_init(scull_init);
module_exit(scull_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Xiangyi Meng");