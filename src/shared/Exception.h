#pragma once
#include <stdexcept>

#ifndef NOMINMAX 
#define NOMINMAX
#endif
#include <windows.h>
#include <tchar.h>

namespace RLBotBM {

struct RLBotBMException : public std::runtime_error {
	static std::string getLastErrorMessage() {
		DWORD errorCode = GetLastError();
		char errorMessage[1024];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorCode, 0, errorMessage, sizeof(errorMessage), NULL);
		return std::string(errorMessage);
	}
	RLBotBMException(std::string desc) : std::runtime_error((desc + ": " + getLastErrorMessage()).c_str()) {}
};
struct CreateFileMappingException : public RLBotBMException { CreateFileMappingException() : RLBotBMException("Failed to create file mapping object (Shared memory already exists?)") {} };
struct OpenFileMappingException   : public RLBotBMException { OpenFileMappingException()   : RLBotBMException("Failed to open file mapping object (Shared memory does not exist?)") {} };
struct MapViewOfFileException     : public RLBotBMException { MapViewOfFileException()     : RLBotBMException("Failed to open map view of file") {} };
struct CreateSemaphoreException   : public RLBotBMException { CreateSemaphoreException()   : RLBotBMException("Failed to create semaphore") {} };

}