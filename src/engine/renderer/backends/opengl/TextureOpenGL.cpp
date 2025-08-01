// Includes
#include "TextureOpenGL.h"
#include "engine/core/Check.h"

namespace gltut
{

static_assert(sizeof(GLuint) == sizeof(u32), "GLuint must be the same size as u32");

// Local functions
namespace
{

u32 toOpenGLFormat(Texture::Format format) noexcept
{
	switch (format)
	{
	case Texture::Format::RGB:
		return GL_RGB;

	case Texture::Format::RGBA:
		return GL_RGBA;

	case Texture::Format::DEPTH:
		return GL_DEPTH_COMPONENT;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(format)
	}
	return 0;
}

u32 toOpenGLFilterMode(Texture::FilterMode filterMode) noexcept
{
	switch (filterMode)
	{
	case Texture::FilterMode::NEAREST:
		return GL_NEAREST;

	case Texture::FilterMode::LINEAR:
		return GL_LINEAR;

	case Texture::FilterMode::NEAREST_MIPMAP_NEAREST:
		return GL_NEAREST_MIPMAP_NEAREST;

	case Texture::FilterMode::LINEAR_MIPMAP:
		return GL_LINEAR_MIPMAP_LINEAR;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(filterMode)
	}
	return 0;
}

u32 toOpenGLWrapMode(Texture::WrapMode wrapMode) noexcept
{
	switch (wrapMode)
	{
	case Texture::WrapMode::REPEAT:
		return GL_REPEAT;

	case Texture::WrapMode::CLAMP_TO_EDGE:
		return GL_CLAMP_TO_EDGE;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(wrapMode)
	}
	return 0;
}

u32 getChannelType(Texture::Format format) noexcept
{
	switch (format)
	{
	case Texture::Format::RGB:
	case Texture::Format::RGBA:
		return GL_UNSIGNED_BYTE;

	case Texture::Format::DEPTH:
		return GL_FLOAT;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(format)
	}
	return 0;
}

} // namespace

// Global classes
TextureOpenGL::TextureOpenGL(
	const void* data,
	u32 width,
	u32 height,
	Texture::Format format,
	Texture::FilterMode minFilter,
	Texture::FilterMode magFilter,
	Texture::WrapMode wrapMode) :

	mFormat(format),
	mMinFilter(minFilter),
	mMagFilter(magFilter),
	mWrapMode(wrapMode),
	mId(0)
{
	GLTUT_CHECK(data != nullptr, "Texture data is null");
	GLTUT_CHECK(width > 0, "Texture width is 0");
	GLTUT_CHECK(height > 0, "Texture height is 0");

	glGenTextures(1, &mId);
	GLTUT_CHECK(mId != 0, "Failed to generate texture");
	GLTUT_CHECK(mId < std::numeric_limits<u32>::max(), "Texture ID is out of 32-bit range");

	//	Get the currently bound texture to restore it after
	GLint currentTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);

	glBindTexture(GL_TEXTURE_2D, mId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toOpenGLFilterMode(minFilter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toOpenGLFilterMode(magFilter));

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		toOpenGLFormat(format),
		width,
		height,
		0,
		toOpenGLFormat(format),
		getChannelType(format),
		data);
	
	if (minFilter == Texture::FilterMode::LINEAR_MIPMAP ||
		minFilter == Texture::FilterMode::NEAREST_MIPMAP_NEAREST ||
		magFilter == Texture::FilterMode::LINEAR_MIPMAP ||
		magFilter == Texture::FilterMode::NEAREST_MIPMAP_NEAREST)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, currentTexture);

	setWrapMode(wrapMode);
}

TextureOpenGL::~TextureOpenGL()
{
	glDeleteTextures(1, &mId);
}

void TextureOpenGL::setWrapMode(WrapMode wrapMode) noexcept
{
	mWrapMode = wrapMode;
	// Get the currently bound texture to restore it after
	GLint currentTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);

	glBindTexture(GL_TEXTURE_2D, mId);
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

void TextureOpenGL::setMinFilterMode(FilterMode mode) noexcept
{
	mMinFilter = mode;
	GLint currentTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toOpenGLFilterMode(mode));
	glBindTexture(GL_TEXTURE_2D, currentTexture);
}

void TextureOpenGL::setMagFilterMode(FilterMode mode) noexcept
{
	mMagFilter = mode;
	GLint currentTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toOpenGLFilterMode(mode));
	glBindTexture(GL_TEXTURE_2D, currentTexture);
}

void TextureOpenGL::bind(u32 slot) const noexcept
{
	GLTUT_ASSERT(slot < TEXTURE_SLOTS);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, mId);
}

// End of the namespace gltut
}
