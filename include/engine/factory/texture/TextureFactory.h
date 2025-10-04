// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/graphics/texture/Texture2.h"

namespace gltut
{
// Global classes
/// The texture factory interface. Creates various textures
class TextureFactory
{
public:
	/// Virtual destructor
	virtual ~TextureFactory() noexcept = default;

	/// Creates a binding between a texture and the window size
	virtual bool createWindowSizeTextureBinding(Texture2* texture) noexcept = 0;

	/// Removes the window-size texture binding for a texture
	virtual bool removeWindowSizeTextureBinding(Texture2* texture) noexcept = 0;

	/// Creates a window-size color texture
	virtual Texture2* createWindowSizeTexture(TextureFormat format) noexcept = 0;
};

// End of the namespace gltut
}
