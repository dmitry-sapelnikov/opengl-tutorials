// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "FramebufferManagerC.h"
#include <string>
#include "../GraphicsDeviceBase.h"

namespace gltut
{

// Global classes
Framebuffer* FramebufferManagerC::getDefault() const noexcept
{
	return mDevice.getDefaultFramebuffer();
}

TextureFramebuffer* FramebufferManagerC::create(
	Texture2* color,
	Texture2* depth) noexcept
{
	TextureFramebuffer* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = add(mDevice.createBackendTextureFramebuffer(
			color,
			depth));
	GLTUT_CATCH_ALL_END("Failed to create framebuffer")
	return result;
}

// End of the namespace gltut
}
