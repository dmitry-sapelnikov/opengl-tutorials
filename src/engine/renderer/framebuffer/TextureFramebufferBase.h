#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/renderer/framebuffer/TextureFramebuffer.h"

namespace gltut
{

/// Base class for frame buffers
class TextureFramebufferBase : public TextureFramebuffer, public NonCopyable
{
public:
	/// Returns the color texture
	Texture* getColor() const noexcept final
	{
		return mColor;
	}

	/// Sets the color texture
	void setColor(Texture* texture) noexcept;

	/// Returns the depth texture
	Texture* getDepth() const noexcept final
	{
		return mDepth;
	}

	/// Sets the depth texture
	void setDepth(Texture* texture) noexcept;

	/// Returns the size of the framebuffer
	Point2u getSize() const noexcept final;

private:
	/// Color texture
	Texture* mColor = nullptr;

	/// Depth texture
	Texture* mDepth = nullptr;
};

// End of the namespace gltut
}
