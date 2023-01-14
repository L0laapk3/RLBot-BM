#pragma once

#include "shared/FileMapping.hpp"
#include "shared/CondVar.hpp"
#include "shared/SharedObjects.h"



namespace RLBotBM {

class IPComm {
public:
	IPComm(bool create, const std::string fileMappingSuffix = "");

private:
	FileMapping<SharedMemoryObj> fileMapping;
public:
	FileMappingView<SharedMemoryObj> mem;
	CondVar_MultiRecipient cvWaitTick;
	CondVar_SingleRecipient cvWaitControls;
};

}
