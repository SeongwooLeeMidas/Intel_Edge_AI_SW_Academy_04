#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void error_handling(char *message);

int main(int argc, char* argv[])
{
		int sock;
		struct sockaddr_in serv_addr;
		char message[100];
		int str_len;
		int in;

		if(argc!=4){
				printf("Usage : %s <IP> <port> <file>\n", argv[0]);
				exit(1);
		}
		/* 복사의 원본이 되는 파일을 읽기 모드로 연다. */
		if ((in = open(argv[3], O_RDONLY)) < 0) {
				perror(argv[1]);
				return 2;
		}

		sock=socket(PF_INET, SOCK_STREAM, 0);
		if(sock < 0)
				error_handling("socket() error");

		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family=AF_INET;
		serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
		serv_addr.sin_port=htons(atoi(argv[2]));

		if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
				error_handling("connect() error!");

		do
		{
				str_len = read(in, message, sizeof(message));
				printf("str_len : %d\n", str_len);
				if(str_len > 0)
						write(sock, message, str_len);
				else if(str_len == 0)
						break;
				else
				{
						perror("read");
						break;
				}
		}while(1);


/*		str_len=read(sock, message, sizeof(message)-1);
		if(str_len < 0)
				error_handling("read() error!");

		printf("Message from server: %s(%d) \n", message, str_len);
*/
		fputs("Done ...",stdout);
		close(sock);
		return 0;
}

void error_handling(char *message)
{
		fputs(message, stderr);
		fputc('\n', stderr);
		exit(1);
}
