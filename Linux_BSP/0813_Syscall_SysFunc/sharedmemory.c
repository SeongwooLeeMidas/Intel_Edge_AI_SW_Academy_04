#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
        int shmid, pid;
        char *shmaddr_parent, *shmaddr_child; // 공유 메모리 영역을 할당할 포인터 변수
        shmid = shmget((key_t)1234, 100, IPC_CREAT|0664); // 키값 생성
        if(shmid == -1) {
                perror("shmget error\n");
                exit(1);
        }

        pid = fork(); // 자식 프로세스 생성
        if(pid > 0) { // 2.부모 프로세스
                wait(0); // 자식 프로세스의 exit() 호출까지 대기
                shmaddr_parent = (char *)shmat(shmid, (char *)NULL, 0);
                printf("%s\n", shmaddr_parent); // 공유 메모리 값을 읽음(read)
                shmdt((char *)shmaddr_parent);
        }
        else { // 1.자식 프로세스
                shmaddr_child = (char *)shmat(shmid, (char *)NULL, 0); // 공유 메모리 키를 변수에 매핑
                strcpy((char *)shmaddr_child, "Hello Parent!"); // 공유 메모리에 쓰기(write)
                shmdt((char *)shmaddr_child); // 포인터 변수를 공유 메모리에서 해제
				sleep(10);
                exit(0);
        }
        shmctl(shmid, IPC_RMID, (struct shmid_ds *)NULL); // 공유메모리를 커널영역에서 삭제
        return 0;
}
