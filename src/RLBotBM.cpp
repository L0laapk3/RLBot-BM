
#include "RLBotBM.h"

namespace RLBotBM {

RLBotBM::RLBotBM(uint32_t rlPID) : ipComm(false, rlPID) {
}

void RLBotBM::setControls(int carIndex, Shared::ControllerInput& controls) {
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

void RLBotBM::waitNextTick(GameState& state) {
	// lock the wait cv to prevent tick from being updated later
	ipComm.cvWaitTick.lock();	// todo: somehow all bots should be able to lock and unlock this simultaneously but not the framework
	if (lastTick != ipComm.mem->tick) {
		ipComm.cvWaitTick.unlock();
		state = ipComm.mem;
		return;
	}
		
	// signal the framework that we're ready with current tick
	ipComm.cvWaitControls.notifyAll();
	
	// wait for next tick
	ipComm.cvWaitTick.wait<true>();
	
}

}