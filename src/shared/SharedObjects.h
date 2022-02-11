#pragma once

#include <array>
#include <bitset>

namespace RLBotBM::Shared {
	
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
struct Car : PhysicsObj {
	ControllerInput input;
	float boost;
	unsigned char team;
	Vec3 hitBox;
	Vec3 hitBoxOffset;

	int demolishedAt = std::numeric_limits<int>::min();
	int flippedAt = std::numeric_limits<int>::min();
	union {
		struct {
			unsigned int frontLeftWheelContact : 1;
			unsigned int frontRightWheelContact : 1;
			unsigned int backLeftWheelContact : 1;
			unsigned int backRightWheelContact : 1;
			unsigned int frontLeftWheelReset : 1;
			unsigned int frontRightWheelReset : 1;
			unsigned int backLeftWheelReset : 1;
			unsigned int backRightWheelReset : 1;
			unsigned int onGround : 1;
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
	std::array<Car, 64> cars;
	unsigned int numCars;

	std::array<Ball, 8> balls;
	unsigned int numBalls;

	std::array<int, 128> boostPads;
	unsigned int numBoostPads;

	int tick;

	int nTickWaiters;
	int nControlWaiters;
};

}