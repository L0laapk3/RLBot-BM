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

struct PhysicsObj {
	Quat orientation;
	Vec3 position;
	Vec3 velocity;
	Vec3 angularVelocity;
};
struct Ball : PhysicsObj {
	float radius;
};

struct Wheel {
	float spinSpeed;
	float suspensionDistance;
	float frictionCurveInput;	
	unsigned int contact : 1;
	unsigned int reset : 1;
};
struct Car : PhysicsObj {
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
};

}