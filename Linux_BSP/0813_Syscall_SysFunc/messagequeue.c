#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

// 메세지 타입을 설정하는 부분
typedef struct msgbuf { 
        long type;
        char text[50];
} MsgBuf;

int main(void) {
        int msgid, len;
        MsgBuf msg;
        key_t key = 1234;
        msgid = msgget(key, IPC_CREAT|0644); // 메세지 큐 생성 

        if(msgid == -1) { // 메세지 큐가 생성이 안된 경우
                perror("msgget");
                exit(1);
        }

        msg.type = 1;
        strcpy(msg.text, "Hello Message Queue!\n");

        if(msgsnd(msgid, (void *)&msg, 50, IPC_NOWAIT) == -1) { // 메세지 큐 전송 실패
                perror("msgsnd");
                exit(1);
        }
        return 0;
}
