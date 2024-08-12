#include <linux/kernel.h>
#include <linux/gpio.h>

#define OFF 0
#define ON 1
#define GPIOCNT 8

int gpioLed[] = {6,7,8,9,10,11,12,13};
long sys_mysyscall(long val)
{
	int ret;
	int i;
	char gpioName[10];
//	int gpioCnt = sizeof(gpioLed)/sizeof(gpioLed[0]));
	printk(KERN_INFO "Welcome ~ app value=%ld\n",val);
		
	for(i=0;i<GPIOCNT;i++)
	{
		sprintf(gpioName,"gpio%d",gpioLed[i]);
		ret = gpio_request(gpioLed[i],gpioName);
		if(ret < 0) {
			printk("Failed request gpio%d error\n",gpioLed[i]);
			return ret;
		}
	}

	for(i=0;i<GPIOCNT;i++)
	{
		ret = gpio_direction_output(gpioLed[i],OFF);	
		if(ret < 0) {
			printk("Failed direction gpio%d error\n",gpioLed[i]);
			return ret;
		}

	}
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_set_value(gpioLed[i],val & (0x01 << i));	
	}

	for(i=0;i<GPIOCNT;i++)
	{
		gpio_free(gpioLed[i]);
	}
	return val;
}
