#pragma once

// Includes
#include "engine/renderer/Texture.h"

namespace gltut
{
///	Represents a framebuffer
/// A framebuffer is a collection of textures that
/// can be used for off-screen rendering.
class Framebuffer
{
public:
	/// Virtual destructor
	virtual ~Framebuffer() noexcept = default;

	/// Returns the color texture
	virtual Texture* getColor() const noexcept = 0;

	/// Sets the color texture
	virtual void setColor(Texture* texture) noexcept = 0;

	/// Returns the depth texture
	virtual Texture* getDepth() const noexcept = 0;

	/// Sets the depth texture
	virtual void setDepth(Texture* texture) noexcept = 0;

	/// Activates the framebuffer as the current rendering target
	virtual void activate() const noexcept = 0;
};

// End of the namespace gltut
}
