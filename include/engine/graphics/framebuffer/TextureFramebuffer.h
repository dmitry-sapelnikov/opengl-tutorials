#pragma once

// Includes
#include "engine/graphics/framebuffer/Framebuffer.h"

namespace gltut
{
// Global classes
/// Represents a framebuffer that contains textures
class TextureFramebuffer : public Framebuffer
{
	/// Returns the color texture
	virtual Texture2* getColor() const noexcept = 0;

	/// Sets the color texture
	virtual void setColor(Texture2* texture) noexcept = 0;

	/// Returns the depth texture
	virtual Texture2* getDepth() const noexcept = 0;

	/// Sets the depth texture
	virtual void setDepth(Texture2* texture) noexcept = 0;
};

// End of the namespace gltut
}
