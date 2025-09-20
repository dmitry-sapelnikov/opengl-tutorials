// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include <array>

#include "engine/core/NonCopyable.h"
#include "engine/graphics/GraphicsDevice.h"
#include "engine/renderer/texture/TextureSet.h"

namespace gltut
{

// Global classes
class TextureSetC final : public TextureSet, public NonCopyable
{
public:
	/// Constructor
	explicit TextureSetC(
		GraphicsDevice& device,
		u32 textureSlotsCount) :
		mDevice(device)
	{
		mTextures.fill(nullptr);
		setTextureSlotsCount(textureSlotsCount);
	}

	/// Returns the texture associated with the specified slot
	const Texture* getTexture(u32 slot) const noexcept final;

	/// Sets a texture to a slot If the slot >= current texture count, does nothing.
	void setTexture(const Texture* texture, u32 slot) noexcept final;

	/// Returns the number of textures
	u32 getTextureSlotsCount() const noexcept final;

	/// Sets the number of used texture slots
	/// The number is truncated to Texture::TEXTURE_SLOTS
	void setTextureSlotsCount(u32 count) noexcept final;

	/// Binds the textures to the slots
	void bind() const noexcept final;

private:
	/// Reference to the graphics device
	GraphicsDevice& mDevice;

	/// Texture slots
	std::array<const Texture*, Texture::TEXTURE_SLOTS> mTextures;

	/// The number of texture slots
	u32 mTextureSlotsCount = 0;
};

// End of the namespace gltut
}
