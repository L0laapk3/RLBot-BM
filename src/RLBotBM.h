#pragma once

#include <stdexcept>
#include <string>

#include "shared/SharedObjects.h"
#include "shared/Exception.h"
#include "shared/IPComm.h"


namespace RLBotBM {

typedef GameStateObj GameState;
typedef ControllerInput ControllerInput;
typedef Vec3 Vec3;
typedef Quat Quat;
typedef StateSetObj StateSetObj;

class RLBotBM {	
protected:
	IPComm ipComm;
	int lastTick = 0;
	
	RLBotBM(bool createFileMapping, const std::string fileMappingSuffix);
	
public:
	RLBotBM();
	void getCurrentState(GameState& state);

	// set controls for bot at carIndex
	void setBotInput(const ControllerInput& controls, const int carIndex);

	// test if the next tick is available (state.tick) and if so, update state
	bool pollNextTick(GameState& state);
	// wait until next tick is available (state.tick) and update state, return true if the thread had to wait
	bool waitNextTick(GameState& state);

	StateSetObj& getStateSetObj();
};

class RLBotBMVersionMisMatchException : public RLBotBMException {
public:
	RLBotBMVersionMisMatchException(unsigned int currentMajorVersion, unsigned int currentMinorVersion, unsigned int expectedMajorVersion, unsigned int expectedMinorVersion) : RLBotBMException("RLBotBM: Shared memory version mismatch. Has " + std::to_string(currentMajorVersion) + "." + std::to_string(currentMinorVersion) + ", but server requires " + std::to_string(expectedMajorVersion) + "." + std::to_string(expectedMinorVersion)) {}
};

}