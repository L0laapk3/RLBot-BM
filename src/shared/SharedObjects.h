#pragma once

#include <array>

namespace RLBotBM::Shared {

constexpr unsigned int VERSION = 4;

	
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

struct StateSetVec3 : Vec3 {
	bool setX;
	bool setY;
	bool setZ;
};

struct StateSetQuat : Quat {
	bool setX;
	bool setY;
	bool setZ;
	bool setW;
};

struct StateSetBall : PhysObj<StateSetVec3, StateSetQuat> {
};

struct StateSetWheel {
	float spinSpeed;
	bool setSpinSpeed;
};

struct StateSetCar : PhysObj<StateSetVec3, StateSetQuat> {
	float boost;
	bool setBoost;

	std::array<StateSetWheel, 4> wheels;
};

struct StateSetObj {
	bool setAny;
	std::array<StateSetCar, 64> cars;
	std::array<StateSetBall, 8> balls;
};

struct SharedMemoryObj {
	unsigned int version;
	std::array<Car, 64> cars;
	unsigned int numCars;

	std::array<Ball, 8> balls;
	unsigned int numBalls;

	std::array<int, 128> boostPads;
	unsigned int numBoostPads;

	int tick;

	int nTickWaiters;

	union {
		struct {
			unsigned int roundActive : 1;
			unsigned int matchEnded : 1;
		};
		unsigned int flags;
	};

	StateSetObj stateSetObj;
};

}