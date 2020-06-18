struct PlayerController {};

#include "IO_API/IO_API.h"
#include "PhysicsEngine.h"
#include "Asset.h"
#include <Entt.h>
#include <iostream>

entt::registry reg;
//std::unique_ptr<Codex> codex;
static constexpr uint32_t max_entities = 100000;
entt::entity entities[max_entities];
uint32_t entityCount = 0;
PhysicsEngine physics;

#include "systems.h"

void appStart() {
	for (auto i = 0; i < 50000; ++i) {
		auto entity = reg.create();
		BodyID bodyID = physics.addBody(i * 64 + 16, 50, 64, 64);
		//physics.setVelocity(bodyID, 2, 5);
		reg.emplace<BodyID>(entity, bodyID);
		reg.emplace<TextureID>(entity, TextureCodex::add("data/Koishi.png"));
	}
	{
		auto entity = reg.create();
		BodyID bodyID = physics.addBody(300, 350, 64, 64);
		reg.emplace<BodyID>(entity, bodyID);
		reg.emplace<TextureID>(entity, TextureCodex::add("data/Koishi.png"));
	}

	auto entity = reg.create();
	reg.emplace<BodyID>(entity, physics.addBody(250, 250, 64, 64));
	reg.emplace<TextureID>(entity, TextureCodex::add("data/Koishi.png"));
	reg.emplace<PlayerController>(entity);
}
void appLoop() {
	static int interval = 0;
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
	
}