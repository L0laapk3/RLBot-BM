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
template bool CondVar::notifyOne<false, false>();
template bool CondVar::notifyOne<true, false>();
template bool CondVar::notifyOne<false, true>();
template bool CondVar::notifyOne<true, true>();

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
template bool CondVar::notifyAll<false, false>();
template bool CondVar::notifyAll<true, false>();
template bool CondVar::notifyAll<false, true>();
template bool CondVar::notifyAll<true, true>();

template <bool preLocked>
bool CondVar::wait(DWORD waitTimeMS) {
	if (!preLocked)
		lock();
    (*nWaiters)++;
    unlock();
    return WaitForSingleObject(hSem, waitTimeMS) == WAIT_OBJECT_0;
}
template bool CondVar::wait<false>(DWORD waitTimeMS);
template bool CondVar::wait<true>(DWORD waitTimeMS);


}