#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	char buffer[4096];
	struct sockaddr_in destaddr;
	bzero(&destaddr,sizeof(destaddr));
	destaddr.sin_family=AF_INET;
	destaddr.sin_port=htons(8888);
	inet_pton(AF_INET,"127.0.0.1",&destaddr.sin_addr.s_addr);

	int sockfd;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if((connect(sockfd,(struct sockaddr*)&destaddr,sizeof(destaddr)))==-1)
	{
		perror("connect call failed");
		exit(0);
	}
	printf("connect success\n");

	bzero(buffer,sizeof(buffer));
	printf("input msg:");
	scanf("%s",buffer);
	send(sockfd,buffer,strlen(buffer),0);

	bzero(buffer,sizeof(buffer));
	recv(sockfd,buffer,sizeof(buffer),0);
	printf("client recv response =%s\n",buffer);

	close(sockfd);
	return 0;
}
