#pragma once

// Includes
#include "engine/core/ItemManager.h"
#include "../../core/ItemManagerT.h"
#include "engine/graphics/texture/TextureManager.h"

namespace gltut
{

class GraphicsDeviceBase;

/// GraphicsDevice base class
class TextureManagerC : public ItemManagerT<TextureManager>
{
public:
	TextureManagerC(GraphicsDeviceBase& device) noexcept :
		mDevice(device)
	{
	}

	Texture* create(
		const void* data,
		u32 width,
		u32 height,
		TextureFormat format,
		const TextureParameters& parameters) noexcept final;

	Texture* load(
		const char* imagePath,
		const TextureParameters& parameters) noexcept final;

private:
	GraphicsDeviceBase& mDevice;
};

// End of the namespace gltut
}
