// Mansoor Zafar
#include <iomanip>
#include <iostream>
#include <random>
#include <mutex>
#include <thread>
#include <semaphore>

#include <chrono>
#include <vector>
#define MAX_COUNTER_ITEMS 20
#define MAX_THREADS 7
#define NUMBER_OF_WORKERS 1

#define BAKER_REST_TIME 1
#define MIN_REST_TIME_CUSTOMER 1
#define MAX_REST_TIME_CUSTOMER 7

std::counting_semaphore<0> freeSpaces(MAX_COUNTER_ITEMS);
std::counting_semaphore<0> filledSpaces(0);
std::mutex mutex;

std::vector<bool> counter(MAX_COUNTER_ITEMS);
int in = 0, out = 0;

void printBuffer() {
	std::cout << "[ ";
	for(int i = 0; i < MAX_COUNTER_ITEMS; ++i) 
		std::cout << (counter[i] ? "\033[0;33mloaf\033[0m" : "\033[90mnone\033[0m") 
			<< ( i < MAX_COUNTER_ITEMS - 1 ? ", " : "");
	std::cout << " ]\n\n";
}

void printBaker(std::thread::id id, int index) {
	std::cout << "\n\033[32mBaker\033[0m produces one bread [ " 
		<< "\033[32m" << in << "\033[0m" << " ] " << std::setw(7) << "Thread ID: [ \033[32m" 
		<< std::this_thread::get_id() << "\033[0m ]" 
		<< "\n> Counter: ";
}

void printCustomer(std::thread::id id, int index) {
	std::cout << "\n\033[31mCustomer\033[0m purchases bread [ " 
		<< "\033[31m" << out << "\033[m" << " ] " << std::setw(7) << "Thread ID: [ \033[31m" 
		<< std::this_thread::get_id() << "\033[0m ]"
		<< "\n> Counter: ";
}

void ProducerConsumer(
	std::counting_semaphore<0>& get, 
	std::counting_semaphore<0>& release,
	int& increment,
	bool addBread,
	void (*print)(std::thread::id id, int index)
) {
	while(true) {
		get.acquire();
		std::unique_lock<std::mutex> lock(mutex);
		
		counter[increment] = addBread;
		
		print(std::this_thread::get_id(), increment);
		printBuffer();

		increment = (increment + 1) % MAX_COUNTER_ITEMS;		
		
		lock.unlock();		
		release.release();		
		const int randomTime = MIN_REST_TIME_CUSTOMER + (rand() % (MAX_REST_TIME_CUSTOMER + MIN_REST_TIME_CUSTOMER + 1));
		std::this_thread::sleep_for(std::chrono::seconds(addBread ? BAKER_REST_TIME : randomTime));
	}
}

int main() {
	std::srand(time(0));
	for(int i = 0; i < MAX_COUNTER_ITEMS; ++i) counter[i] = 0;

	std::vector<std::thread> threads;
	threads.reserve(MAX_THREADS);

	for(int i = 0; i < MAX_THREADS; ++i) {
		if(i < NUMBER_OF_WORKERS) {
			threads.emplace_back(
				ProducerConsumer, 
				std::ref(freeSpaces), 
				std::ref(filledSpaces), 
				std::ref(in), 
				true,
				printBaker
			);
		} else {
			threads.emplace_back(
				ProducerConsumer, 
				std::ref(filledSpaces), 
				std::ref(freeSpaces), 
				std::ref(out), 
				false,
				printCustomer
			);
		}
	}
	
	for(std::thread& thread : threads) {
		thread.join();
	}
	
	return 0;
}