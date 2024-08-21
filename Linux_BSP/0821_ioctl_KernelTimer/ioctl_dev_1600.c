#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>

#include <linux/fs.h>          
#include <linux/errno.h>       
#include <linux/types.h>       
#include <linux/fcntl.h>       

#include <linux/moduleparam.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include "ioctl_test.h"

#define GPIOLEDCNT 8
#define GPIOKEYCNT 8
#define OFF 0
#define ON 1

#define   LEDKEY_DEV_NAME            "ioctldev"
#define   LEDKEY_DEV_MAJOR            230      
static int gpioLed[GPIOLEDCNT] = {6,7,8,9,10,11,12,13};
static int gpioKey[GPIOKEYCNT] = {16,17,18,19,20,21,22,23};
static int onevalue = 1;
static char * twostring = NULL;
module_param(onevalue, int ,0);
module_param(twostring,charp,0);


static int gpioLedInit(void);
static void gpioLedSet(long);
static void gpioLedFree(void);
static int gpioKeyInit(void);
static int gpioKeyGet(void);
static void gpioKeyFree(void);

static int	gpioLedInit(void)
{
	int i;
	int ret = 0;
	char gpioName[10];
	for(i=0;i<GPIOLEDCNT;i++)
	{
		sprintf(gpioName,"led%d",i);
		ret = gpio_request(gpioLed[i], gpioName);
		if(ret < 0) {
			printk("Failed Request gpio%d error\n", 6);
			return ret;
		}
	}
	for(i=0;i<GPIOLEDCNT;i++)
	{
		ret = gpio_direction_output(gpioLed[i], OFF);
		if(ret < 0) {
			printk("Failed direction_output gpio%d error\n", 6);
       	 return ret;
		}
	}
	return ret;
}

static void gpioLedSet(long val) 
{
	int i;
	for(i=0;i<GPIOLEDCNT;i++)
	{
		gpio_set_value(gpioLed[i], (val>>i) & 0x01);
	}
}
static void gpioLedFree(void)
{
	int i;
	for(i=0;i<GPIOLEDCNT;i++)
	{
		gpio_free(gpioLed[i]);
	}
}

static int gpioKeyInit(void) 
{
	int i;
	int ret=0;
	char gpioName[10];
	for(i=0;i<GPIOKEYCNT;i++)
	{
		sprintf(gpioName,"key%d",i);
		ret = gpio_request(gpioKey[i], gpioName);
		if(ret < 0) {
			printk("Failed Request gpio%d error\n", 6);
			return ret;
		}
	}
	for(i=0;i<GPIOKEYCNT;i++)
	{
		ret = gpio_direction_input(gpioKey[i]);
		if(ret < 0) {
			printk("Failed direction_output gpio%d error\n", 6);
       	 return ret;
		}
	}
	return ret;
}
static int	gpioKeyGet(void) 
{
	int i;
	int ret;
	int keyData=0;
	for(i=0;i<GPIOKEYCNT;i++)
	{
		ret=gpio_get_value(gpioKey[i]) << i;
		keyData |= ret;
	}
	return keyData;
}
static void gpioKeyFree(void) 
{
	int i;
	for(i=0;i<GPIOKEYCNT;i++)
	{
		gpio_free(gpioKey[i]);
	}
}
static int ledkey_open (struct inode *inode, struct file *filp)
{
    int num0 = MAJOR(inode->i_rdev); 
    int num1 = MINOR(inode->i_rdev); 
    printk( "call open -> major : %d\n", num0 );
    printk( "call open -> minor : %d\n", num1 );
	try_module_get(THIS_MODULE);

    return 0;
}

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	char kbuf;
	int ret;
	kbuf = gpioKeyGet();
//  put_user(kbuf,buf);
    ret=copy_to_user(buf,&kbuf,count);
	if (ret != 0) {
    	return -EFAULT;
    }
    return count;
}

