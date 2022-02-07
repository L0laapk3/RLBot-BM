#include "Semaphore.h"


namespace RLBotBM::Shared {

Semaphore::Semaphore(const std::string name, int *const shMemWaiters, const DWORD pid) : nWaiters(shMemWaiters) {
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

Semaphore::~Semaphore() {
	CloseHandle(hSemLock);
	CloseHandle(hSem);
}



bool Semaphore::notifyOne() {
	WaitForSingleObject(hSemLock, INFINITE);
	bool result = ReleaseSemaphore(hSem, 1, NULL);
	(*nWaiters)--;
	ReleaseSemaphore(hSemLock, 1, NULL);
	return result;
}

bool Semaphore::notifyAll() {
	WaitForSingleObject(hSemLock, INFINITE);
	bool result = ReleaseSemaphore(hSem, *nWaiters, NULL);
	*nWaiters = 0;
	ReleaseSemaphore(hSemLock, 1, NULL);
	return result;
}

bool Semaphore::wait(DWORD waitTimeMS) {
    WaitForSingleObject(hSemLock, INFINITE);
    (*nWaiters)++;
    ReleaseSemaphore(hSemLock, 1, NULL);
    return WaitForSingleObject(hSem, waitTimeMS) == WAIT_OBJECT_0;
}

}