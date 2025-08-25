// Includes
#include "TextureOpenGL.h"
#include "engine/core/Check.h"

namespace gltut
{

static_assert(sizeof(GLuint) == sizeof(u32), "GLuint must be the same size as u32");

// Local functions
namespace
{

u32 toOpenGLFormat(TextureFormat format) noexcept
{
	switch (format)
	{
	case TextureFormat::R:
		return GL_RED;

	case TextureFormat::RGB:
		return GL_RGB;

	case TextureFormat::RGBA:
		return GL_RGBA;

	case TextureFormat::FLOAT:
		return GL_DEPTH_COMPONENT;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(format)
	}
	return 0;
}

u32 toOpenGLFilterMode(TextureFilterMode filterMode) noexcept
{
	switch (filterMode)
	{
	case TextureFilterMode::NEAREST:
		return GL_NEAREST;

	case TextureFilterMode::LINEAR:
		return GL_LINEAR;

	case TextureFilterMode::NEAREST_MIPMAP_NEAREST:
		return GL_NEAREST_MIPMAP_NEAREST;

	case TextureFilterMode::LINEAR_MIPMAP:
		return GL_LINEAR_MIPMAP_LINEAR;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(filterMode)
	}
	return 0;
}

u32 toOpenGLWrapMode(TextureWrapMode wrapMode) noexcept
{
	switch (wrapMode)
	{
	case TextureWrapMode::REPEAT:
		return GL_REPEAT;

	case TextureWrapMode::CLAMP_TO_EDGE:
		return GL_CLAMP_TO_EDGE;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(wrapMode)
	}
	return 0;
}

u32 getChannelType(TextureFormat format) noexcept
{
	switch (format)
	{
	case TextureFormat::R:
	case TextureFormat::RGB:
	case TextureFormat::RGBA:
		return GL_UNSIGNED_BYTE;

	case TextureFormat::FLOAT:
		return GL_FLOAT;

	GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(format)
	}
	return 0;
}

} // namespace

// Global classes
TextureOpenGL::TextureOpenGL(
	const void* data,
	const Point2u& size,
	TextureFormat format,
	const TextureParameters& parameters) :

	mSize(size),
	mFormat(format),
	mId(0)
{
	GLTUT_CHECK(mSize.x > 0, "Texture width is 0");
	GLTUT_CHECK(mSize.y > 0, "Texture height is 0");

	//	Get the currently bound texture to restore it after
	GLint currentTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);

	glGenTextures(1, &mId);
	GLTUT_CHECK(mId != 0, "Failed to generate texture");
	GLTUT_CHECK(mId < std::numeric_limits<u32>::max(), "Texture ID is out of 32-bit range");

	glBindTexture(GL_TEXTURE_2D, mId);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		toOpenGLFormat(format),
		mSize.x,
		mSize.y,
		0,
		toOpenGLFormat(format),
		getChannelType(format),
		data);

	setParameters(parameters);
	glBindTexture(GL_TEXTURE_2D, currentTexture);
}

TextureOpenGL::~TextureOpenGL()
{
	glDeleteTextures(1, &mId);
}

void TextureOpenGL::setParameters(const TextureParameters& parameters) noexcept
{
	setMinFilterMode(parameters.minFilter);
	setMagFilterMode(parameters.magFilter);
	setWrapMode(parameters.wrapMode);
}

void TextureOpenGL::setWrapMode(TextureWrapMode wrapMode) noexcept
{
	mParameters.wrapMode = wrapMode;
	// Get the currently bound texture to restore it after
	GLint currentTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);

	glBindTexture(GL_TEXTURE_2D, mId);
	switch (wrapMode)
	{
	case TextureWrapMode::REPEAT:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	break;

	case TextureWrapMode::CLAMP_TO_EDGE:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	break;

	GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(wrapMode)
	}

	glBindTexture(GL_TEXTURE_2D, currentTexture);
}

void TextureOpenGL::setMinFilterMode(TextureFilterMode mode) noexcept
{
	mParameters.minFilter = mode;
	GLint currentTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toOpenGLFilterMode(mode));
	updateMipmap();
	glBindTexture(GL_TEXTURE_2D, currentTexture);
}

void TextureOpenGL::setMagFilterMode(TextureFilterMode mode) noexcept
{
	mParameters.magFilter = mode;
	GLint currentTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toOpenGLFilterMode(mode));
	updateMipmap();
	glBindTexture(GL_TEXTURE_2D, currentTexture);
}

void TextureOpenGL::bind(u32 slot) const noexcept
{
	GLTUT_ASSERT(slot < TEXTURE_SLOTS);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, mId);
}

void TextureOpenGL::updateMipmap()
{
	if (mParameters.minFilter == TextureFilterMode::LINEAR_MIPMAP ||
		mParameters.minFilter == TextureFilterMode::NEAREST_MIPMAP_NEAREST ||
		mParameters.magFilter == TextureFilterMode::LINEAR_MIPMAP ||
		mParameters.magFilter == TextureFilterMode::NEAREST_MIPMAP_NEAREST)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

// End of the namespace gltut
}
