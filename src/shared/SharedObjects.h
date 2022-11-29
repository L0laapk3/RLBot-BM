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


const unsigned int VERSION_MAJOR = 9;
const unsigned int VERSION_MINOR = 0;

const unsigned int MAX_CARS = 64;
const unsigned int MAX_BALLS = 64;
const unsigned int MAX_BOOST_PADS = 128;
const unsigned int MAX_DROPSHOT_TILES = 140;

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
	unsigned int handbrake : 1;
	unsigned int jump : 1;
	unsigned int boost : 1;
	unsigned int useItem : 1;
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
	unsigned int reset : 1; // true if the wheel had contact after jumping (for flip resets)
};

enum RumblePowerupType {
	NONE = 0,
	HAYMAKER = 1,
	BOOT = 2,
	MAGNETIZER = 3,
	SWAPPER = 4,
	SPIKES = 5,
	GRAPPLING_HOOK = 6,
	POWER_HITTER = 7,
	PLUNGER = 8,
	FREEZE = 9,
	DISRUPTOR = 10,
	TORNADO = 11,
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
	int jumpedAt;
	int flippedAt;

	RumblePowerupType rumblePowerupType;
	int rumblePowerupExpiresAt; // 0 until activated

	// front left, front right, back left, back right
	ARRAY(Wheel, 4, wheels);
	
	unsigned int jumped : 1;
	unsigned int flipped : 1;
	unsigned int superSonic : 1;
	unsigned int demolished : 1;
	unsigned int bot : 1;
	unsigned int RLBotBMControlled : 1;
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

	float ballCharge;
	ARRAY(enum TileState, MAX_DROPSHOT_TILES, tileDamage);
	unsigned int numTiles;
};
typedef struct DropShotObj DropShotObj;

struct BoostPad {
	int pickupTick; // 0 if has respawned
	bool isBig;
	Vec3 position;
};
typedef struct BoostPad BoostPad;


struct GameStateObj {
	int tick;

	union {
		struct {
			unsigned int roundActive : 1;
			unsigned int matchEnded : 1;
		};
		unsigned int flags;
	};

	ARRAY(Car, MAX_CARS, cars);
	unsigned int numCars;

	ARRAY(Ball, MAX_BALLS, balls);
	unsigned int numBalls;

	ARRAY(BoostPad, MAX_BOOST_PADS, boostPads);
	unsigned int numBoostPads;

	bool isDropShot;
	bool isRumble;
	DropShotObj dropShot;
};
typedef struct GameStateObj GameStateObj;

struct StateSetObj {
	ARRAY(StateSetCar, MAX_CARS, cars);
	ARRAY(StateSetBall, MAX_BALLS, balls);
	bool setAny;
};
typedef struct StateSetObj StateSetObj;

struct SharedMemoryObj {
	unsigned int versionMajor, versionMinor;
	
	int nTickWaiters;

	StateSetObj stateSetObj;
	
	GameStateObj gameState;
};
typedef struct SharedMemoryObj SharedMemoryObj;

#ifdef __cplusplus
	}
	}
#endif