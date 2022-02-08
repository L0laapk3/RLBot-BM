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

	void setBotInput(const ControllerInput& controls, const int carIndex);

	bool pollNextTick(GameState& state);
	bool waitNextTick(GameState& state);
};

}