#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUF 1024 // same as the server
#define SERVER_PORT 9900
#define STD_IN 0

int main(int argc, const char** argv) {
	int sockfd;
	struct sockaddr_in server_addr;

	char buf[MAX_BUF];

	if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket fail");
		return 1;
	}

	memset(&server_addr, 0, sizeof(server_addr));	
	server_addr.sin_family = PF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	server_addr.sin_port = htons(SERVER_PORT);

	if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		perror("connect fail");
		return 1;
	}

	while (1) {	
		printf("input: ");
		memset(buf, 0, sizeof(buf));
		//read(STD_IN, buf, sizeof(buf));
		fgets(buf, sizeof(buf), stdin);
		if (strncmp(buf, "quit", 4) == 0) {
			printf("good bye...\n");
			return 0;
		}

		if (write(sockfd, buf, sizeof(buf)) <= 0) {
			perror("write fail");
			return 1;
		}

		memset(buf, 0, sizeof(buf));
		if (read(sockfd, buf, sizeof(buf)) <= 0) {
			perror("read fail");
			return 1;
		}

		printf("echo: %s\n", buf);
	}	

	close(sockfd);

	return 0;
}

