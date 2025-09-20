// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include <glad/glad.h>

#include "../../../framebuffer/WindowFramebufferBase.h"

namespace gltut
{
// Global classes
/// Implementation of a window framebuffer using OpenGL
class WindowFramebufferOpenGL final : public WindowFramebufferBase
{
public:
	/// Constructor
	using WindowFramebufferBase::WindowFramebufferBase;

	/// Binds the framebuffer as the current rendering target
	void bind() const noexcept final
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
};

// End of the namespace gltut
}
