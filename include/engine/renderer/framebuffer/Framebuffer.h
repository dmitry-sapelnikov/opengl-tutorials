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

	/// Returns the size of the framebuffer
	virtual Point2u getSize() const noexcept = 0;

	/// Binds the framebuffer as the current rendering target
	virtual void bind() const noexcept = 0;
};

// End of the namespace gltut
}
