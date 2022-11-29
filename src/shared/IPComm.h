#pragma once

#include "shared/FileMapping.hpp"
#include "shared/CondVar.hpp"
#include "shared/SharedObjects.h"



namespace RLBotBM::Shared {

class IPComm {
public:
	IPComm(bool create);

private:
	FileMapping<SharedMemoryObj> fileMapping;
public:
	FileMappingView<SharedMemoryObj> mem;
	CondVar_MultiRecipient cvWaitTick;
	CondVar_SingleRecipient cvWaitControls;
};

}
