#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int onevalue = 1;
static char* twostring = NULL;

module_param(onevalue, int, 0);
module_param(twostring, charp, 0);

static int hello_init(void)
{
		printk("Hello, world[ onevalue=%d, twostring=%s ]\n",onevalue, twostring);
		return 0;
}

static void hello_exit(void)
{
		printk("Goodbye, world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("KCC-AIOT");
MODULE_DESCRIPTION("test module");
MODULE_LICENSE("Dual BSD/GPL");
