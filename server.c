#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8888

int main(void)
{
	int servfd, connfd;
	struct sockaddr_in serv_addr;
	char buf[1024];
	int n;

	servfd = socket(AF_INET, SOCK_STREAM, 0);
	if (servfd < 0) {
		perror("socket");
		exit(1);
	}
	int opt = 1;
	setsockopt(servfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(servfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("bind");
		close(servfd);
		exit(1);
	}
	if (listen(servfd, 3) < 0) {							
		perror("listen");		
		close(servfd);
		exit(1);
	}
	printf("server ready, wait connect...\n");
					
	while (1)
	{
		connfd = accept(servfd, NULL, NULL);
		if (connfd < 0) continue;

		bzero(buf, sizeof(buf));
		n = read(connfd, buf, sizeof(buf)-1);
		if (n > 0)
		{
			printf("server recv: %s\n", buf);  // 新加这句！服务端打印收到的数据
			write(connfd, buf, n);
		}
		close(connfd);
	}
	close(servfd);
	return 0;
}
