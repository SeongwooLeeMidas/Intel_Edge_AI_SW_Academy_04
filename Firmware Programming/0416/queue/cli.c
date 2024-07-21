/*
 * cli.c
 *
 *  Created on: Apr 12, 2024
 *      Author: IOT
 */

// Comand line interface
// 텍스트 기반의 동작 인터페이스

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include "uart.h"
#include "app.h"
//#include "tim.h"
#include "button.h"
#include "type.h"
#include "led.h"
#include "cli.h"


typedef struct{
	char *cmd;					// 명령어
	uint8_t no;					// 입력받을 argument 수
	int (*cbf)(int, char**);	// int argc, char *argv[]
	char *remark;				// 설명
}CMD_LIST_T;

static osThreadId_t cli_thread_hnd;			// 쓰레드 핸들
//static osEventFlagsId_t cli_evt_id;		// 이벤트 플래그 핸들
static osMessageQueueId_t cli_msg_id;  		// 메시지 큐 

static const osThreadAttr_t cli_thread_attr = {
  .stack_size = 128 * 8,
  .priority = (osPriority_t) osPriorityNormal,
};


static int cli_led(int argc, char*argv[]);
static int cli_echo(int argc, char*argv[]);
static int cli_help(int argc, char*argv[]);
static int cli_mode(int argc, char *argv[]);
static int cli_btn_uart(int argc, char *argv[]);


const CMD_LIST_T gCmdListObjs[]={
		{ "help",	1,	cli_help, 		"help"},
		{ "mode",	2,	cli_mode,		"mode [0/1]: change app mode"	},
		{ "led", 	3,	cli_led,		"led [1/2/3] [on/off]"},
		{ "echo",	2,	cli_echo,		"echo [echo data]"},
		{ "btn",	2,	cli_btn_uart,	"button(uart)\r\n- btn ['a'~'Z']"},
		{ NULL,  	0,	NULL, 			NULL}
};


//extern UART_HandleTypeDef huart2;		// idx = 0
static int cli_btn_uart(int argc, char *argv[])
{
	if (argc < 2) {
		printf("\nError: Need more argument\r\n");
		return -1;
	}
	//HAL_UART_Transmit(&huart2, (uint8_t*)&argv[1][0], 1, 0xffff);
	printf("cli_button: %c\r\n", argv[1][0]);

	return 0;
}

static int cli_mode(int argc, char *argv[])
{
	if (argc < 2) {
		printf("\nError: Need more argument\r\n");
		return -1;
	}

	//long mode = strtol(argv[1], NULL, 10);
	//app_mode((int)mode);

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
	//bool sts = onoff ? true : false;

	printf("led %ld, %d\r\n", no, onoff);
	// led onoff 관련 함수
	//led_onoff((uint8_t)no, sts);


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


static void cli_parser(BUF_T *arg);
//static void cli_event_set(void *arg);
static void cli_msg_put(void *arg);


static BUF_T gBufObj[1];

void cli_thread(void* arg){

	//uint32_t flags;
	(void)arg;
	osStatus sts;
	MSG_T rxMsg, txMsg;

	txMsg.id = E_MSG_CLI_INIT;
	osMessageQueuePut(cli_msg_id, &txMsg, 0, osWaitForever);

	while (1) {
		sts = osMessageQueueGet(cli_msg_id, &rxMsg, NULL, osWaitForever);

		if(sts == osOK){
			// 메세지의 구분을 위한 switch
			switch(rxMsg.id){
			case E_MSG_CLI:{
				cli_parser((BUF_T *)rxMsg.body.vPtr);
			} break;

			case E_MSG_CLI_INIT:{
				printf("CLI Thread Started\r\n");
				printf("Sizeof(MSG_T) = %d\r\n", sizeof(MSG_T));
				uart_regcbf(E_UART_1, cli_msg_put);
			} break;


			}
		}
	}
}

void cli_init(void)
{
	//cli_evt_id = osEventFlagsNew(NULL);
	cli_msg_id = osMessageQueueNew(3, sizeof(MSG_T), NULL);

	if (cli_msg_id != NULL) printf("CLI Message Queue Created...\r\n");
	else {
		printf("CLI Message Queue Create Fail...\r\n");
		while (1);
	}

	cli_thread_hnd = osThreadNew(cli_thread, NULL, &cli_thread_attr);
	if (cli_thread_hnd != NULL) printf("CLI Thread Created...\r\n");
	else {
		printf("CLI Thread Create Fail...\r\n");
		while (1);
	}
}



//static void cli_event_set(void *arg){
//
//	BUF_T *pBuf = (BUF_T*)arg;
//
//	memcpy(&gBufObj[0], pBuf, sizeof(BUF_T));
//
//	osEventFlagsSet(cli_evt_id, 0x0001);
//}


// ISR
static void cli_msg_put(void *arg){

	BUF_T *pBuf = (BUF_T*)arg;

	memcpy(&gBufObj[0], pBuf, sizeof(BUF_T));

	MSG_T txMsg;
	txMsg.id = E_MSG_CLI;
	txMsg.body.vPtr = (void*)&gBufObj[0];
	osMessageQueuePut(cli_msg_id, &txMsg, 0, 0);
}



#define D_DELIMITER		" ,\r\n"

//  uart의 call back으로 등록
static void cli_parser(BUF_T *arg){

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

	// 여기까지 나왔다는 것은 일치하는 명령어가 없었다는 뜻
	printf("Unsupported Command\r\n");
}
