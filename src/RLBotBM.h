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
	RLBotBM();

	void setControls(int carIndex, ControllerInput& controls);

	bool pollNextTick(GameState& state);
	bool waitNextTick(GameState& state);
};

}