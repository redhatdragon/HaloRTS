#pragma once

#include "FlatBuffer.h"
#include "Math.h"
#include <time.h>

//Perhaps we should include PhysicsEngineAABB.h and hide our data/logic inside it instead?

struct BodyPointCluster {
	Vec2D<int32_t> pos, vel;
	std::vector<Vec2D<int16_t>> relativePoints;
	//Relative AABB body used to help broad phase detection.
	//Should we use a circle instead?
	Vec2D<int32_t> AABB_Width;

	__forceinline void simulate() {
		
	}
	__forceinline void reverseSimulate() {
		
	}
	__forceinline bool collidesWith(BodyPointCluster& other) {
		
	}
};

struct BodyID {
	uint32_t id;
};

class PhysicsEngine {
public:

};