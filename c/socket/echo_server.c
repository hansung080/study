#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUF 1024 // same as the client.
#define SERVER_PORT 9990
#define BACK_LOG 5

int main(int argc, const char** argv) {
	int server_sockfd, client_sockfd;
	struct sockaddr_in server_addr, client_addr;
	int client_len;
	char buf[MAX_BUF];

	if ((server_sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket failed");
		return 1;
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);

	if (bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		perror("bind failed");
		return 1;
	}

	if (listen(server_sockfd, BACK_LOG) == -1) {
		perror("listen failed");
		return 1;
	}	

	printf("server is running at %d\n", SERVER_PORT);

	while (1) {
		memset(buf, 0, sizeof(buf));

		if ((client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &client_len)) < 0) {
			perror("accept failed");
			continue;
		}

		printf("accept client: %s\n", inet_ntoa(client_addr.sin_addr));		

		if (read(client_sockfd, buf, sizeof(buf)) <= 0) {
			close(client_sockfd);
			continue;
		}
		
		if (write(client_sockfd, buf, sizeof(buf)) <= 0) {
			perror("write failed");
			close(client_sockfd);
		}
		
		close(client_sockfd);

	}

	close(server_sockfd);

	return 0;
}

