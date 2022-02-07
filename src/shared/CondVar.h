#pragma once


#define NOMINMAX
#include <windows.h>
#include <string>


namespace RLBotBM::Shared {

struct CondVar {
	HANDLE hSem;
	HANDLE hSemLock;
	int *const nWaiters;
	CondVar(const std::string name, int *const shMemWaiters);
	~CondVar();
	

	void lock();
	void unlock();

	template<bool preLocked = false, bool keepLocked = false>
	bool notifyOne();
	template<bool preLocked = false, bool keepLocked = false>
	bool notifyAll();
	template<bool preLocked = false>
	bool wait(DWORD waitTimeMS = INFINITE);
};

}