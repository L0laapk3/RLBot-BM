#pragma once


#define NOMINMAX
#include <windows.h>
#include <string>


namespace RLBotBM::Shared {

struct CondVar {
	HANDLE hSem;
	HANDLE hSemLock;
	int *const nWaiters;
	CondVar(const std::string name, int *const shMemWaiters, const DWORD pid);
	~CondVar();

	bool notifyOne();
	bool notifyAll();
	bool wait(DWORD waitTimeMS = INFINITE);

	void lock();
	bool notifyOnePreLocked();
	bool notifyAllPreLocked();
	bool waitPreLocked(DWORD waitTimeMS = INFINITE);
};

}