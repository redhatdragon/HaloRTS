#pragma once
#include "IO_API/IO_API.h"
#include <unordered_map>

struct TextureID { uint32_t id; };
struct SoundID { uint32_t id; };

struct TextureCodex {
	static constexpr uint32_t max = 256;
	static void* textures[max];
	static std::unordered_map<std::string, uint32_t> hashes;
	static uint32_t refCount[max];
	static uint32_t textureCount;

	static uint32_t add(const std::string& path) {
		const auto& element = hashes.find(path.c_str());
		if (element != hashes.end()) {
			refCount[element->second]++;
			return { element->second };
		}
		textureCount++;
		hashes[path] = textureCount;
		void* newTexture;
		newTexture = getTexture(path.c_str());
		textures[textureCount] = newTexture;
		return textureCount;
	}

	static void* get(TextureID id) {
		return textures[id.id];
	}
};