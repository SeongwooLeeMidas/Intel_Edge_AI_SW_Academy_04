#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#pragma GCC diagnostic ignored "-Wunused-result"

#define DEVICE_FILENAME  "/dev/calldev"

int main(int argc, char *argv[])
{
	char val=0, key_data,key_data_old=0;
	int i;
	int dev;
	int ret;
	if(argc < 2)
	{
		printf("USAGE : %s ledVal[0x00~0xff]\n",argv[0]);
		return 1;
	}
//	printf("input value = ");
//	scanf("%x",&val);
	val = strtoul(argv[1],NULL,16);
    if(val<0 || 0xff<val)
    {
   		printf("Usage : %s ledValue(0x00~0xff)\n",argv[0]);
       	return 2;
    }
	dev = open( DEVICE_FILENAME, O_RDWR|O_NDELAY );
	if( dev < 0 )
    {
        perror("open");
        return 1;
    }

	write(dev,&val,sizeof(val));
	do {
		usleep(100000);  //100MSec
//		key_data = syscall(__NR_mysyscall,val);
		ret = read(dev, &key_data, sizeof(key_data));
		if(ret < 0)
		{
        	perror("read");
        	return 2;
		}
//		printf("key_data : %d\n",key_data);
//		perror("syscall()");
		if(key_data != key_data_old)
		{
			key_data_old = key_data;
			if(key_data)
			{
				val = key_data;
				puts("0:1:2:3:4:5:6:7");
				for(i=0;i<8;i++)
				{
					if(key_data & (0x01 << i))
						putchar('O');
					else
						putchar('X');
					if(i != 7 )
						putchar(':');
					else
						putchar('\n');
				}
				putchar('\n');
				write(dev,&key_data,sizeof(key_data));
			}
			if(key_data == 0x80)
				break;
		}
	}while(1);
	close(dev);
//   	printf("mysyscall return value = %#04x\n",key_data);
   	return 0;
}
