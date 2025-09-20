#pragma once

// Includes
#include "engine/core/ItemManager.h"
#include "engine/graphics/texture/Texture2.h"
#include "engine/graphics/texture/TextureCubemap.h"
#include "engine/math/Color.h"

namespace gltut
{

// Global classes
/// Interface for texture management
class TextureManager : public ItemManager<Texture>
{
public:
	/// Parameters for loading a texture from a file
	struct LoadParameters
	{
		bool invertChannel[4] = {false, false, false, false};
	};

	/// Creates a texture with the given parameters
	virtual Texture2* create(
		const TextureData& data,
		const TextureParameters& parameters = {}) noexcept = 0;

	/// Loads a texture from a file
	virtual Texture2* load(
		const char* imagePath,
		const TextureParameters& textureParameters = {},
		const LoadParameters& loadParameters = {}) noexcept = 0;

	/// Loads a cubemap texture from 6 files
	virtual TextureCubemap* load(
		const char* plusXAxisImagePath,
		const char* minusXAxisImagePath,
		const char* plusYAxisImagePath,
		const char* minusYAxisImagePath,
		const char* plusZAxisImagePath,
		const char* minusZAxisImagePath,
		const TextureParameters& textureParameters = {},
		const LoadParameters& loadParameters = {}) noexcept = 0;

	/// Creates a solid color texture
	virtual const Texture2* createSolidColor(const Color& color) noexcept = 0;
};

// End of the namespace gltut
}
