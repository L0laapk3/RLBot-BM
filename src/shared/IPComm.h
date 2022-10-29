#pragma once

#include "shared/FileMapping.hpp"
#include "shared/CondVar.hpp"
#include "shared/SharedObjects.h"

#include <stdexcept>


namespace RLBotBM::Shared {


class IPComm {
public:
	struct IPCommException : public std::runtime_error {
		static std::string getLastErrorMessage() {
			DWORD errorCode = GetLastError();
			char errorMessage[1024];
			FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorCode, 0, errorMessage, sizeof(errorMessage), NULL);
			return std::string(errorMessage);
		}
		IPCommException(std::string desc) : std::runtime_error((desc + ": " + getLastErrorMessage()).c_str()) {}
	};
	struct CreateFileMappingException        : public IPCommException { CreateFileMappingException()        : IPCommException("Failed to create file mapping object") {} };
	struct OpenFileMappingException          : public IPCommException { OpenFileMappingException()          : IPCommException("Failed to open file mapping object") {} };
	struct MapViewOfFileException            : public IPCommException { MapViewOfFileException()            : IPCommException("Failed to open map view of file") {} };
	struct CreateSemaphoreException          : public IPCommException { CreateSemaphoreException()          : IPCommException("Failed to create semaphore") {} };
	struct SharedMemoryExistsException       : public IPCommException { SharedMemoryExistsException()       : IPCommException("Shared memory already exists") {} };
	struct SharedMemoryDoesNotExistException : public IPCommException { SharedMemoryDoesNotExistException() : IPCommException("Shared memory does not exist") {} };


	IPComm(bool create);

private:
	FileMapping<SharedMemoryObj> fileMapping;
public:
	FileMappingView<SharedMemoryObj> mem;
	CondVar_MultiRecipient cvWaitTick;
	CondVar_SingleRecipient cvWaitControls;
};

}
