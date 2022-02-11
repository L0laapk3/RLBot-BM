#pragma once

#include <array>

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
	struct {
		unsigned int frontLeftWheelContact : 1;
		unsigned int frontRightWheelContact : 1;
		unsigned int backLeftWheelContact : 1;
		unsigned int backRightWheelContact : 1;
		unsigned int RLBotBMControlled : 1;
	};
};

struct SharedMemoryObj {
	std::array<Car, 64> cars;
	unsigned int numCars;

	std::array<Ball, 8> balls;
	unsigned int numBalls;

	int tick;

	int nTickWaiters;
	int nControlWaiters;
};

}