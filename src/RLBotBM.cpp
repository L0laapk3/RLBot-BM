
#include "RLBotBM.h"

#include <iostream>

namespace RLBotBM {

RLBotBM::RLBotBM() : ipComm(false) {
	if (ipComm.mem->version != Shared::VERSION) {
		std::cerr << "RLBotBM: Shared memory version mismatch. Expected " << Shared::VERSION << ", got " << ipComm.mem->version << "." << std::endl;
		throw RLBotBMVersionMisMatchException();
	}
}

void RLBotBM::setBotInput(const Shared::ControllerInput& controls, const int carIndex) {
	ipComm.mem->cars[carIndex].input = controls;
	ipComm.mem->cars[carIndex].RLBotBMControlled = true;
}

void RLBotBM::getCurrentState(GameState& state) {
	lastTick = ipComm.mem->tick;
	state = ipComm.mem;
}

bool RLBotBM::pollNextTick(GameState& state) {
	if (lastTick == ipComm.mem->tick)
		return false;

	getCurrentState(state);
	return true;
}

bool RLBotBM::waitNextTick(GameState& state) {
	bool hadToWait = false;
	// lock the wait cv to prevent tick from being updated later
	ipComm.cvWaitTick.lock();	// todo: somehow all bots should be able to lock and unlock this simultaneously but not the framework
	if (lastTick != ipComm.mem->tick) { // next tick is already ready, immediately progress
		ipComm.cvWaitTick.unlock();
	} else {
		// signal the framework that we're ready with current tick
		ipComm.cvWaitControls.notifyAll();
		
		// wait for next tick
		ipComm.cvWaitTick.wait<true>();
		hadToWait = true;
	}
	
	getCurrentState(state);
	return hadToWait;
}

}