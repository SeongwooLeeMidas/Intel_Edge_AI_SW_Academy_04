#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>          
#include <linux/errno.h>       
#include <linux/types.h>       
#include <linux/fcntl.h>       

#include <linux/gpio.h>
#include <linux/moduleparam.h>

#define   CALL_DEV_NAME            "call_dev"
#define   CALL_DEV_MAJOR            230      

#define OFF 0
#define ON 1
#define GPIOCNT 8
//#define DEBUG

static int ledval = 0;
module_param(ledval, int, 0);

static long gpioLedInit(void);
static void gpioLedSet(long);
static void gpioLedFree(void);
static long gpioKeyInit(void);
static long gpioKeyGet(void);
static void gpioKeyFree(void);

static int gpioLed[] = {6,7,8,9,10,11,12,13};
static int gpioKey[] = {16,17,18,19,20,21,22,23};

static long gpioLedInit(void)
{
	long ret = 0;
	int i;
	char gpioName[10];
	for(i=0;i<GPIOCNT;i++)
	{
		sprintf(gpioName,"gpio%d",gpioLed[i]);
		ret = gpio_request(gpioLed[i],gpioName);
		if(ret < 0) {
#ifdef DEBUG
			printk("Failed request gpio%d error\n",gpioLed[i]);
#endif
			return ret;
		}
	}
	for(i=0;i<GPIOCNT;i++)
	{
		ret = gpio_direction_output(gpioLed[i],OFF);
		if(ret < 0) {
#ifdef DEBUG
			printk("Failed direction_output gpio%d error\n",gpioLed[i]);
#endif
			return ret;
		}
	}
	return ret;
}
static void gpioLedSet(long val)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_set_value(gpioLed[i],val & (0x1 << i));
//		gpio_set_value(gpioLed[i],(val>>i) & 0x1);
	}

}
static void gpioLedFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
  		gpio_free(gpioLed[i]);
	}
}
static long gpioKeyInit(void)
{
	long ret = 0;
	int i;
	char gpioName[10];
	for(i=0;i<GPIOCNT;i++)
	{
		sprintf(gpioName,"gpio%d",gpioKey[i]);
		ret = gpio_request(gpioKey[i],gpioName);
		if(ret < 0) {
#ifdef DEBUG
			printk("Failed request gpio%d error\n",6);
#endif
			return ret;
		}
	}
	for(i=0;i<GPIOCNT;i++)
	{
		ret = gpio_direction_input(gpioKey[i]);
		if(ret < 0) {
#ifdef DEBUG
			printk("Failed direction_output gpio%d error\n",6);
#endif
			return ret;
		}
	}
	return ret;
}
static long gpioKeyGet(void)
{
	long keyData=0;
	long temp;
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		temp = gpio_get_value(gpioKey[i]) << i;
		keyData |= temp;
	}
	return keyData;
}
static void gpioKeyFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
  		gpio_free(gpioKey[i]);
	}
}
int call_open (struct inode *inode, struct file *filp)
{
    int num0 = MAJOR(inode->i_rdev); 
    int num1 = MINOR(inode->i_rdev); 
    printk( "call open -> major : %d\n", num0 );
    printk( "call open -> minor : %d\n", num1 );
	try_module_get(THIS_MODULE);
    return 0;
}

loff_t call_llseek (struct file *filp, loff_t off, int whence )
{
    printk( "call llseek -> off : %08X, whenec : %08X\n", (unsigned int)off, whence );
    return 0x23;
}

ssize_t call_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	long keyData;
    printk( "call read -> buf : %08X, count : %08X \n", (unsigned int)buf, count );
	keyData = gpioKeyGet();
	*buf = (char)keyData;
    return 0x33;
}

ssize_t call_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    printk( "call write -> buf : %08X, count : %08X \n", (unsigned int)buf, count );
	gpioLedSet(*buf);
    return 0x43;
}

//int call_ioctl (struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
static long call_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{

    printk( "call ioctl -> cmd : %08X, arg : %08X \n", cmd, (unsigned int)arg );
    return 0x53;
}

int call_release (struct inode *inode, struct file *filp)
{
    printk( "call release \n" );
	module_put(THIS_MODULE);
    return 0;
}

struct file_operations call_fops =
{
//    .owner    = THIS_MODULE,
    .open     = call_open,     
    .read     = call_read,     
    .write    = call_write,    
	.unlocked_ioctl = call_ioctl,
    .llseek   = call_llseek,   
    .release  = call_release,  
};

int call_init(void)
{
    int result;

    printk( "call call_init \n" );    

    result = register_chrdev( CALL_DEV_MAJOR, CALL_DEV_NAME, &call_fops);
    if (result < 0) return result;

	result = gpioLedInit();
    if(result < 0)
		return result;
	result = gpioKeyInit();
    if(result < 0)
        return result;

    return 0;
}

void call_exit(void)
{
    printk( "call call_exit \n" );    
    unregister_chrdev( CALL_DEV_MAJOR, CALL_DEV_NAME );
	gpioLedFree();
    gpioKeyFree();
}

module_init(call_init);
module_exit(call_exit);

MODULE_AUTHOR("KCCI-AIOT");
MODULE_DESCRIPTION("test moudle");
MODULE_LICENSE("Dual BSD/GPL");
