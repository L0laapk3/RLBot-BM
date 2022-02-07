#pragma once

#include <array>

#include "shared/FileMapping.hpp"
#include "shared/Semaphore.h"
#include "shared/SharedObjects.h"


namespace RLBotBM::Shared {


class IPComm {
public:
	struct Exception : public std::exception {
		static std::string getLastErrorMessage() {
			DWORD errorCode = GetLastError();
			char errorMessage[1024];
			FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorCode, 0, errorMessage, sizeof(errorMessage), NULL);
			return std::string(errorMessage);
		}
		Exception(std::string desc) : std::exception((desc + ": " + getLastErrorMessage()).c_str()) {}
	};
	struct CreateFileMappingException : public Exception { CreateFileMappingException() : Exception("Failed to create file mapping object") {} };
	struct OpenFileMappingException : public Exception { OpenFileMappingException() : Exception("Failed to open file mapping object") {} };
	struct MapViewOfFileException : public Exception { MapViewOfFileException() : Exception("Failed to open map view of file") {} };
	struct CreateSemaphoreException : public Exception { CreateSemaphoreException() : Exception("Failed to create semaphore") {} };
	struct SharedMemoryExistsException : public Exception { SharedMemoryExistsException() : Exception("Shared memory already exists") {} };
	struct SharedMemoryDoesNotExistException : public Exception { SharedMemoryDoesNotExistException() : Exception("Shared memory does not exist") {} };


	IPComm(bool create, DWORD pid);

private:
	FileMapping<SharedMemoryObj> fileMapping;
public:
	FileMappingView<SharedMemoryObj> mem;
	Semaphore semWaitTick;
	Semaphore semWaitControls;
};

}
