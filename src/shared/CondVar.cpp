#include "CondVar.h"


namespace RLBotBM::Shared {

CondVar::CondVar(const std::string name, int *const shMemWaiters) : nWaiters(shMemWaiters) {
	auto semName = name + "/sem/";
    hSem = CreateSemaphore(NULL, 0, std::numeric_limits<LONG>::max(), semName.c_str());
    if (hSem == NULL) {
        throw std::exception();
    }
	ReleaseSemaphore(hSem, 1, NULL);

	auto semLockName = name + "/semLock/";
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
void CondVar::unlock() {
	ReleaseSemaphore(hSemLock, 1, NULL);
}

	template<bool preLocked = false, bool keepLocked = false>
	bool notifyOne();
	template<bool preLocked = false, bool keepLocked = false>
	bool notifyAll();
	template<bool preLocked = false, bool keepLocked = false>
	bool wait(DWORD waitTimeMS = INFINITE);
};

template <bool preLocked, bool keepLocked>
bool CondVar::notifyOne() {
	if (!preLocked)
		lock();
	bool result = ReleaseSemaphore(hSem, 1, NULL);
	(*nWaiters)--;
	if (!keepLocked)
		unlock();
	return result;
}
template CondVar::notifyOne<false, false>();
template CondVar::notifyOne<true, false>();
template CondVar::notifyOne<false, true>();
template CondVar::notifyOne<true, true>();

template <bool preLocked, bool keepLocked>
bool CondVar::notifyAll() {
	if (!preLocked)
		lock();
	bool result = ReleaseSemaphore(hSem, *nWaiters, NULL);
	*nWaiters = 0;
	if (!keepLocked)
		unlock();
	return result;
}
template CondVar::notifyAll<false, false>();
template CondVar::notifyAll<true, false>();
template CondVar::notifyAll<false, true>();
template CondVar::notifyAll<true, true>();

template <bool preLocked>
bool CondVar::wait(DWORD waitTimeMS) {
	if (!preLocked)
		lock();
    (*nWaiters)++;
    unlock();
    return WaitForSingleObject(hSem, waitTimeMS) == WAIT_OBJECT_0;
}
template CondVar::wait<false>();
template CondVar::wait<true>();


}