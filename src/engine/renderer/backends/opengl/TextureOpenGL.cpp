// Includes
#include "TextureOpenGL.h"

#include <glad/glad.h>
#include "engine/core/Check.h"

namespace gltut
{

static_assert(sizeof(GLuint) == sizeof(u32), "GLuint must be the same size as u32");

// Global classes
TextureOpenGL::TextureOpenGL(
	const u8* data,
	u32 width,
	u32 height,
	u32 datachannelCount)
{
	GLTUT_CHECK(data != nullptr, "Texture data is null")
	GLTUT_CHECK(width > 0, "Texture width is 0")
	GLTUT_CHECK(height > 0, "Texture height is 0")
	GLTUT_CHECK(
		datachannelCount == 3 || datachannelCount == 4,
		"Texture data channels count must be 3 or 4")

	glGenTextures(1, &mTexture);
	GLTUT_CHECK(mTexture != 0, "Failed to generate texture")

	//	Get the currently bound texture to restore it after
	GLint currentTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);

	glBindTexture(GL_TEXTURE_2D, mTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		datachannelCount == 3 ? GL_RGB : GL_RGBA,
		width,
		height,
		0,
		datachannelCount == 3 ? GL_RGB : GL_RGBA,
		GL_UNSIGNED_BYTE,
		data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, currentTexture);
}

TextureOpenGL::~TextureOpenGL()
{
	glDeleteTextures(1, &mTexture);
}

Texture::WrapMode TextureOpenGL::getWrapMode() const noexcept
{
	return mWrapMode;
}

void TextureOpenGL::setWrapMode(WrapMode wrapMode) noexcept
{
	mWrapMode = wrapMode;
	// Get the currently bound texture to restore it after
	GLint currentTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);

	glBindTexture(GL_TEXTURE_2D, mTexture);
	switch (wrapMode)
	{
	case WrapMode::REPEAT:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	break;

	case WrapMode::CLAMP_TO_EDGE:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	break;

	GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(wrapMode)
	}

	glBindTexture(GL_TEXTURE_2D, currentTexture);
}

void TextureOpenGL::bind(u32 slot) const noexcept
{
	GLTUT_ASSERT(slot < 32);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}

// End of the namespace gltut
}
