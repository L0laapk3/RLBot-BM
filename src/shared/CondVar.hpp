#pragma once

#include "shared/Exception.h"


#ifndef NOMINMAX 
#define NOMINMAX
#endif
#include <windows.h>

#include <string>
#include <type_traits>
#include <chrono>


namespace RLBotBM {


class CondVar_SingleRecipient {
protected:
	HANDLE hSem;
	HANDLE hSemLock;

public:
	CondVar_SingleRecipient(const std::string name) {
		auto semName = name + "/sem/";
		hSem = CreateSemaphore(NULL, 0, std::numeric_limits<LONG>::max(), semName.c_str());
		if (hSem == NULL)
			throw CreateSemaphoreException();
		ReleaseSemaphore(hSem, 1, NULL);

		auto semLockName = name + "/semLock/";
		hSemLock = CreateSemaphore(NULL, 0, 1, semLockName.c_str());
		if (hSemLock == NULL) {
			CloseHandle(hSem);
			throw CreateSemaphoreException();
		}
		ReleaseSemaphore(hSemLock, 1, NULL);
	}

	~CondVar_SingleRecipient() {
		CloseHandle(hSemLock);
		CloseHandle(hSem);
	}
	
	void lock() {
		WaitForSingleObject(hSemLock, INFINITE);
	}
	void unlock() {
		ReleaseSemaphore(hSemLock, 1, NULL);
	}
	
	bool notifyOne() {
		return ReleaseSemaphore(hSem, 1, NULL);
	}

	bool waitOne(DWORD waitTimeMs = INFINITE) {
		auto res = WaitForSingleObject(hSem, waitTimeMs);
		return res == WAIT_OBJECT_0;
	}

	int waitN(int count, DWORD waitTimeMs = INFINITE) {
		auto endTime = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(waitTimeMs);
		while (count > 0) {
			if (!waitOne(waitTimeMs))
				return count;
			auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - std::chrono::high_resolution_clock::now()).count();
			if (elapsedMs >= waitTimeMs)
				return count;
			count--;
			waitTimeMs -= elapsedMs;
		}
		return 0;
	}

	void clearNotifications() {
		while (waitOne(0)) { }
	}
};


class CondVar_MultiRecipient : public CondVar_SingleRecipient {
	int *const nWaiters;

public:
	CondVar_MultiRecipient(const std::string name, int *const shMemWaiters) : CondVar_SingleRecipient(name), nWaiters(shMemWaiters) { }

	template<bool preLocked = false, bool keepLocked = false>
	bool notifyOne() {
		if (!preLocked)
			lock();
		bool result = CondVar_SingleRecipient::notifyOne();
		(*nWaiters)--;
		if (!keepLocked)
			unlock();
		return result;
	}

	template<bool preLocked = false, bool keepLocked = false>
	bool notifyAll() {
		if (!preLocked)
			lock();
		bool result = ReleaseSemaphore(hSem, *nWaiters, NULL);
		*nWaiters = 0;
		if (!keepLocked)
			unlock();
		return result;
	}

	template<bool preLocked = false>
	bool waitOne(DWORD waitTimeMs = INFINITE) {
		if (!preLocked)
			lock();
		(*nWaiters)++;
		unlock();
		return CondVar_SingleRecipient::waitOne(waitTimeMs);
	}
	
	template<bool preLocked = false>
	int waitN(int count, DWORD waitTimeMs = INFINITE) {
		auto endTime = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(waitTimeMs);
		bool locked = preLocked;
		while (count > 0) {
			if (!locked)
				lock();
			if (!waitOne<true>(waitTimeMs))
				return count;
			locked = false;
			auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - std::chrono::high_resolution_clock::now()).count();
			if (elapsedMs >= waitTimeMs)
				return count;
			count--;
			waitTimeMs -= elapsedMs;
		}
		return count;
	}
};

}