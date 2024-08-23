#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>          
#include <linux/errno.h>       
#include <linux/types.h>       
#include <linux/fcntl.h>       

#include <linux/gpio.h>
#include <linux/moduleparam.h>

#include <linux/interrupt.h>
#include <linux/irq.h>

#include <linux/wait.h>

#define   LEDKEY_DEV_NAME            "ledkey_dev"
#define   LEDKEY_DEV_MAJOR            230      

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
//static long gpioKeyGet(void);
static void gpioKeyFree(void);

static int gpioLed[] = {6,7,8,9,10,11,12,13};
static int gpioKey[] = {16,17,18,19,20,21,22,23};
//static int key_irq[GPIOCNT];
//static int keyNumber=0;
typedef struct {
	int keyNumber;
	int key_irq[GPIOCNT];
} keyDataStruct;

static int gpioKeyIrqInit(keyDataStruct * pKeyData);
static void gpioKeyIrqFree(keyDataStruct * pKeyData);
irqreturn_t key_isr(int irq, void * data);
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
/*
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
*/
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
static int ledkey_open (struct inode *inode, struct file *filp)
{
	int i;
	int result;
    int num0 = MAJOR(inode->i_rdev); 
    int num1 = MINOR(inode->i_rdev); 
	char * irqName[GPIOCNT] = {"irqKey0","irqKey1","irqKey2","irqKey3","ir    qKey4","irqKey5","irqKey6","irqKey7"};
	keyDataStruct * pKeyData;
    printk( "call open -> major : %d\n", num0 );
    printk( "call open -> minor : %d\n", num1 );
	try_module_get(THIS_MODULE);

	    pKeyData = (keyDataStruct *)kmalloc(sizeof(keyDataStruct),GFP_KERNEL);
    if(!pKeyData)
        return -ENOMEM;
    pKeyData->keyNumber = 0;

    result = gpioKeyIrqInit(pKeyData);
    if(result < 0)
        return result;

    for(i=0;i<GPIOCNT;i++)
    {
        result = request_irq(pKeyData->key_irq[i],key_isr,IRQF_TRIGGER_RISING,irqName[i],pKeyData);
        if(result < 0)
        {
            printk("request_irq() failed irq %d\n",pKeyData->key_irq[i]);
            return result;
        }
    }

    filp->private_data = pKeyData;
    return 0;
}

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
//	char kbuf;
	int ret;
	keyDataStruct * pKeyData = (keyDataStruct *)filp->private_data;
    printk( "call read -> buf : %08X, count : %08X \n", (unsigned int)buf, count );
//	kbuf = (char)gpioKeyGet();
//	kbuf = pKeyData->keyNumber;
	if(pKeyData->keyNumber == 0)
	{
		if(!(filp->f_flags & O_NONBLOCK))	
		{
			wait_event_interruptible(WaitQueue_Read,pKeyData->keyNumber);
//			wait_event_interruptible_timeout(WaitQueue_Read,pKeyData->keyNumber,100);     //100 * 1/HZ = 1Sec

		}
	}

//	put_user(pKeyData->keyNumber,buf);
	ret=copy_to_user(buf,&(pKeyData->keyNumber),count);
	if(ret<0)
		return -EFAULT;
	if(pKeyData->keyNumber != 0)
        pKeyData->keyNumber = 0;
    return count;
}

static ssize_t ledkey_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	char kbuf;
	int ret;
    printk( "call write -> buf : %08X, count : %08X \n", (unsigned int)buf, count );
//	get_user(kbuf,buf);
	ret=copy_from_user(&kbuf,buf,count);
	if(ret<0)
		return -EFAULT;
	gpioLedSet(kbuf);
    return count;
}

static long ledkey_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{

    printk( "call ioctl -> cmd : %08X, arg : %08X \n", cmd, (unsigned int)arg );
    return 0x53;
}

static int ledkey_release (struct inode *inode, struct file *filp)
{
    printk( "call release \n" );
	module_put(THIS_MODULE);
    gpioKeyIrqFree(filp->private_data);
    if(filp->private_data)
    	kfree(filp->private_data);
    return 0;
}

struct file_operations ledkey_fops =
{
//    .owner    = THIS_MODULE,
    .open     = ledkey_open,     
    .read     = ledkey_read,     
    .write    = ledkey_write,    
	.unlocked_ioctl = ledkey_ioctl,
    .release  = ledkey_release,  
};
irqreturn_t key_isr(int irq, void * data)
{
	int i;
	keyDataStruct * pKeyData = (keyDataStruct *)data;
    for(i=0;i<GPIOCNT;i++)
    {
        if(irq == pKeyData->key_irq[i])
        {
            pKeyData->keyNumber = i+1;
            break;
        }
    }

	printk("key_isr() irq : %d, keyNumber : %d\n",irq, pKeyData->keyNumber);
	wake_up_interruptible(&WaitQueue_Read);
	return IRQ_HANDLED;
}
static int ledkey_init(void)
{
    int result;
    printk( "call ledkey_init \n" );    

    result = register_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME, &ledkey_fops);
    if (result < 0) return result;

	result = gpioLedInit();
	if(result < 0)
		return result;
	result = gpioKeyInit();
	if(result < 0)
		return result;
    return 0;
}

static void ledkey_exit(void)
{
    printk( "call ledkey_exit \n" );    
    unregister_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME );
	gpioLedFree();
    gpioKeyFree();
}

module_init(ledkey_init);
module_exit(ledkey_exit);

MODULE_AUTHOR("KCCI-AIOT");
MODULE_DESCRIPTION("test moudle");
MODULE_LICENSE("Dual BSD/GPL");
