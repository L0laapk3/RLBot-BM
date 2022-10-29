#include "RLBotBM_c.h"
#include "RLBotBM.h"
#include "shared/IPComm.h"

#include <iostream>

namespace RLBotBM {
extern "C" {



RLBotBM_H* RLBotBM_create() {
	try {
		return reinterpret_cast<RLBotBM_H*>(new RLBotBM());
	} catch (IPComm::IPCommException& e) {
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

void RLBotBM_destroy(RLBotBM_H* handle) {
	delete reinterpret_cast<RLBotBM*>(handle);
}

void RLBotBM_getCurrentState(RLBotBM_H* handle, GameStateObj* state) {
	reinterpret_cast<RLBotBM*>(handle)->getCurrentState(*state);
}

void RLBotBM_setBotInput(RLBotBM_H* handle, const ControllerInput* controls, const int carIndex) {
	reinterpret_cast<RLBotBM*>(handle)->setBotInput(*controls, carIndex);
}

bool RLBotBM_pollNextTick(RLBotBM_H* handle, GameStateObj* state) {
	return reinterpret_cast<RLBotBM*>(handle)->pollNextTick(*state);
}

bool RLBotBM_waitNextTick(RLBotBM_H* handle, GameStateObj* state) {
	return reinterpret_cast<RLBotBM*>(handle)->waitNextTick(*state);
}

StateSetObj* RLBotBM_getStateSetObj(RLBotBM_H* handle) {
	return &reinterpret_cast<RLBotBM*>(handle)->getStateSetObj();
}



}
}