static ssize_t ledkey_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	char kbuf;
	int ret;
//  get_user(kbuf,buf);
    ret=copy_from_user(&kbuf,buf,count);
	if (ret != 0) {
        return -EFAULT;
    }
    gpioLedSet(kbuf);

    return count;
//	return -EFAULT;
}

static long ledkey_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{

	ioctl_test_info ctrl_info = {0,{0}};
	int err=0, size;
	if( _IOC_TYPE( cmd ) != IOCTLTEST_MAGIC ) return -EINVAL;
	if( _IOC_NR( cmd ) >= IOCTLTEST_MAXNR ) return -EINVAL;

	size = _IOC_SIZE( cmd );
	if( size )
	{
		if( _IOC_DIR( cmd ) & _IOC_READ )
			err = access_ok( (void *) arg, size );
		if( _IOC_DIR( cmd ) & _IOC_WRITE )
			err = access_ok( (void *) arg, size );
		if( !err ) return err;
	}
	switch( cmd )
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
		case IOCTLTEST_LEDON :
			gpioLedSet(255);
			break;
		case IOCTLTEST_LEDONOFF :
			gpioLedSet(255);
			mdelay(500);
			gpioLedSet(0);
			break;
		case IOCTLTEST_GETSTATE :
			buf = gpioKeyGet();
			return buf;
		case IOCTLTEST_READ :
  			ctrl_info.buff[0] = gpioKeyGet();
			if(ctrl_info.buff[0] != 0)
				ctrl_info.size=1;
			err = copy_to_user((void *)arg,(const void *)&ctrl_info,size);
			if (err != 0) {
    			return -EFAULT;
    		}
			break;

		case IOCTLTEST_WRITE :
			err = copy_from_user((void *)&ctrl_info,(void *)arg,size);
			if (err != 0) {
        		return -EFAULT;
    		}
			if(ctrl_info.size == 1)
				gpioLedSet(ctrl_info.buff[0]);
			break;
		case IOCTLTEST_WRITE_READ :
			err = copy_from_user((void *)&ctrl_info,(void *)arg,size);
			if (err != 0) {
        		return -EFAULT;
    		}
			if(ctrl_info.size == 1)
				gpioLedSet(ctrl_info.buff[0]);

  			ctrl_info.buff[0] = gpioKeyGet();
			if(ctrl_info.buff[0] != 0)
				ctrl_info.size=1;
			else
				ctrl_info.size=0;

			err = copy_to_user((void *)arg,(const void *)&ctrl_info,size);
			if (err != 0) {
        		return -EFAULT;
    		}
			break;
		default:
			err =-E2BIG;
			break;
	}	
	return err;
}

static int ledkey_release (struct inode *inode, struct file *filp)
{
    printk( "call release \n" );
	module_put(THIS_MODULE);
	if(gpio_is_valid(gpioLed[0]))
    	gpioLedFree();
	if(gpio_is_valid(gpioKey[0]))
    	gpioKeyFree();
    return 0;
}

struct file_operations ledkey_fops =
{
//    .owner    = THIS_MODULE,
    .read     = ledkey_read,     
    .write    = ledkey_write,    
	.unlocked_ioctl = ledkey_ioctl,
    .open     = ledkey_open,     
    .release  = ledkey_release,  
};

static int ledkey_init(void)
{
    int result;

    printk( "call ledkey_init \n" );    

    result = register_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME, &ledkey_fops);
    if (result < 0) return result;

//	gpioLedInit();
//	gpioKeyInit();
    return 0;
}

static void ledkey_exit(void)
{
    printk( "call ledkey_exit \n" );    
    unregister_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME );
//	gpioLedFree();
//	gpioKeyFree();
}

module_init(ledkey_init);
module_exit(ledkey_exit);

MODULE_AUTHOR("KCCI-AIOT KSH");
MODULE_DESCRIPTION("led key test module");
MODULE_LICENSE("Dual BSD/GPL");
