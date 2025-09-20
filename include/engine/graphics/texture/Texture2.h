// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/graphics/texture/Texture.h"

namespace gltut
{

/// Represents a 2-dimensional texture
class Texture2 : public Texture
{
public:
	/// Returns the texture format
	virtual TextureFormat getFormat() const noexcept = 0;

	/// Returns the size of the texture
	virtual const Point2u& getSize() const noexcept = 0;

	/// Sets the size of the texture, recreating it. The existing texture data will be lost.
	virtual void setSize(const Point2u& size) noexcept = 0;

	/// Returns the aspect ratio of the texture
	float getAspectRatio() const noexcept
	{
		const auto& size = getSize();
		return size.y != 0 ? static_cast<float>(size.x) / static_cast<float>(size.y) : 1.0f;
	}
};

// End of the namespace gltut
}
