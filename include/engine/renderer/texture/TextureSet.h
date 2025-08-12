#pragma once

// Includes
#include "engine/graphics/texture/Texture.h"
#include "engine/graphics/shader/ShaderParameters.h"
#include "engine/renderer/shader/ShaderRendererBinding.h"

namespace gltut
{

// Global classes
class TextureSet
{
public:
	/// Returns the texture associated with the specified slot
	virtual const Texture* getTexture(u32 slot) const noexcept = 0;

	/// Sets a texture to a slot If the slot >= current texture count, does nothing.
	virtual void setTexture(const Texture* texture, u32 slot) noexcept = 0;

	/// Returns the number of textures
	virtual u32 getTextureSlotsCount() const noexcept = 0;

	/// Sets the number of used texture slots
	/// The number is truncated to Texture::TEXTURE_SLOTS
	virtual void setTextureSlotsCount(u32 count) noexcept = 0;

	/// Binds the textures to the slots
	virtual void bind() const noexcept = 0;
};

// End of the namespace gltut
}
