
#include "RLBotBM.h"

#include <iostream>

namespace RLBotBM {

RLBotBM::RLBotBM() : ipComm(false) {
	if (ipComm.mem->versionMajor != VERSION_MAJOR || VERSION_MINOR > ipComm.mem->versionMinor) {
		std::cerr << "RLBotBM: Shared memory version mismatch. Has " << VERSION_MAJOR << "." << VERSION_MINOR << ", but server requires " << ipComm.mem->versionMajor << "(." << ipComm.mem->versionMinor << ")" << std::endl;
		throw RLBotBMVersionMisMatchException(VERSION_MAJOR, VERSION_MINOR, ipComm.mem->versionMajor, ipComm.mem->versionMinor);
	}
	if (ipComm.mem->versionMinor != VERSION_MINOR) {
		std::cout << "RLBotBM: Shared memory version outdated. Has " << VERSION_MAJOR << "." << VERSION_MINOR << ", server has " << ipComm.mem->versionMajor << "." << ipComm.mem->versionMinor << std::endl;
	}
}

void RLBotBM::setBotInput(const ControllerInput& controls, const int carIndex) {
	ipComm.mem->gameState.cars[carIndex].input = controls;
	ipComm.mem->gameState.cars[carIndex].RLBotBMControlled = true;
}

void RLBotBM::getCurrentState(GameState& state) {
	lastTick = ipComm.mem->gameState.tick;
	state = ipComm.mem->gameState;
}

bool RLBotBM::pollNextTick(GameState& state) {
	if (lastTick == ipComm.mem->gameState.tick)
		return false;

	getCurrentState(state);
	return true;
}

bool RLBotBM::waitNextTick(GameState& state) {
	bool hadToWait = false;
	// lock the wait cv to prevent tick from being updated later
	ipComm.cvWaitTick.lock();	// todo: somehow all bots should be able to lock and unlock this simultaneously but not the framework
	if (lastTick != ipComm.mem->gameState.tick) { // next tick is already ready, immediately progress
		ipComm.cvWaitTick.unlock();
	} else {
		// signal the framework that we're ready with current tick
		ipComm.cvWaitControls.notifyOne();
		
		// wait for next tick
		ipComm.cvWaitTick.waitOne<true>();
		while (lastTick == ipComm.mem->gameState.tick) // eat any possible extra abandoned notifications if we're not on the next tick yet
			ipComm.cvWaitTick.CondVar_SingleRecipient::waitOne(0);

		hadToWait = true;
	}
	
	getCurrentState(state);
	return hadToWait;
}



StateSetObj& RLBotBM::getStateSetObj() {
	return ipComm.mem->stateSetObj;
}

}