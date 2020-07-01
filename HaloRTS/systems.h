#pragma once

void systemRendering() {
	const auto& view = reg.view<BodyID, TextureID>();
	for (auto& entity : view) {
		BodyID bodyID = view.get<BodyID>(entity);
		TextureID textureID = view.get<TextureID>(entity);
		Vec2D<double> pos = physics.getPos<double>(bodyID);
		//const Vec2D<int32_t> siz = physics.getSize<int32_t>(bodyID);
		const Vec2D<int32_t> siz = { 64, 64 };
		const void* texture = TextureCodex::get(textureID);
		constexpr int32_t winWidth = 1024, winHeight = 768;
		if (pos.x > winWidth || pos.x + siz.x < 0 ||
			pos.y > winHeight || pos.y + siz.y < 0)
			continue;  //TODO:  Not sure this helps or hinders runtime
		drawTexture(texture, pos.x, pos.y, siz.x, siz.y);
	}
}


// Maybe pixel instead of texel, or we could call it chunk
// I plan on using the term of chunk to describe "intact" portions of the ship which haven't incurred damage, therefore they can be rendered 
// More efficiently as a chunk of 1, rather than a group of many
struct ChunkHealthMap {
	static constexpr uint32_t max_x = 128, max_y = 128;
	uint32_t chunkIndex[max_x * max_y];
	int32_t value[max_x * max_y];
	uint32_t count;
};
struct ChunkArmorMap {
	static constexpr uint32_t max_x = 128, max_y = 128;
	uint32_t chunkIndex[max_x * max_y];
	int32_t value[max_x * max_y];
	uint32_t count;
};
struct ChunkFlammableMap {
	static constexpr uint32_t max_x = 128, max_y = 128;
	uint32_t chunkIndex[max_x * max_y];
	int32_t value[max_x * max_y];
	uint32_t count;
};

//  Assuming each body is AABB.
//  Not calculated by the physics engine.
struct InnerBodies {

};



// Is this the camera control?
// For now it just moves the player but am going to add camera data/logic later
// What player? lol
void systemPlayerLogic() {
	const auto& view = reg.view<BodyID, PlayerController>();
	for (auto& entity : view) {
		BodyID bodyID = view.get<BodyID>(entity);
		int32_t downVel = 0, rightVel = 0;
		constexpr uint32_t speed = 5;
		if (getKeyState('w'))
			downVel -= speed;
		if (getKeyState('s'))
			downVel += speed;
		if (getKeyState('a'))
			rightVel -= speed;
		if (getKeyState('d'))
			rightVel += speed;
		physics.setVelocity(bodyID, rightVel, downVel);

	}
}

void systemPhysics() {
	physics.tick();
}