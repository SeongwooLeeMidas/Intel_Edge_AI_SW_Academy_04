#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int fatal(char *s);
int main (void)
{
		pid_t pid;
		int status;
		char *argv[] = {"ls", "-1", NULL};
		system("ls -l");
		switch (pid = fork()){
		case -1:
			fatal("fork failed.\n");
			break;
		case 0: // 자식 프로세스
//			sleep(10);
//			execl("/bin/ls", "ls", "-1",NULL); // 자식이 exec 호출
//			execlp("ls", "ls", "-1",NULL); 
			execv("/bin/ls", argv); 
			fatal("exec failed.\n");
			break;
		default: // 부모 프로세스
			printf("child pid: %d\n", pid);
//			wait((int *)0); // 부모는 자식이 종료될 때까지 대기
			wait(&status);
			printf("ls completed %d\n", status>>8);
			exit(0);
		}
}

int fatal(char *s)
{
		perror(s);
		exit(1);
}
