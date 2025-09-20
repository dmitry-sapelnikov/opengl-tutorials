// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/graphics/framebuffer/TextureFramebuffer.h"

namespace gltut
{

/// Base class for frame buffers
class TextureFramebufferBase : public TextureFramebuffer, public NonCopyable
{
public:
	/// Returns the color texture
	Texture2* getColor() const noexcept final
	{
		return mColor;
	}

	/// Sets the color texture
	void setColor(Texture2* texture) noexcept;

	/// Returns the depth texture
	Texture2* getDepth() const noexcept final
	{
		return mDepth;
	}

	/// Sets the depth texture
	void setDepth(Texture2* texture) noexcept;

	/// Returns the size of the framebuffer
	Point2u getSize() const noexcept final;

private:
	/// Color texture
	Texture2* mColor = nullptr;

	/// Depth texture
	Texture2* mDepth = nullptr;
};

// End of the namespace gltut
}
