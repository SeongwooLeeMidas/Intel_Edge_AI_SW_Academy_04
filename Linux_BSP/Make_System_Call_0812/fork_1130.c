#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int fatal(char *s);
int main (void)
{
		pid_t pid;
		switch (pid = fork()){
		case -1:
			fatal("fork failed.\n");
			break;
		case 0: // 자식 프로세스
			execl("/bin/ls", "ls", "-1",NULL); // 자식이 exec 호출
			fatal("exec failed.\n");
			break;
		default: // 부모 프로세스
			wait((int *)0); // 부모는 자식이 종료될 때까지 대기
			printf("ls completed\n");
			exit(0);
		}
}

int fatal(char *s)
{
		perror(s);
		exit(1);
}
