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
#include <linux/delay.h>

#include <linux/gpio.h>
#include <linux/moduleparam.h>

#include <linux/interrupt.h>
#include <linux/irq.h>

#include <linux/ioctl.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include "ioctl_test.h"

#define   LEDKEY_DEV_NAME            "keyled_dev"
#define   LEDKEY_DEV_MAJOR            230

#define DEBUG 1
#define OFF 0
#define ON 1
#define GPIOCNT 8

static int ledVal = 0;
module_param(ledVal, int, 0);
static int timerVal = 100;	//f=100HZ, T=1/100 = 10ms, 100*10ms = 1Sec
module_param(timerVal, int ,0);

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

typedef struct {
		int keyNumber;
		int key_irq[GPIOCNT];
} keyDataStruct;

static int gpioKeyIrqInit(keyDataStruct * pKeyData);
static void gpioKeyIrqFree(keyDataStruct * pKeyData);
irqreturn_t key_isr(int irq, void* data);
DECLARE_WAIT_QUEUE_HEAD(WaitQueue_Read);

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

static int gpioKeyIrqInit(keyDataStruct * pKeyData)
{
    int i;
    for(i=0;i<GPIOCNT;i++)
    {
        pKeyData->key_irq[i] = gpio_to_irq(gpioKey[i]);
        if(pKeyData->key_irq[i] < 0) {
            printk("Failed gpio_to_irq() gpio%d error\n", gpioKey[i]);
            return pKeyData->key_irq[i];
        }
    }
    return 0;
}

static void gpioKeyIrqFree(keyDataStruct * pKeyData)
{
    int i;
    for(i=0;i<GPIOCNT;i++)
    {
        free_irq(pKeyData->key_irq[i],pKeyData);
    }
}


int ledkey_open (struct inode* inode, struct file* filp)
{
		int i;
		int result;
		int num0 = MAJOR(inode->i_rdev);
		int num1 = MINOR(inode->i_rdev);
		char* irqName[GPIOCNT] = {"irqKey0", "irqKey1", "irqKey2", "irqKey3", "irqKey4", "irqKey5", "irqKey6", "irqKey7"};
		keyDataStruct* pKeyData;
		printk("call open -> major : %d\n", num0);
		printk("call open -> minor : %d\n", num1);
		try_module_get(THIS_MODULE);
		
		pKeyData = (keyDataStruct *)kmalloc(sizeof(keyDataStruct), GFP_KERNEL);
		if(!pKeyData)
				return -ENOMEM;
		pKeyData->keyNumber = 0;

		result = gpioKeyIrqInit(pKeyData);
		if(result<0)
				return result;

		for(i=0; i<GPIOCNT; i++)
		{
				result = request_irq(pKeyData->key_irq[i], key_isr, IRQF_TRIGGER_RISING, irqName[i], pKeyData);
				if (result < 0)
				{
						printk("request_irq() failed irq %d\n", pKeyData->key_irq[i]);
						return result;
				}
		}
		
		filp->private_data = pKeyData;
		return 0;
}

loff_t ledkey_llseek (struct file *filp, loff_t off, int whence )
{
    printk( "call llseek -> off : %08X, whenec : %08X\n", (unsigned int)off, whence );
    return 0x23;
}

ssize_t ledkey_read(struct file* filp, char* buf, size_t count, loff_t* f_pos)
{
//	char kbuf;
	int ret;
	keyDataStruct * pKeyData = (keyDataStruct *)filp->private_data;
	printk("call read -> buf: %08X, count : %08X \n", (unsigned int)buf, count);
//	kbuf = (char)gpioKeyGet();
//	ret = copy_to_user(buf, &kbuf, count);
	if (pKeyData->keyNumber == 0)
	{
			if(!(filp->f_flags & O_NONBLOCK))
			{
					wait_event_interruptible(WaitQueue_Read,pKeyData->keyNumber);
			}
	}
	
	ret=copy_to_user(buf,&(pKeyData->keyNumber),count);
	if (ret < 0)
			return -EFAULT;
	if(pKeyData->keyNumber != 0)
			pKeyData->keyNumber = 0;
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
    gpioLedSet(kbuf);
	ledVal=kbuf;
	return count;
}

