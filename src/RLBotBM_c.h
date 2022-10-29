#pragma once

#include "shared/SharedObjects.h"

#ifdef __cplusplus
	namespace RLBotBM {
	using namespace Shared;
	extern "C" {
#endif


struct RLBotBM_H;
RLBotBM_H* RLBotBM_create();	// can return null pointers if construction
void RLBotBM_destroy(RLBotBM_H* handle);

void RLBotBM_getCurrentState(RLBotBM_H* handle, GameStateObj* state);

// set controls for bot at carIndex
void RLBotBM_setBotInput(RLBotBM_H* handle, const ControllerInput* controls, const int carIndex);

// test if the next tick is available (state.tick) and if so, update state
bool RLBotBM_pollNextTick(RLBotBM_H* handle, GameStateObj* state);
// wait until next tick is available (state.tick) and update state, return true if the thread had to wait
bool RLBotBM_waitNextTick(RLBotBM_H* handle, GameStateObj* state);

StateSetObj* RLBotBM_getStateSetObj(RLBotBM_H* handle);


#ifdef __cplusplus
	}
	}
#endif