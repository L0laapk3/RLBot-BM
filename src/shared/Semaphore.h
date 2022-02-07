#pragma once


#define NOMINMAX
#include <windows.h>
#include <string>


namespace RLBotBM::Shared {

struct Semaphore {
	HANDLE hSem;
	HANDLE hSemLock;
	int *const nWaiters;
	Semaphore(const std::string name, int *const shMemWaiters, const DWORD pid);
	~Semaphore();

	bool notifyOne();
	bool notifyAll();
	bool wait(DWORD waitTimeMS = INFINITE);
};

}