#include "shared/IPComm.h"
#include "shared/Exception.h"

#ifndef NOMINMAX 
#define NOMINMAX
#endif
#include <windows.h>
#include <tchar.h>

#include <string>


namespace RLBotBM::Shared {

IPComm::IPComm(bool create) :
	fileMapping("sharedMemory", create),
	mem(fileMapping),
	cvWaitTick("cvWaitTick", &mem->nTickWaiters),
	cvWaitControls("cvWaitControls") {
		if (create)
			new (mem.mem) SharedMemoryObj{}; // initialize memory
	}
}