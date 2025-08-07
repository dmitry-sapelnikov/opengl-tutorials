#pragma once

// Includes
#include <glad/glad.h>

namespace gltut
{

/// A RAII class to backup the currently bound framebuffer
class FramebufferBackupOpenGL
{
public:
	FramebufferBackupOpenGL() noexcept
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &mFramebuffer);
	}

	~FramebufferBackupOpenGL() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
	}
private:
	GLint mFramebuffer = 0;
};

// End of the namespace gltut
}
