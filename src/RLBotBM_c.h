#pragma once

#include "shared/SharedObjects.h"

#ifdef __cplusplus
	namespace RLBotBM {
	using namespace Shared;
	extern "C" {
#endif


struct RLBotBM_H;
// can return null pointers if it fails to connect to the shared memory
__declspec(dllexport) RLBotBM_H* RLBotBM_create();

__declspec(dllexport) void RLBotBM_destroy(RLBotBM_H* handle);

__declspec(dllexport) void RLBotBM_getCurrentState(RLBotBM_H* handle, GameStateObj* state);

// set controls for bot at carIndex
__declspec(dllexport) void RLBotBM_setBotInput(RLBotBM_H* handle, const ControllerInput* controls, const int carIndex);

// test if the next tick is available (state.tick) and if so, update state
__declspec(dllexport) bool RLBotBM_pollNextTick(RLBotBM_H* handle, GameStateObj* state);
// wait until next tick is available (state.tick) and update state, return true if the thread had to wait
__declspec(dllexport) bool RLBotBM_waitNextTick(RLBotBM_H* handle, GameStateObj* state);

__declspec(dllexport) StateSetObj* RLBotBM_getStateSetObj(RLBotBM_H* handle);


#ifdef __cplusplus
	}
	}
#endif