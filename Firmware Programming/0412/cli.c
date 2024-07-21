/*
 * cli.c
 *
 *  Created on: Apr 12, 2024
 *      Author: IOT
 */

// Comand line interface
// 텍스트 기반의 동작 인터페이스

#include <stdio.h>
#include <stdlib.h>		// stdtol용
#include <string.h>
#include "uart.h"
#include "cli.h"
#include "led.h"


typedef struct{
	char *cmd;					// 명령어
	uint8_t no;					// 입력받을 argument 수
	int (*cbf)(int, char**);	// int argc, char *argv[]
	char *remark;				// 설명
}CMD_LIST_T;


static int cli_led(int argc, char*argv[]);
static int cli_echo(int argc, char*argv[]);
static int cli_help(int argc, char*argv[]);
static int cli_mode(int argc, char *argv[]);


const CMD_LIST_T gCmdListObjs[]={
		{ "mode",	2,	cli_mode,	"mode [0/1]: change app mode"	},
		{ "led", 	3,	cli_led,	"led [1/2/3] [on/off]"},
		{ "echo",	2,	cli_echo,	"echo [echo data]"},
		{ "help",	1,	cli_help, 	"help"},
		{ NULL,  	0,	NULL, 		NULL}
};



static int cli_mode(int argc, char *argv[])
{
	if (argc < 2) {
		printf("\nError: Need more argument\r\n");
		return -1;
	}

	long mode = strtol(argv[1], NULL, 10);
	app_mode((int)mode);

	return 0;
}


static int cli_led(int argc, char*argv[]){
	// on은 0, off는 1으로 넘어옴
	if(argc < 3){
		printf("\nError: Need more argument\r\n");
		return -1;
	}

	long no = strtol(argv[1], NULL, 10);		// strtol(바꿀문자열, 문자열로 반환시, 진수)
	int onoff = strcmp(argv[2], "off");

	if (onoff != 0) onoff = 1;

	printf("\nled %ld, %d\r\n", no, onoff);
	led_onoff(no, onoff);
	// led onoff 관련 함수
	// led_onoff((uint8_y))


	return 0;
}


static int cli_echo(int argc, char*argv[]){
	if(argc < 2){
		printf("\nError: Need more argument\r\n");
		return -1;
	}
	printf("%s\r\n", argv[1]);

	return 0;
}


static int cli_help(int argc, char*argv[]){
	printf("\n-----------\nhelp\n-----------\n");

	for(int i=0;gCmdListObjs[i].cmd != NULL;i++) {
		printf("%s\r\n", gCmdListObjs[i].remark);
	}
	printf("-----------\n");
	return 0;
}


static void cli_parser(void *arg);



void cli_init(){
	uart_regcbf(cli_parser);
}

void cli_thread(void* arg){
	(void)arg;

}

#define D_DELIMITER		" ,\r\n"

//  uart의 call back으로 등록
void cli_parser(void *arg){

	int argc = 0;
	// 각자 잘린 단어를 저장
	char *argv[10];
	char *ptr;

	char *buf = (char *)arg;

	// 출력 확인시 주석
	//printf("\nRX: %s\r\n", (char *)arg);

	// 토큰 분리
	ptr = strtok(buf, D_DELIMITER);
	if (ptr == NULL) return;

	while (ptr != NULL) {
		argv[argc] = ptr;
		argc++;
		ptr = strtok(NULL, D_DELIMITER);
	}

	// 출력 기능 확인시 주석
	//for(int i=0;i<argc;i++){
	//	printf("%d: %s\r\n", i, argv[i]);
	//}

	for (int i=0; gCmdListObjs[i].cmd != NULL; i++) {
		if (strcmp(gCmdListObjs[i].cmd, argv[0]) == 0) {
			gCmdListObjs[i].cbf(argc, argv);
			return;
		}
	}

	printf("Unsupported Command\r\n");
}
