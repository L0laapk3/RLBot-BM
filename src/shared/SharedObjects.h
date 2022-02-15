#pragma once

#include <array>

#include "markable.hpp"

namespace RLBotBM::Shared {

constexpr unsigned int VERSION = 6;

typedef Markable<MarkableFloat> OptFloat;
	
struct Vec3 {
	float x, y, z;
};
struct Quat {
	float x, y, z, w;
};

struct ControllerInput {
    float throttle;
    float steer;
    float pitch;
    float yaw;
    float roll;
    unsigned long handbrake : 1;
    unsigned long jump : 1;
    unsigned long boost : 1;
};

template<typename V = Vec3, typename Q = Quat>
struct PhysObj {
	Q orientation;
	V position;
	V velocity;
	V angularVelocity;
};
struct Ball : PhysObj<> {
	float radius;
};

struct Wheel {
	float spinSpeed;
	float suspensionDistance;
	float frictionCurveInput;	
	unsigned int contact : 1;
	unsigned int reset : 1;
};
struct Car : PhysObj<> {
	ControllerInput input;
	float boost;
	unsigned char team;
	Vec3 hitbox;
	Vec3 hitboxOffset;

	int demolishedAt;
	int flippedAt;

	// front left, front right, back left, back right
	std::array<Wheel, 4> wheels;
	union {
		struct {
			unsigned int jumped : 1;
			unsigned int hasFlip : 1;
			unsigned int superSonic : 1;
			unsigned int demolished : 1;
			unsigned int bot : 1;
			unsigned int RLBotBMControlled : 1;
		};
		unsigned int flags;
	};
};

struct StateSetVec3 {
	OptFloat x, y, z;
};

struct StateSetQuat {
	OptFloat x, y, z, w;
};

struct StateSetBall : PhysObj<StateSetVec3, StateSetQuat> {
};

struct StateSetWheel {
	OptFloat spinSpeed;
};

struct StateSetCar : PhysObj<StateSetVec3, StateSetQuat> {
	OptFloat boost;

	std::array<StateSetWheel, 4> wheels;
};

struct GameStateObj {
	std::array<Car, 64> cars;
	unsigned int numCars;

	std::array<Ball, 8> balls;
	unsigned int numBalls;

	std::array<int, 128> boostPads;
	unsigned int numBoostPads;

	int tick;

	union {
		struct {
			unsigned int roundActive : 1;
			unsigned int matchEnded : 1;
		};
		unsigned int flags;
	};
};

struct StateSetObj {
	std::array<StateSetCar, 64> cars;
	std::array<StateSetBall, 8> balls;
	bool setAny;
};

struct SharedMemoryObj {
	unsigned int version;
	
	GameStateObj gameState;
	
	int nTickWaiters;

	StateSetObj stateSetObj;
};

}