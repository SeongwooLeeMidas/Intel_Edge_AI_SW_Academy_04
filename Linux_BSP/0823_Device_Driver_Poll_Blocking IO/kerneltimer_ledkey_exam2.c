#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/time.h>
#include <linux/timer.h>

#include <linux/gpio.h>
#include <linux/moduleparam.h>

#include <linux/interrupy.h>
#include <linux/irq.h>

#include <linux/ioctl.h>
#include <linux/wait.h>
#include <linux/poll.h>

#define   LEDKEY_DEV_NAME            "kerneltimer"
#define   LEDKEY_DEV_MAJOR            230

#define DEBUG 1
#define OFF 0
#define ON 1
#define GPIOCNT 8
//#define DEBUG

static int timerVal = 100;	//f=100HZ, T=1/100 = 10ms, 100*10ms = 1Sec
module_param(timerVal, int ,0);
static int ledVal = 0;
module_param(ledVal, int, 0);

struct timer_list timerLed;
void kerneltimer_func(struct timer_list *t );

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
			printk("Failed request gpio%d error\n",gpioKey[i]);
#endif
			return ret;
		}
	}
	for(i=0;i<GPIOCNT;i++)
	{
		ret = gpio_direction_input(gpioKey[i]);
		if(ret < 0) {
#ifdef DEBUG
			printk("Failed direction_output gpio%d error\n",gpioKey[i]);
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

int ledkey_open (struct inode* inode, struct file* filp)
{
		int num0 = MAJOR(inode->i_rdev);
		int num1 = MINOR(inode->i_rdev);
		printk("call open -> major : %d\n", num0);
		printk("call open -> minor : %d\n", num1);
		try_module_get(THIS_MODULE);
		return 0;
}

loff_t ledkey_llseek (struct file *filp, loff_t off, int whence )
{
    printk( "call llseek -> off : %08X, whenec : %08X\n", (unsigned int)off, whence );
    return 0x23;
}

ssize_t ledkey_read(struct file* filp, char* buf, size_t count, loff_t* f_pos)
{
	char kbuf;
	int ret;
	printk("call read -> buf: %08X, count : %08X \n", (unsigned int)buf, count);
	kbuf = (char)gpioKeyGet();
	ret = copy_to_user(buf, &kbuf, count);
	if (ret < 0)
		return -EFAULT;
		
	return count;
}

ssize_t ledkey_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    char kbuf;
    int ret;
    printk( "call write -> buf : %08X, count : %08X \n", (unsigned int)buf, count );
//  get_user(kbuf,buf);
    ret=copy_from_user(&kbuf,buf,count);
    if(ret<0)
        return -EFAULT;
//    gpioLedSet(kbuf);
    ledVal = (int)kbuf;
	return count;
}

static long ledkey_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{

    printk( "call ioctl -> cmd : %08X, arg : %08X \n", cmd, (unsigned int)arg );
    return 0x53;
}

int ledkey_release (struct inode *inode, struct file *filp)
{
    printk( "call release \n" );
    module_put(THIS_MODULE);
    return 0;
}

struct file_operations ledkey_fops =
{
    .open     = ledkey_open,
    .read     = ledkey_read,
    .write    = ledkey_write,
    .unlocked_ioctl = ledkey_ioctl,
    .llseek   = ledkey_llseek,
    .release  = ledkey_release,
};

void kerneltimer_registertimer(unsigned long timeover)
{
	timerLed.expires = get_jiffies_64() + timeover;  //10ms(1/100) *100 = 1sec
	timer_setup( &timerLed,kerneltimer_func,0);
	add_timer( &timerLed );
}

void kerneltimer_func(struct timer_list *t)
{
#if DEBUG
	printk("ledVal : %#04x\n",(unsigned int)(ledVal));
#endif
	gpioLedSet(ledVal);

	ledVal = ~ledVal & 0xff;
	mod_timer(t, get_jiffies_64() + timerVal);
}

int kerneltimer_init(void)
{
	int ret;
#if DEBUG
	printk("timerVal : %d , sec : %d \n",timerVal,timerVal/HZ );
#endif
	ret = register_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME, &ledkey_fops);

	ret = gpioLedInit();
	if(ret < 0)
		return ret;
	ret = gpioKeyInit();
	if(ret < 0)
		return ret;

	kerneltimer_registertimer(timerVal);
	return 0;
}
void kerneltimer_exit(void)
{
	printk( "call ledkey_exit \n" );
    unregister_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME );
	if(timer_pending(&timerLed))
		del_timer(&timerLed);
	gpioLedFree();
	gpioKeyFree();
}

module_init(kerneltimer_init);
module_exit(kerneltimer_exit);

MODULE_AUTHOR("KCCI-AIOT KSH");
MODULE_DESCRIPTION("led key test module");
MODULE_LICENSE("Dual BSD/GPL");
