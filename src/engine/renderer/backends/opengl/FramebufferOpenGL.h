#pragma once

// Includes
#include <glad/glad.h>
#include "../../framebuffer/FramebufferBase.h"

namespace gltut
{

/// A RAII class to backup the currently bound framebuffer
class FramebufferOpenGLBackup
{
public:
	FramebufferOpenGLBackup() noexcept
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &mFramebuffer);
	}

	~FramebufferOpenGLBackup() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
	}
private:
	GLint mFramebuffer = 0;
};

class FramebufferOpenGL final : public FramebufferBase
{
public:
	/**
		Constructor
		\throw std::runtime_error If the framebuffer could not be created
	*/
	FramebufferOpenGL(
		Texture* color,
		Texture* depth);

	/// Destructor
	~FramebufferOpenGL() noexcept final;

	/// Sets the color texture
	void setColor(Texture* texture) noexcept final;

	/// Sets the depth texture
	void setDepth(Texture* texture) noexcept final;

	/// Activates the framebuffer as the current rendering target
	void activate() const noexcept final;

private:
	void validate() const;

	/// Framebuffer ID
	GLuint mId = 0;
};

// End of the namespace gltut
}
