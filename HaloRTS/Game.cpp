struct PlayerController {};  //Need to move this somewhere else.

#include "IO_API/IO_API.h"
//#include "PhysicsEngine.h"
#include "PhysicsEngineConvex.h"
#include "Asset.h"
#include <Entt.h>
#include <iostream>

entt::registry reg;
static constexpr uint32_t max_entities = 100000;
// Consider this an array of "IDs" to entities.  Exactly 32 bits large each.
// Therefore no references required.
// Honestly we might not even need this buffer but it might help later on.
entt::entity entities[max_entities];
uint32_t entityCount = 0;
PhysicsEngine physics;

#include "systems.h"

void appStart() {
	static constexpr uint32_t test_count = 5000;
	physics = PhysicsEngine();  // Probably not necessary.
	physics.init();
	for (auto i = 0; i < test_count; i++) {
		auto entity = reg.create();
		entities[entityCount] = entity;
		entityCount++;
		BodyID bodyID = physics.addBodyRect(i * 64 + 16, 50, 64, 64);
		reg.emplace<BodyID>(entity, bodyID);
		reg.emplace<TextureID>(entity, TextureCodex::add("data/Koishi.png"));
		physics.setUserData(bodyID, (void*)entity);  // Casting our entity id to a void*, works on 32 bit+ address spaces.
	}
	{
		auto entity = reg.create();
		entities[entityCount] = entity;
		entityCount++;
		BodyID bodyID = physics.addBodyRect(300, 350, 64, 64);
		reg.emplace<BodyID>(entity, bodyID);
		reg.emplace<TextureID>(entity, TextureCodex::add("data/Koishi.png"));
		physics.setUserData(bodyID, (void*)entity);
		physics.setVelocity(bodyID, 0, -1);
	}

	auto entity = reg.create();
	entities[entityCount] = entity;
	entityCount++;
	BodyID bodyID = physics.addBodyRect(250, 250, 64, 64);
	reg.emplace<BodyID>(entity, bodyID);
	reg.emplace<TextureID>(entity, TextureCodex::add("data/Koishi.png"));
	reg.emplace<PlayerController>(entity);
	physics.setUserData(bodyID, (void*)entity);
}
void appLoop() {
	static unsigned int interval = 0;
	if (interval == 128) {
		std::cout << getFPS() << std::endl;
		interval = 0;
	}
	interval++;
	systemPlayerLogic();
	systemPhysics();
	systemRendering();
}
void appEnd() {
	physics.destroy();
}