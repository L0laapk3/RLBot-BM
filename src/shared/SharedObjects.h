#pragma once

#ifdef __cplusplus
	#include <array>
	#define ARRAY(T, N, name) std::array<T, N> name

	#include "markable.hpp"
	typedef Markable<MarkableFloat> OptFloat_t;

	extern "C" {
#else
	#define ARRAY(T, N, name) T name[N]
	typedef float OptFloat_t;
#endif

namespace RLBotBM::Shared {

constexpr unsigned int VERSION = 8;

typedef OptFloat_t OptFloat;
	
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
	unsigned long useItem : 1;
	unsigned long itemTarget;
};

struct PhysObj {
	Quat orientation;
	Vec3 position;
	Vec3 velocity;
	Vec3 angularVelocity;
};

struct Ball : PhysObj {
	float radius;
};

struct Wheel {
	float spinSpeed;
	float suspensionDistance;
	float frictionCurveInput;	
	unsigned int contact : 1;
	unsigned int reset : 1;
};
struct Car : PhysObj {
	ControllerInput input;
	float boost;
	unsigned char team;
	Vec3 hitbox;
	Vec3 hitboxOffset;

	int demolishedAt;
	int flippedAt;

	// front left, front right, back left, back right
	ARRAY(Wheel, 4, wheels);
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
struct StateSetPhysObj {
	Quat orientation;
	Vec3 position;
	Vec3 velocity;
	Vec3 angularVelocity;
};

struct StateSetBall : StateSetPhysObj {
};

struct StateSetWheel {
	OptFloat spinSpeed;
};

struct StateSetCar : StateSetPhysObj {
	OptFloat boost;

	ARRAY(StateSetWheel, 4, wheels);
};

struct DropShotObj {
	enum TileState : unsigned char {
		Normal = 0,
		Damaged = 1,
		Open = 2,
	};

	bool isDropShot;
	float ballCharge;
	ARRAY(TileState, 140, tileDamage);
};

struct BoostPad {
	int pickupTick; // 0 if has respawned
	bool isBig;
	Vec3 position;
};

struct GameStateObj {
	ARRAY(Car, 64, cars);
	unsigned int numCars;

	ARRAY(Ball, 8, balls);
	unsigned int numBalls;

	ARRAY(BoostPad, 128, boostPads);
	unsigned int numBoostPads;

	DropShotObj dropShot;

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
	ARRAY(StateSetCar, 64, cars);
	ARRAY(StateSetBall, 8, balls);
	bool setAny;
};

struct SharedMemoryObj {
	unsigned int version;
	
	GameStateObj gameState;
	
	int nTickWaiters;

	StateSetObj stateSetObj;
};

}

#ifdef __cplusplus
	}
#endif