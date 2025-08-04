// Includes
#include "FramebufferOpenGL.h"
#include "engine/core/Check.h"

namespace gltut
{

FramebufferOpenGL::FramebufferOpenGL(
	Texture* color,
	Texture* depth)
{
	glGenFramebuffers(1, &mId);
	GLTUT_CHECK(mId != 0, "Failed to generate framebuffer");
	setColor(color);
	setDepth(depth);
	validate();
}

FramebufferOpenGL::~FramebufferOpenGL() noexcept
{
	glDeleteFramebuffers(1, &mId);
}

void FramebufferOpenGL::setColor(Texture* texture) noexcept
{
	FramebufferBase::setColor(texture);
	FramebufferOpenGLBackup backup;
	activate();
	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D,
		getColor() != nullptr ? getColor()->getId() : 0,
		0);
}

void FramebufferOpenGL::setDepth(Texture* texture) noexcept
{
	FramebufferBase::setDepth(texture);
	FramebufferOpenGLBackup backup;
	activate();
	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D,
		getDepth() != nullptr ? getDepth()->getId() : 0,
		0);
}

void FramebufferOpenGL::activate() const noexcept
{
	glBindFramebuffer(GL_FRAMEBUFFER, mId);
}

void FramebufferOpenGL::validate() const
{
	FramebufferOpenGLBackup backup;
	activate();
	if (GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		status != GL_FRAMEBUFFER_COMPLETE)
	{
		throw std::runtime_error("Framebuffer is not complete");
	}
}

// End of the namespace gltut
}
