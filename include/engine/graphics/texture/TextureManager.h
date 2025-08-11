#pragma once

// Includes
#include "engine/core/ItemManager.h"
#include "engine/graphics/texture/Texture.h"

namespace gltut
{

// Global classes
/// Interface for texture management
class TextureManager : public ItemManager<Texture>
{
public:
	/// Creates a texture with the given parameters
	virtual Texture* create(
		const void* data,
		const Point2u& size,
		TextureFormat format = TextureFormat::RGBA,
		const TextureParameters& parameters = {}) noexcept = 0;

	/// Loads a texture from a file
	virtual Texture* load(
		const char* imagePath,
		const TextureParameters& parameters = {}) noexcept = 0;
};

// End of the namespace gltut
}
