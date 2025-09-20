#pragma once

// Includes
#include <glad/glad.h>

namespace gltut
{
// Global classes
/// A RAII class to backup the currently bound framebuffer
class FramebufferBackupOpenGL
{
public:
	/// Constructor. Backs up the currently bound framebuffer
	FramebufferBackupOpenGL() noexcept
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &mFramebuffer);
	}

	/// Destructor. Restores the previously bound framebuffer
	~FramebufferBackupOpenGL() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
	}

private:
	/// The previously bound framebuffer
	GLint mFramebuffer = 0;
};

// End of the namespace gltut
}
