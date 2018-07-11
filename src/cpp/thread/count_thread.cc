#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <vector>

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
		increase(count);
		std::cout << "worker thread : " << thread_id << ", " << *count << std::endl;
		sleep(1);
	}
}

int main(int argc, const char** argv) {
	std::vector<std::thread> threads;
	int i = 0;
	int count = 0;

	for (i = 0; i < MAX_THREAD; i++) {
		std::thread thread(t_func, &count);
		threads.push_back(std::move(thread));
		usleep(5000);
	}

	pthread_t main_thread_id = pthread_self();
	while (1) {
		increase(&count);
		std::cout << "main thread   : " << main_thread_id << ", " << count << std::endl;
		sleep(2);
	}

	for (auto& thread : threads) {
		thread.join();
	}	

	return 0;
}

