#include <IO_API/IO_API.h>  //handles all io such as gfx, threading, networking and input.
#include <DDECS.h>   //custom data driven ECS.
//#include <PhysicsEngineAABB.h>  //custom AABB (40k moving bodies max)
//#include "PhysicsEngineConvex.h"  //uses chipmunk2d as the back end (4k moving bodies max)
#include <FancyMath.h>
#include "Asset.h"  //manages (loads and unloads) resources while sharing a single id per resource.
#include <iostream>
#include <time.h>
#include <stdio.h>

//#include "systems/systems.h"  //example "systems" used for ecs.

struct ThreadPool* threadPool;  //needs further debugging

// Kat's Global Variables
static const unsigned int MAX_SHIP_COUNT = 100;
unsigned int shipCount = 0;
long unsigned int voxelID = 0;
Ship* ships[MAX_SHIP_COUNT];

void* canvasPtr;


//void foo(void*) {

//}

void appStart() {
	srand(time(NULL));

	auto c = clock();

	std::cout << "Pre initialization finished in " << c << " miliseconds." << std::endl;
	std::cout << "Initializing app...    ";

	physics.init();
	canvasPtr = getBlankTexture(1024, 768);

	//threadPool = ThreadPoolCreate(8);
	//ThreadPoolGiveTask(threadPool, foo, NULL);

	registerComponents();

	c = clock()-c;
	std::cout << "Done!  \nInitialized in " << c << " miliseconds." << std::endl;
}
void appLoop() {
	physics.tick();
	systemDisplay();
	systemPlayer();
	systemDamage();
	systemDead();
}
void appEnd() {
	//ThreadPoolDestroy(threadPool);
}

// Kat's Stuff
struct halcyonClassCruiser {
	int voxelSubimg[HALCYON_CLASS_WIDTH][HALCYON_CLASS_HEIGHT];
	bool detached[HALCYON_CLASS_WIDTH][HALCYON_CLASS_HEIGHT];
	int centerOfMassX;
	int centerOfMassY;
	int rotationDegree;

	BodyID pixelClusterBody;
};

struct ColorRGBA {
	uint8_t r, g, b, a;
	ColorRGBA() {}
	ColorRGBA(uint32_t val) { memcpy(&r, &val, sizeof(uint32_t)); }  //TODO: could be better optimized with custom asssembly or something maybe >.>
};

void shipBuilder(SHIP_TYPE type) {

	ships[shipCount] = new Ship();
	ships[shipCount]->SHIP_TYPE = type;
	unsigned int voxelCount = 0;
	unsigned int imageWidth;
	unsigned int imageHeight;
	void* img = nullptr;

	switch (type) {
		case HALCYON_CLASS:
			img = getTexture("HalyconClass.png");
			break;
		case PARIS_CLASS:
			img = getTexture("ParisClass.png");
			imageWidth = 535; imageHeight = 162;
			break;
		case CAS_CLASS:
			img = getTexture("CasClass.png");
			imageWidth = 2674; imageHeight = 350;
			break;
		case WARRIOR_CLASS:
			img = getTexture("WarriorClass.png");
			imageWidth = 614; imageHeight = 146;
			break;
		case DARING_CLASS:
			img = getTexture("DaringClass.png");
			imageWidth = 517; imageHeight = 135;
			break;
		}

	Vec2D<int32_t> pos;
	for (pos.x = 0; pos.x < imageWidth; pos.x++) {
		for (pos.y = 0; pos.y < imageHeight; pos.y++) {
			ColorRGBA c = (ColorRGBA)getPixelRGBA(img, pos.x, pos.y);
			if (c.a != 0) {
				Voxel voxel;
				memcpy(&voxel.r, &c.r, sizeof(ColorRGBA));
				voxel.offset += pos;
				voxel.ID = voxelID;
				ships[shipCount]->voxels[voxelCount] = voxel;
				voxelCount++;
				voxelID++;
			}
		}
	}

	releaseTexture(img);
	ship[shipCount]->voxelCount = voxelCount;
	shipCount++;
}

void shipStep() {

	for (unsigned int i = 0; i < MAX_SHIP_COUNT; i++) {
		void* texture = getBlankTexture(w, h);
		Ship ship = ships[i];
		ship.x += ship.velocityX;
		ship.y += ship.velocityY; //I'd use a cluster ID instead of having the ship store it's own physics data.
		//I'd also consider not using object difinitions specific to ships maybe.
		unsigned int voxCount = ship->voxCount;
		for (unsigned int j = 0; j < voxCount; j++) {
			Voxel voxel = ship.voxel[j];
			vox.x += ship.velocityX;
			vox.y += ship.velocityY;
			vox.angle += vox.rotSpeed;
			if (vox.angle >= 360) {
				vox.angle = 0;
			}
			long long drawPosX = lengthdir_x(distFromCenterOfMass, angle) + vox.x;
			long long drawPosY = lengthdir_y(distFromCenterOfMass, angle) + vox.y;
			// Draw The Voxels
			setPixel(texture, drawPosX, drawPosY, vox.red, vox.green, vox.blue, vox.alpha);

		}
		//We could just use drawTexture if you'd rather
		drawTexture(texture, x, y);
		//drawSurface(surface);
		//delete surface;
	}
}

class Voxel() {
public:

	long int x;
	long int y;
	float rotSpeed;
	float angle;
	uint8_t r, g, b, a;
	int xOffset;
	int yOffset;

private:
}