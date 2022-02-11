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

	// set controls for bot at carIndex
	void setBotInput(const ControllerInput& controls, const int carIndex);

	// test if the next tick is available (state.tick) and if so, update state
	bool pollNextTick(GameState& state);
	// wait until next tick is available (state.tick) and update state, return true if the thread had to wait
	bool waitNextTick(GameState& state);
};

}