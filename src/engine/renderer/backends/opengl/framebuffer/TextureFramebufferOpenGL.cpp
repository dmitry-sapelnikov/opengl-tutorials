// Includes
#include "TextureFramebufferOpenGL.h"
#include "FramebufferBackupOpenGL.h"
#include "engine/core/Check.h"

namespace gltut
{

TextureFramebufferOpenGL::TextureFramebufferOpenGL(
	Texture* color,
	Texture* depth)
{
	glGenFramebuffers(1, &mId);
	GLTUT_CHECK(mId != 0, "Failed to generate framebuffer");
	setColor(color);
	setDepth(depth);
	validate();
}

TextureFramebufferOpenGL::~TextureFramebufferOpenGL() noexcept
{
	glDeleteFramebuffers(1, &mId);
}

void TextureFramebufferOpenGL::setColor(Texture* texture) noexcept
{
	TextureFramebufferBase::setColor(texture);
	FramebufferBackupOpenGL backup;
	activate();
	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D,
		getColor() != nullptr ? getColor()->getId() : 0,
		0);
}

void TextureFramebufferOpenGL::setDepth(Texture* texture) noexcept
{
	TextureFramebufferBase::setDepth(texture);
	FramebufferBackupOpenGL backup;
	activate();
	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D,
		getDepth() != nullptr ? getDepth()->getId() : 0,
		0);
}

void TextureFramebufferOpenGL::activate() const noexcept
{
	glBindFramebuffer(GL_FRAMEBUFFER, mId);
}

void TextureFramebufferOpenGL::validate() const
{
	FramebufferBackupOpenGL backup;
	activate();
	if (GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		status != GL_FRAMEBUFFER_COMPLETE)
	{
		throw std::runtime_error("Framebuffer is not complete");
	}
}

// End of the namespace gltut
}
