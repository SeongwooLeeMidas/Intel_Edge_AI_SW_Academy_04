#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <asm-generic/unistd.h>
#pragma GCC diagnostic ignored "-Wunused-result"
int main(int argc, char *argv[])
{
	int val=0, key_data,key_data_old=0;
	int i;
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
	do {
		usleep(100000);  //100MSec
		key_data = syscall(__NR_mysyscall,val);
		if(key_data < 0)
		{
			printf("key_data : %d\n",key_data);
			perror("syscall()");
		}
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
			}
			if(key_data == 0x80)
				break;
		}
	}while(1);
    	printf("mysyscall return value = %#04x\n",key_data);
    	return 0;
}
