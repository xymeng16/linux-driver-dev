#include <linux/init.h>
#include <linux/module.h>

int hello_init(void) {
  printk(KERN_INFO "Hello Kernel World\n");
  return 0;
}

void hello_exit(void) { printk(KERN_INFO "Goodbye Kernel World\n"); }

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Xiangyi Meng");