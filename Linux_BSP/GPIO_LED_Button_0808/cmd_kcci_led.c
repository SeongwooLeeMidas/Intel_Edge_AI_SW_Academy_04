#include <vsprintf.h>
#include <command.h>
#include <asm/io.h>
  
#define BCM2711_GPIO_GPFSEL0	0xFE200000
#define BCM2711_GPIO_GPFSEL1	0xFE200004
#define BCM2711_GPIO_GPFSEL2    0xFE200008
#define BCM2711_GPIO_GPSET0     0xFE20001C
#define BCM2711_GPIO_GPCLR0     0xFE200028
#define BCM2711_GPIO_GPLEV0     0xFE200034

#define GPIO6_9_SIG_OUTPUT	0x09240000
#define GPIO10_13_SIG_OUTPUT	0x00012249 //txd, rxd

void led_init(void)
{
	writel(GPIO6_9_SIG_OUTPUT, BCM2711_GPIO_GPFSEL0);
	writel(GPIO10_13_SIG_OUTPUT, BCM2711_GPIO_GPFSEL1);
}
void led_write(unsigned long led_data)
{
	writel(0x3fc0, BCM2711_GPIO_GPCLR0);	//led all off
	led_data = led_data << 6;
	writel(led_data, BCM2711_GPIO_GPSET0); // led X on
}

void key_read(unsigned long *key_data)
{
	*key_data = readl(BCM2711_GPIO_GPLEV0) & 0xFF;
}

static int do_KCCL_LED(struct cmd_tbl *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned long led_data;
	unsigned long key_data;
	unsigned long prev_key_data = 0xFF;
	
	if(argc != 2)
	{
		cmd_usage(cmdtp);
		return 1;
	}
	printf("*LED TEST START\n");
	led_init();
	led_data = simple_strtoul(argv[1], NULL, 16);
	led_write(led_data);

	while(1) {
	key_read(&key_data);

	if (key_data != prev_key_data) {
		for (int i=0; i<8; i++)
	{
		if (key_data & (1 << i))
		{
			printf("O:");
		}
		else
		{
			printf("X:");
		}
	}
	printf("\n");

	prev_key_data = key_data;
   }

	if (key_data & (1 << 7)) {
		break;
	}
   }

	printf("*LED TEST END(%s : %#04x)\n\n", argv[0], (unsigned int)led_data);
	return 0;
}
U_BOOT_CMD(
	led, 2, 0, do_KCCL_LED,
	"led - kcci LED Test.",
	"number - Input argument is only one. (led [0x00~0xff])\n");
