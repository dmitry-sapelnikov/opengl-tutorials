// Includes
#include "TextureTOpenGL.h"
#include "engine/core/Check.h"

namespace gltut
{

// Global functions
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

// End of the namespace gltut
}
