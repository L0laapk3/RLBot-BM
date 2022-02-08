
#include "RLBotBM.h"

#define NOMINMAX
#include <windows.h>

namespace RLBotBM {

RLBotBM::RLBotBM() : ipComm(false) {
}

void RLBotBM::setBotInput(const Shared::ControllerInput& controls, const int carIndex) {
	ipComm.mem->cars[carIndex].input = controls;
	ipComm.mem->cars[carIndex].RLBotBMControlled = true;
}

bool RLBotBM::pollNextTick(GameState& state) {
	if (lastTick == ipComm.mem->tick)
		return false;

	lastTick = ipComm.mem->tick;
	state = ipComm.mem;
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
	
	state = ipComm.mem;
	return hadToWait;
}

}