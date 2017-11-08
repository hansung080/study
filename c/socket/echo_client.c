#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUF 1024 // same as the server
#define SERVER_PORT 9990
#define STD_IN 0

int main(int argc, const char** argv) {
	int sockfd;
	struct sockaddr_in server_addr;

	char buf[MAX_BUF];

	if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket failed");
		return 1;
	}

	memset(&server_addr, 0, sizeof(server_addr));	
	server_addr.sin_family = PF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	server_addr.sin_port = htons(SERVER_PORT);

	if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		perror("connect failed");
		return 1;
	}

	while (1) {	
		memset(buf, 0, sizeof(buf));
		read(STD_IN, buf, MAX_BUF);
		if (strncmp(buf, "quit", 4) == 0) {
			printf("good bye...\n");
			return 0;
		}

		if (write(sockfd, buf, sizeof(buf)) <= 0) {
			perror("write failed");
			return 1;
		}

		memset(buf, 0, sizeof(buf));
		if (read(sockfd, buf, sizeof(buf)) <= 0) {
			perror("read failed");
			return 1;
		}

		printf("echo: %s\n", buf);
	}	

	close(sockfd);

	return 0;
}

