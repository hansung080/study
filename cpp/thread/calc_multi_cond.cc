#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

#define ARRAY_SIZE 100
#define THREAD_NUM 4

std::mutex mutex;
std::condition_variable cond;

int* datas;
int sums[THREAD_NUM];

struct data {
	int* arr; // start address of datas array
	int idx; // thread index
};

void t_func(struct data* arg) {
	struct data data;
	int i = 0;
	int sum = 0;
	data = *arg;
	
	std::unique_lock<std::mutex> lock(mutex);
	cond.wait(lock);

	for (i = 0; i < 25; i++) {
		sum += data.arr[data.idx * 25 + i];
	}

	printf("thread sum: %d, %d\n", data.idx, sum);
	sums[data.idx] = sum;
	return;
}

int main(int argc, const char** argv) {
	int i = 0;
	int sum = 0;
	struct data data;
	std::vector<std::thread> threads;

	if ((datas = (int*)malloc(sizeof(int) * ARRAY_SIZE)) == NULL) {
		perror("malloc fail");
		return 1;
	}

	for (i = 0; i < THREAD_NUM; i++) {
		memset(&data, 0, sizeof(data));	

		data.arr = datas;
		data.idx = i;
		
		std::thread thread(t_func, &data);
		threads.push_back(std::move(thread));
		usleep(100);
	}

	// insert data of 1 ~ 100 to datas.	
	for (i = 0; i < ARRAY_SIZE; i++) {
		datas[i] = i + 1;
	}

	cond.notify_all();
	//cond.notify_one();
	
	int count = 0;
	for (auto& thread : threads) {
		thread.join();
		sum += sums[count];
		count++;
	}

	printf("total sum of 1~100: %d\n", sum);
	return 0;
}

