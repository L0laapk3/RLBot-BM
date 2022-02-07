#include "CondVar.h"


namespace RLBotBM::Shared {

CondVar::CondVar(const std::string name, int *const shMemWaiters, const DWORD pid) : nWaiters(shMemWaiters) {
	auto semName = name + "/sem/" + std::to_string(pid);
    hSem = CreateSemaphore(NULL, 0, std::numeric_limits<LONG>::max(), semName.c_str());
    if (hSem == NULL) {
        throw std::exception();
    }
	ReleaseSemaphore(hSem, 1, NULL);

	auto semLockName = name + "/semLock/" + std::to_string(pid);
	hSemLock = CreateSemaphore(NULL, 0, 1, semLockName.c_str());
	if (hSemLock == NULL) {
		CloseHandle(hSem);
		throw std::exception();
	}
	ReleaseSemaphore(hSemLock, 1, NULL);
}

CondVar::~CondVar() {
	CloseHandle(hSemLock);
	CloseHandle(hSem);
}

void CondVar::lock() {
	WaitForSingleObject(hSemLock, INFINITE);
}

bool CondVar::notifyOne() {
	lock();
	return notifyOnePreLocked();
}

bool CondVar::notifyAllPreLocked() {
	bool result = ReleaseSemaphore(hSem, 1, NULL);
	(*nWaiters)--;
	ReleaseSemaphore(hSemLock, 1, NULL);
	return result;
}

bool CondVar::notifyAll() {
	lock();
	return notifyAllPreLocked();
}
bool CondVar::notifyAllPreLocked() {
	bool result = ReleaseSemaphore(hSem, *nWaiters, NULL);
	*nWaiters = 0;
	ReleaseSemaphore(hSemLock, 1, NULL);
	return result;
}

bool CondVar::wait(DWORD waitTimeMS) {
	lock();
	return waitPreLocked(waitTimeMS);
}
bool CondVar::waitPreLocked(DWORD waitTimeMS) {
    (*nWaiters)++;
    ReleaseSemaphore(hSemLock, 1, NULL);
    return WaitForSingleObject(hSem, waitTimeMS) == WAIT_OBJECT_0;
}

}