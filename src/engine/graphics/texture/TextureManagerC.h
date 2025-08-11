#pragma once

// Includes
#include <unordered_map>
#include "engine/core/ItemManager.h"
#include "../../core/ItemManagerT.h"
#include "engine/graphics/texture/TextureManager.h"

namespace gltut
{

/// GraphicsDevice base class
class GraphicsDeviceBase;

/// Implementation of the TextureManager interface
class TextureManagerC : public ItemManagerT<TextureManager>
{
public:
	/// Constructor
	TextureManagerC(GraphicsDeviceBase& device) noexcept :
		mDevice(device)
	{
	}

	/// Creates a texture from raw data
	Texture* create(
		const void* data,
		const Point2u& size,
		TextureFormat format,
		const TextureParameters& parameters) noexcept final;

	/// Loads a texture from an image file
	Texture* load(
		const char* imagePath,
		const TextureParameters& parameters) noexcept final;

	/// Creates a solid color texture
	const Texture* createSolidColor(const Color& color) noexcept final;

private:
	/// Reference to the graphics device
	GraphicsDeviceBase& mDevice;

	/// Solid color textures
	std::unordered_map<u32, const Texture*> mSolidColorTextures;
};

// End of the namespace gltut
}
