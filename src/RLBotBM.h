#pragma once

#include <bitset>

#include "shared/SharedObjects.h"
#include "shared/IPComm.h"


namespace RLBotBM {

typedef Shared::SharedMemoryObj GameState;
typedef Shared::ControllerInput ControllerInput;

class RLBotBM {
	Shared::IPComm ipComm;
	int lastTick = 0;

public:
	RLBotBM(uint32_t rlPID);

	void setControls(int carIndex, ControllerInput& controls);

	bool pollNextTick(GameState& state);
	void waitNextTick(GameState& state);
};

}