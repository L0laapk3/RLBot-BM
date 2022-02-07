#include "shared/IPComm.h"

#include <windows.h>
#include <tchar.h>

#include <string>


namespace RLBotBM::Shared {

IPComm::IPComm(bool create, DWORD pid) :
	fileMapping("sharedMemory", create, pid),
	mem(fileMapping, pid),
	semWaitTick("semWaitTick", &mem->nTickWaiters, pid),
	semWaitControls("semWaitControls", &mem->nControlWaiters, pid) {}
	
}