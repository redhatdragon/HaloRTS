#pragma once

void systemRendering() {
	const auto& view = reg.view<BodyID, TextureID>();
	for (auto& entity : view) {
		BodyID bodyID = view.get<BodyID>(entity);
		TextureID textureID = view.get<TextureID>(entity);
		Vec2D<int32_t> pos;
		pos = physics.getPos<int32_t>(bodyID);
		const Vec2D<int32_t> siz = physics.getSize<int32_t>(bodyID);
		const void* texture = TextureCodex::get(textureID);
		constexpr int32_t winWidth = 1024, winHeight = 768;
		if (pos.x > winWidth || pos.x + siz.x < 0 ||
			pos.y > winHeight || pos.y + siz.y < 0)
			continue;  //TODO:  Not sure this helps or hinders runtime
		drawTexture(texture, pos.x, pos.y, siz.x, siz.y);
	}
}

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