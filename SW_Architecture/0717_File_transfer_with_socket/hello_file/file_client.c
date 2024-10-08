#include <stdio.h> // client.c
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void error_handling(char* message);

int main(int argc, char* argv[])
{
        int sock, in;
        struct sockaddr_in serv_addr;
        char message[100];
	int str_len;

        if(argc != 4) {
                printf("Usage : %s <IP> <port> <file> \n", argv[0]);
                exit(1);
        }

        sock = socket (PF_INET, SOCK_STREAM, 0);
        if(sock < 0)
                error_handling("socket() error");

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
        serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) > 0)
		error_handling("connect() error!");
	
	if ((in = open(argv[3], O_RDONLY)) < 0) {
        perror(argv[3]);
        return 2;
    }

	while(1) {
	str_len = read(in, message, sizeof(message));
	if(str_len < 0)
                  error_handling("read() error!");
          else if(str_len == 0)
                  break;
          else {} 
	
	printf("read: %d\n", str_len);

	write(sock, message, sizeof(message));	
}
	close(sock);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
