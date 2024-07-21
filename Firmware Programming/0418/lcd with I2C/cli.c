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
#include "type.h"
#include "uart.h"
#include "app.h"
#include "tim.h"
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

extern UART_HandleTypeDef huart2;
static int cli_btn_uart(int argc, char *argv[])
{
	if (argc < 2) {
		printf("\nError: Need more argument\r\n");
		return -1;
	}
	uint8_t encored[1];
	uint16_t encodedLength = 0;

	slip_encode((uint8_t*)&argv[1][0], 1, encored, &encodedLength);

	HAL_UART_Transmit(&huart2, encored, encodedLength, 0xffff);
	printf("cli_button: %c\r\n", argv[1][0]);
	HAL_Delay(100);

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

static int cli_echo(int argc, char *argv[]){

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


static void cli_parser(uint8_t *arg);
//static void cli_event_set(void *arg);
void cli_msg_put(void *arg);


//static BUF_T gBufObj[1];

void cli_thread(void* arg){

	//uint32_t flags;
	(void)arg;
	osStatus sts;
	MSG_T rxMsg, txMsg;

	osDelay(1000);

	txMsg.id = E_MSG_CLI_INIT;
	osMessageQueuePut(cli_msg_id, &txMsg, 0, osWaitForever);

	while (1) {
		sts = osMessageQueueGet(cli_msg_id, &rxMsg, NULL, osWaitForever);

		if (sts == osOK) {
			switch (rxMsg.id) {
			case E_MSG_CLI:{
				MEM_T *pMem = (MEM_T *)rxMsg.body.vPtr;
				PKT_T *pRxPkt = (PKT_T *)pMem->buf;
				cli_parser(pRxPkt->ctx);

				mem_free(pMem);
			} break;

			case E_MSG_CLI_INIT:{
				printf("CLI Thread Started...\r\n");
//					printf("Sizeof(MSG_T)=%d\r\n", sizeof(MSG_T));
//					MEM_T *p = NULL;
//
//					p = mem_alloc(10, 0);
//					if (p != NULL) {
//						sprintf((char *)p->buf, "%s", "12345678");
//						printf((char *)p->buf);
//						mem_free(p);
//					}
//
//					uart_regcbf(E_UART_1, cli_msg_put);
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
		printf("CLI Message Queue  Create File...\r\n");
		while (1);
	}

	cli_thread_hnd = osThreadNew(cli_thread, NULL, &cli_thread_attr);
	if (cli_thread_hnd != NULL) printf("CLI Thread Created...\r\n");
	else {
		printf("CLI Thread Create Fail...\r\n");
		while (1);
	}
}

// ISR
void cli_msg_put(void *arg){

	Q_PUT(cli_msg_id, E_MSG_CLI, arg, 0);
}


#define D_DELIMITER		" ,\r\n"

//  uart의 call back으로 등록
static void cli_parser(uint8_t *arg){

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
//	for (int i=0; i<argc; i++) {
//		printf("%d:%s\r\n", i, argv[i]);
//	}

	for (int i=0; gCmdListObjs[i].cmd != NULL; i++) {
		if (strcmp(gCmdListObjs[i].cmd, argv[0]) == 0) {
			gCmdListObjs[i].cbf(argc, argv);
			return;
		}
	}

	// 여기까지 나왔다는 것은 일치하는 명령어가 없었다는 뜻
	printf("Unsupported Command\r\n");
}
