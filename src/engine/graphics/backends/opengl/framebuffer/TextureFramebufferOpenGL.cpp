// Includes
#include "TextureFramebufferOpenGL.h"
#include "FramebufferBackupOpenGL.h"
#include "engine/core/Check.h"

namespace gltut
{

TextureFramebufferOpenGL::TextureFramebufferOpenGL(
	Texture2* color,
	Texture2* depth)
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

void TextureFramebufferOpenGL::setColor(Texture2* texture) noexcept
{
	Texture2* prevColor = getColor();
	doSetColor(texture);
	if (!isValid())
	{
		doSetColor(prevColor);
	}
}

void TextureFramebufferOpenGL::setDepth(Texture2* texture) noexcept
{
	Texture2* prevDepth = getDepth();
	doSetDepth(texture);
	if (!isValid())
	{
		doSetDepth(prevDepth);
	}
}

void TextureFramebufferOpenGL::doSetColor(Texture2* texture) noexcept
{
	TextureFramebufferBase::setColor(texture);
	FramebufferBackupOpenGL backup;
	bind();
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

void TextureFramebufferOpenGL::doSetDepth(Texture2* texture) noexcept
{
	TextureFramebufferBase::setDepth(texture);
	FramebufferBackupOpenGL backup;
	bind();
	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D,
		getDepth() != nullptr ? getDepth()->getId() : 0,
		0);
}

void TextureFramebufferOpenGL::bind() const noexcept
{
	glBindFramebuffer(GL_FRAMEBUFFER, mId);
}

bool TextureFramebufferOpenGL::isValid() const noexcept
{
	FramebufferBackupOpenGL backup;
	bind();
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

// End of the namespace gltut
}
