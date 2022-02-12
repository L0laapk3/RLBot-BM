#pragma once

#include <stdexcept>

#include "shared/SharedObjects.h"
#include "shared/IPComm.h"


namespace RLBotBM {

typedef Shared::SharedMemoryObj GameState;
typedef Shared::ControllerInput ControllerInput;
typedef Shared::Vec3 Vec3;
typedef Shared::Quat Quat;

class RLBotBM {
	Shared::IPComm ipComm;
	int lastTick = 0;
	
public:
	RLBotBM();
	void getCurrentState(GameState& state);

	// set controls for bot at carIndex
	void setBotInput(const ControllerInput& controls, const int carIndex);

	// test if the next tick is available (state.tick) and if so, update state
	bool pollNextTick(GameState& state);
	// wait until next tick is available (state.tick) and update state, return true if the thread had to wait
	bool waitNextTick(GameState& state);
};

class RLBotBMVersionMisMatchException : public std::runtime_error {
	virtual char const * what() const { return "RLBot-BM Version mismatch."; }
};

}