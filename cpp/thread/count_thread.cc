#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

#define MAX_THREAD 2

void increase(int* count) {
	int tmp = *count;
	tmp++;
	sleep(1); // sleep to cause a race condition.
	*count = tmp;
}

void t_func(int* count) {
	pthread_t thread_id = pthread_self();

	while (1) {
		//(*count)++;
		increase(count);
		std::cout << "worker thread : " << thread_id << ", " << *count << std::endl;
		sleep(1);
	}
}

int main(int argc, const char** argv) {
	std::thread threads[MAX_THREAD];
	int i = 0;
	int count = 0;

	for (i = 0; i < MAX_THREAD; i++) {
		std::thread t(t_func, &count);
		threads[i] = t;
		usleep(5000);
	}

	pthread_t main_thread_id = pthread_self();
	while (1) {
		//count++;
		increase(&count);
		std::cout << "main thread   : " << main_thread_id << ", " << count << std::endl;
		sleep(2);
	}

	for (i = 0; i < MAX_THREAD; i++) {
		threads[i].join();
	}

	return 0;
}

