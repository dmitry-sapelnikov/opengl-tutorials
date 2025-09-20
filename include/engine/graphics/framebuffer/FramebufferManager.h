// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/ItemManager.h"
#include "engine/graphics/framebuffer/TextureFramebuffer.h"

namespace gltut
{
// Global classes
/// Interface for framebuffer management
class FramebufferManager : public ItemManager<TextureFramebuffer>
{
public:
	/// Returns the default (window) framebuffer
	virtual Framebuffer* getDefault() const noexcept = 0;

	/**
		\brief Creates a texture framebuffer
		\return A new texture framebuffer or nullptr
		if the framebuffer could not be created
	*/
	virtual TextureFramebuffer* create(
		Texture2* color,
		Texture2* depth) noexcept = 0;
};

// End of the namespace gltut
}
