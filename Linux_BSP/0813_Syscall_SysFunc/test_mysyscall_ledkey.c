#include <linux/kernel.h>
#include <linux/gpio.h>
 
#define OFF 0
#define ON 1

int gpioLed[] = {6,7,8,9,10,11,12,13};
int gpioKey[] = {16,17,18,19,20,21,22,23};
asmlinkage long sys_mysyscall(long val)
{
//	printk(KERN_INFO "Welcome to ~ val : %ld\n",val);
//	return val * val;
	unsigned long keyData=0;
	unsigned long temp;
	int ret = 0;
	int i;
	int gpioCnt = sizeof(gpioLed)/sizeof(gpioLed[0] );
	for(i=0;i<gpioCnt;i++)
	{
		ret = gpio_request(gpioLed[i],"led0");
		if(ret < 0) {
			printk("Failed request gpio%d error\n",6);
			return ret;
		}
	}
	for(i=0;i<gpioCnt;i++)
	{
		ret = gpio_direction_output(gpioLed[i],OFF);
		if(ret < 0) {
			printk("Failed direction_output gpio%d error\n",6);
			return ret;
		}
	}
	for(i=0;i<gpioCnt;i++)
	{
		gpio_set_value(gpioLed[i],(val>>i) & 0x1);
	}

	for(i=0;i<gpioCnt;i++)
	{
  		gpio_free(gpioLed[i]);
	}



	gpioCnt = sizeof(gpioKey)/sizeof(gpioKey[0] );
	for(i=0;i<gpioCnt;i++)
	{
		ret = gpio_request(gpioKey[i],"key0");
		if(ret < 0) {
			printk("Failed request gpio%d error\n",6);
			return ret;
		}
	}
	for(i=0;i<gpioCnt;i++)
	{
		ret = gpio_direction_input(gpioKey[i]);
		if(ret < 0) {
			printk("Failed direction_output gpio%d error\n",6);
			return ret;
		}
	}
	for(i=0;i<gpioCnt;i++)
	{
		temp = gpio_get_value(gpioKey[i]) << i;
		keyData |= temp;
	}

	for(i=0;i<gpioCnt;i++)
	{
  		gpio_free(gpioKey[i]);
	}


	return keyData;
}
