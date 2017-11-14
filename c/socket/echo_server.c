#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_BUF 1024 // same as the client.
#define SERVER_PORT 9900
#define BACK_LOG 5
#define MAX_THREAD 1024

void* t_func(void* arg) {
	int client_sockfd  = *(int*)arg;	
	char buf[MAX_BUF] = {0, };
	int	size = 0;

	while (1) {
		memset(buf, 0, sizeof(buf));

		if ((size = read(client_sockfd, buf, sizeof(buf))) <= 0) {
			if (size == 0) {
				printf("closed client: %d\n", client_sockfd);
			} else {
				perror("read fail");
			}
			close(client_sockfd);
			break;
		}

		printf("received message: %d -> %s", client_sockfd, buf);
	
		if (write(client_sockfd, buf, sizeof(buf)) <= 0) {
			perror("write fail");
			close(client_sockfd);
			break;
		}
	}
}

int main(int argc, const char** argv) {
	int server_sockfd, client_sockfd;
	struct sockaddr_in server_addr, client_addr;
	int client_len;
	pthread_t threads[MAX_THREAD] = {0, };

	if ((server_sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket fail");
		return 1;
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);

	if (bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		perror("bind fail");
		return 1;
	}

	if (listen(server_sockfd, BACK_LOG) == -1) {
		perror("listen fail");
		return 1;
	}	

	printf("echo server is running at %d\n", SERVER_PORT);

	int count = 0;
	while (1) {
		if ((client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &client_len)) < 0) {
			perror("accept fail");
			continue;
		}

		printf("accepted client: %d -> %s, %d\n", client_sockfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));		

		pthread_create(&threads[count++], NULL, t_func, (void*)&client_sockfd);		
	}

	close(server_sockfd);

	int i;
	for (i = 0; i < count; i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}

