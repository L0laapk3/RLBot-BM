
#include <iostream>
#include <chrono>
#include <thread>

#include "Shared.h"



int main(int, char**) {
	std::unique_ptr<RLBotBM::Shared::SharedMemoryManager> smm = RLBotBM::Shared::SharedMemoryManager::connect();
	smm->mem->cars[0].throttle = 0.1f;
	while (true) {
		for (; smm->mem->cars[0].throttle < 1.0f; smm->mem->cars[0].throttle += 0.01f) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			std::cout << "throttle: " << smm->mem->cars[0].throttle << std::endl;
		}
		for (; smm->mem->cars[0].throttle > -1.0f; smm->mem->cars[0].throttle -= 0.01f) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			std::cout << "throttle: " << smm->mem->cars[0].throttle << std::endl;
		}
	}
}