static long ledkey_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
		keyled_data info;
		int err = 0, size;

		if( _IOC_TYPE( cmd ) != IOCTLTEST_MAGIC ) return -EINVAL;
		if( _IOC_NR( cmd ) >= IOCTLTEST_MAXNR ) return -EINVAL;

		size = _IOC_SIZE( cmd );
		if (size)
		{
				if( _IOC_DIR( cmd ) & _IOC_READ )
						err = access_ok( (void *) arg, size );
				if( _IOC_DIR( cmd ) & _IOC_WRITE )
						err = access_ok( (void *) arg, size );
				if( !err ) return err;
		}
		switch(cmd)
		{
				char buf;
				case IOCTLTEST_KEYLEDINIT :
					gpioLedInit();
					gpioKeyInit();
					break;
				case IOCTLTEST_KEYINIT :
					gpioKeyInit();
					break;
				case IOCTLTEST_LEDINIT :
					gpioLedInit();
					break;
				case IOCTLTEST_KEYLEDFREE :
					gpioLedFree();
					gpioKeyFree();
					break;
				case IOCTLTEST_LEDOFF :
					gpioLedSet(0);
					break;
				/*
				case IOCTLTEST_LEDONOFF :
					gpioLedSet(255);
					mdelay(1000);
					gpioLedSet(0);
					break;
				*/
				case IOCTLTEST_GETSTATE :
					buf = gpioKeyGet();
					return buf;
				case IOCTLTEST_READ :
					info.timer_val = gpioKeyGet();
					if(info.timer_val != 0)
							info.timer_val=1;
					err = copy_to_user((void *)arg,(const void *)&info.timer_val,size);
					if (err != 0) {
							return -EFAULT;
					}
					break;

				case IOCTLTEST_WRITE :
					err = copy_from_user((void *)&info.timer_val,(void *)arg,size);
					if (err != 0) {
							return -EFAULT;
					}
					if(info.timer_val == 1)
							gpioLedSet(info.timer_val);
					break;
				case IOCTLTEST_WRITE_READ :
					err = copy_from_user((void *)&info.timer_val,(void *)arg,size);
					if (err != 0) {
							return -EFAULT;
					}
					if(info.timer_val == 1)
							gpioLedSet(info.timer_val);

					info.timer_val = gpioKeyGet();
					if(info.timer_val != 0)
							info.timer_val=1;
					else
							info.timer_val=0;

					err = copy_to_user((void *)arg,(const void *)&info.timer_val,size);
					if (err != 0) {
							return -EFAULT;
					}
					break;
				case TIMER_START :
					mod_timer(&timerLed, get_jiffies_64() + timerVal);
					printk(KERN_INFO "TIMER START!\n");
					break;

				case TIMER_STOP :
					del_timer_sync(&timerLed);
					printk(KERN_INFO "TIMER STOP!\n");
					break;

				case TIMER_VALUE :
					if (copy_from_user((void*)&info, (void*)arg, size))
							return -EFAULT;
							
					timerVal = info.timer_val;
					printk(KERN_INFO "TIMER INTERVAL SET TO %lu ms\n", timerVal);
					break;

				default:
					err =-E2BIG;
					break;
			}
		return err;
}

static __poll_t ledkey_poll(struct file* filp, struct poll_table_struct* wait)
{
		unsigned int mask = 0;
		keyDataStruct * pKeyData = (keyDataStruct *)filp->private_data;
#ifdef DEBUG
		printk("_key : %u\n",(wait->_key & POLLIN));
#endif
		if(wait->_key & POLLIN)
				poll_wait(filp, &WaitQueue_Read, wait);
		if(pKeyData->keyNumber > 0)
				mask = POLLIN;

		return mask;
}

int ledkey_release (struct inode *inode, struct file *filp)
{
    printk( "call release \n" );
    module_put(THIS_MODULE);
	gpioKeyIrqFree(filp->private_data);
	
	if(timer_pending(&timerLed))
		del_timer(&timerLed);
	
	if(filp->private_data)
			kfree(filp->private_data);
    return 0;
}

struct file_operations ledkey_fops =
{
    .open     = ledkey_open,
    .read     = ledkey_read,
    .write    = ledkey_write,
    .unlocked_ioctl = ledkey_ioctl,
    .llseek   = ledkey_llseek,
    .poll     = ledkey_poll,
	.release  = ledkey_release,
};

irqreturn_t key_isr(int irq, void * data)
{
		int i;
		keyDataStruct * pKeyData = (keyDataStruct *)data;
		for (i = 0; i < GPIOCNT; i++)
		{
				if(irq == pKeyData->key_irq[i])
				{
						pKeyData->keyNumber = i + 1;
						break;
				}
		}
		printk("key_isr() irq : %d, keyNumber : %d\n",irq, pKeyData->keyNumber);
		wake_up_interruptible(&WaitQueue_Read);
		return IRQ_HANDLED;
}

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
