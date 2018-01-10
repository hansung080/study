#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ARRAY_SIZE 100
#define THREAD_NUM 4

pthread_mutex_t mutex;
pthread_cond_t cond;

int* datas;
int sums[THREAD_NUM];

struct data {
	int* arr; // start address of datas array
	int idx; // thread index
};

void* t_func(void* arg) {
	struct data data;
	int i = 0;
	int sum = 0;
	data = *(struct data*)arg;

	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond, &mutex);
	pthread_mutex_unlock(&mutex);

	for (i = 0; i < 25; i++) {
		sum += data.arr[data.idx * 25 + i];
	}

	printf("thread sum: %d, %d\n", data.idx, sum);
	sums[data.idx] = sum;
	return NULL;
}

int main(int argc, const char** argv) {
	int i = 0;
	int sum = 0;
	struct data data;
	pthread_t threads[THREAD_NUM];

	if ((datas = malloc(sizeof(int) * ARRAY_SIZE)) == NULL) {
		perror("malloc fail");
		return 1;
	}

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);	

	for (i = 0; i < THREAD_NUM; i++) {
		memset(&data, 0, sizeof(data));	

		data.arr = datas;
		data.idx = i;
		
		pthread_create(&threads[i], NULL, t_func, (void*)&data);
		usleep(100);
	}

	// insert data of 1 ~ 100 to datas.	
	for (i = 0; i < ARRAY_SIZE; i++) {
		datas[i] = i + 1;
	}

	pthread_cond_broadcast(&cond);
	//pthread_cond_signal(&cond);

	for (i = 0; i < THREAD_NUM; i++) {
		pthread_join(threads[i], NULL);
		sum += sums[i];
	}

	printf("total sum of 1~100: %d\n", sum);
	return 0;
}

