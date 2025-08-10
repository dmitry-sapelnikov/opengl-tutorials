#pragma once

// Includes
#include "engine/graphics/framebuffer/Framebuffer.h"

namespace gltut
{

/// Represents a framebuffer that contains textures
class TextureFramebuffer : public Framebuffer
{
	/// Returns the color texture
	virtual Texture* getColor() const noexcept = 0;

	/// Sets the color texture
	virtual void setColor(Texture* texture) noexcept = 0;

	/// Returns the depth texture
	virtual Texture* getDepth() const noexcept = 0;

	/// Sets the depth texture
	virtual void setDepth(Texture* texture) noexcept = 0;
};

// End of the namespace gltut
}
