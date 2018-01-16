#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_THREAD 2

pthread_mutex_t mutex;

void increase(int* count) {
	pthread_mutex_lock(&mutex);
	int tmp = *count;
	tmp++;
	sleep(1); // sleep to cause a race condition.
	*count = tmp;
	pthread_mutex_unlock(&mutex);
}

void* t_func(void* data) {
	int* count = (int*)data;
	pthread_t thread_id = pthread_self();

	while (1) {
		increase(count);
		printf("worker thread : %lu, %d\n", thread_id, *count);
		sleep(1);
	}
}

int main(int argc, const char** argv) {
	pthread_t thread_ids[MAX_THREAD];
	int i = 0;
	int count = 0;

	if (pthread_mutex_init(&mutex, NULL) != 0) {
		perror("mutex init failed.");
		return 1;
	}

	for (i = 0; i < MAX_THREAD; i++) {
		pthread_create(&thread_ids[i], NULL, t_func, (void*)&count);
		usleep(5000);
	}

	pthread_t main_thread_id = pthread_self();
	while (1) {
		increase(&count);
		printf("main thread   : %lu, %d\n", main_thread_id, count);
		sleep(2);
	}

	for (i = 0; i < MAX_THREAD; i++) {
		pthread_join(thread_ids[i], NULL);	
	}

	return 0;
}

