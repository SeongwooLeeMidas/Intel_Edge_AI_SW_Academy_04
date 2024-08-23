#ifndef __IOCTL_H__
#define __IOCTL_H__

#define IOCTLTEST_MAGIC '6' 
typedef struct
{
	unsigned long timer_val;
} __attribute__((packed)) keyled_data;

#define IOCTLTEST_KEYLEDINIT 	_IO(IOCTLTEST_MAGIC, 0) 
#define IOCTLTEST_KEYLEDFREE 	_IO(IOCTLTEST_MAGIC, 1)
#define IOCTLTEST_LEDOFF		_IO(IOCTLTEST_MAGIC, 2)
#define IOCTLTEST_LEDON			_IO(IOCTLTEST_MAGIC, 3)
#define IOCTLTEST_GETSTATE		_IO(IOCTLTEST_MAGIC, 4)
#define IOCTLTEST_READ			_IOR(IOCTLTEST_MAGIC, 5,keyled_data)
#define IOCTLTEST_WRITE			_IOW(IOCTLTEST_MAGIC, 6,keyled_data)
#define IOCTLTEST_WRITE_READ	_IOWR(IOCTLTEST_MAGIC, 7,keyled_data)
#define IOCTLTEST_KEYINIT 		_IO(IOCTLTEST_MAGIC, 8) 
#define IOCTLTEST_LEDINIT 		_IO(IOCTLTEST_MAGIC, 9) 

#define TIMER_START             _IO(IOCTLTEST_MAGIC, 11)
#define TIMER_STOP              _IO(IOCTLTEST_MAGIC, 12)
#define TIMER_VALUE             _IOW(IOCTLTEST_MAGIC, 13, keyled_data)

#define IOCTLTEST_MAXNR         14

#endif
