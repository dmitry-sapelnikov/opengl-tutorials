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
	doSetColor(color);
	doSetDepth(depth);
	GLTUT_CHECK(isValid(), "Framebuffer is not valid");
}

TextureFramebufferOpenGL::~TextureFramebufferOpenGL() noexcept
{
	glDeleteFramebuffers(1, &mId);
}

void TextureFramebufferOpenGL::setColor(Texture* texture) noexcept
{
	Texture* prevColor = getColor();
	doSetColor(texture);
	if (!isValid())
	{
		doSetColor(prevColor);
	}
}

void TextureFramebufferOpenGL::setDepth(Texture* texture) noexcept
{
	Texture* prevDepth = getDepth();
	doSetDepth(texture);
	if (!isValid())
	{
		doSetDepth(prevDepth);
	}
}

void TextureFramebufferOpenGL::doSetColor(Texture* texture) noexcept
{
	TextureFramebufferBase::setColor(texture);
	FramebufferBackupOpenGL backup;
	activate();
	const Texture* color = getColor();
	if (color != nullptr)
	{
		glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D,
			getColor()->getId(),
			0);
	}
	else
	{
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
}

void TextureFramebufferOpenGL::doSetDepth(Texture* texture) noexcept
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

bool TextureFramebufferOpenGL::isValid() const noexcept
{
	FramebufferBackupOpenGL backup;
	activate();
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

// End of the namespace gltut
}
