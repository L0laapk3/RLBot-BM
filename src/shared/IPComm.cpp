#include "shared/IPComm.h"
#include "shared/Exception.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <tchar.h>

#include <string>


namespace RLBotBM {


IPComm::IPComm(bool create, const std::string mappingSuffix) :
	fileMapping("sharedMemory" + mappingSuffix, create),
	mem(fileMapping),
	cvWaitTick("cvWaitTick" + mappingSuffix, &mem->nTickWaiters),
	cvWaitControls("cvWaitControls" + mappingSuffix) {
		if (create)
			new (mem.mem) SharedMemoryObj{}; // initialize memory
	}
}