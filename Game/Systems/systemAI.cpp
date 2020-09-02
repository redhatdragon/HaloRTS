#include "systemAI.h"
#include "systems.h"

struct AI {
	uint8_t team : 4;
	uint8_t importance : 4;

	uint8_t seekBias : 1;
	uint8_t fleeBias : 1;
};

struct Path {
	FlatBuffer<Vec2D<int32_t>, 64> points;
	uint8_t currentIndex;
};

void systemAI() {

}