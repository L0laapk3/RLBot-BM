#pragma once

#ifdef __cplusplus
	#include <array>
	#include "markable.hpp"

	#define ARRAY(T, N, name) std::array<T, N> name
	typedef Markable<MarkableFloat> OptFloat_t;

	namespace RLBotBM::Shared {
	extern "C" {
#else
	#include <stdbool.h>
	
	#define ARRAY(T, N, name) T name[N]
	typedef float OptFloat_t;
#endif


const unsigned int VERSION = 8;

typedef OptFloat_t OptFloat;
	
struct Vec3 {
	float x, y, z;
};
typedef struct Vec3 Vec3;
struct Quat {
	float x, y, z, w;
};
typedef struct Quat Quat;

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
typedef struct ControllerInput ControllerInput;


struct Ball {
	Quat orientation;
	Vec3 position;
	Vec3 velocity;
	Vec3 angularVelocity;

	float radius;
};
typedef struct Ball Ball;

struct Wheel {
	float spinSpeed;
	float suspensionDistance;
	float frictionCurveInput;	
	unsigned int contact : 1;
	unsigned int reset : 1;
};
typedef struct Wheel Wheel;

struct Car {
	Quat orientation;
	Vec3 position;
	Vec3 velocity;
	Vec3 angularVelocity;

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
typedef struct Car Car;

struct StateSetVec3 {
	OptFloat x, y, z;
};
typedef struct StateSetVec3 StateSetVec3;

struct StateSetQuat {
	OptFloat x, y, z, w;
};
typedef struct StateSetQuat StateSetQuat;

struct StateSetBall {
	StateSetQuat orientation;
	StateSetVec3 position;
	StateSetVec3 velocity;
	StateSetVec3 angularVelocity;
};
typedef struct StateSetBall StateSetBall;

struct StateSetWheel {
	OptFloat spinSpeed;
};
typedef struct StateSetWheel StateSetWheel;

struct StateSetCar {
	StateSetQuat orientation;
	StateSetVec3 position;
	StateSetVec3 velocity;
	StateSetVec3 angularVelocity;

	OptFloat boost;

	ARRAY(StateSetWheel, 4, wheels);
};
typedef struct StateSetCar StateSetCar;

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
typedef struct DropShotObj DropShotObj;

struct BoostPad {
	int pickupTick; // 0 if has respawned
	bool isBig;
	Vec3 position;
};
typedef struct BoostPad BoostPad;


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
typedef struct GameStateObj GameStateObj;

struct StateSetObj {
	ARRAY(StateSetCar, 64, cars);
	ARRAY(StateSetBall, 8, balls);
	bool setAny;
};
typedef struct StateSetObj StateSetObj;

struct SharedMemoryObj {
	unsigned int version;
	
	GameStateObj gameState;
	
	int nTickWaiters;

	StateSetObj stateSetObj;
};
typedef struct SharedMemoryObj SharedMemoryObj;

#ifdef __cplusplus
	}
	}
#endif