#pragma once

// Includes
#include <glad/glad.h>
#include "engine/graphics/texture/Texture.h"
#include "engine/core/NonCopyable.h"
#include "engine/core/Check.h"
#include "TextureBackupOpenGL.h"

namespace gltut
{

static_assert(sizeof(GLuint) == sizeof(u32), "GLuint must be the same size as u32");

// Global functions
/// Converts a TextureFormat to an OpenGL format
u32 toOpenGLFormat(TextureFormat format) noexcept;

/// Converts a TextureFilterMode to an OpenGL filter mode
u32 toOpenGLFilterMode(TextureFilterMode filterMode) noexcept;

/// Converts a TextureWrapMode to an OpenGL wrap mode
u32 toOpenGLWrapMode(TextureWrapMode wrapMode) noexcept;

/// Converts a TextureFormat to an OpenGL channel type
u32 getChannelType(TextureFormat format) noexcept;

// Global classes
/// Template class for OpenGL textures
template <typename TextureInterfaceType, GLenum glTextureType>
class TextureTOpenGL : public TextureInterfaceType, public NonCopyable
{
	static_assert(
		glTextureType == glTextureType ||
		glTextureType == GL_TEXTURE_CUBE_MAP ||
		glTextureType == GL_TEXTURE_3D,
		"glTextureType must be glTextureType, GL_TEXTURE_CUBE_MAP or GL_TEXTURE_3D");

public:
	/**
		Constructor
		\note IMPORTANT: don't forget to call updateMipmap()
		in the derived class after creation of the texture data
	*/
	TextureTOpenGL(const TextureParameters& parameters) :
		mParameters(parameters),
		mId(0)
	{
		glGenTextures(1, &mId);
		GLTUT_CHECK(mId != 0, "Failed to generate texture");
		//GLTUT_CHECK(mId < std::numeric_limits<u32>::max(), "Texture ID is out of 32-bit range");
		if (mId > std::numeric_limits<u32>::max())
		{
		}
		
		setMinFilterMode(parameters.minFilter, false);
		setMagFilterMode(parameters.magFilter, false);
		setWrapMode(parameters.wrapMode);
	}

	~TextureTOpenGL() noexcept
	{
		glDeleteTextures(1, &mId);
	}

	u32 getId() const noexcept final
	{
		return static_cast<u32>(mId);
	}

	/// Returns the texture parameters
	const TextureParameters& getParameters() const noexcept final
	{
		return mParameters;
	}

	void setParameters(const TextureParameters& parameters) noexcept final
	{
		setMinFilterMode(parameters.minFilter, true);
		setMagFilterMode(parameters.magFilter, true);
		setWrapMode(parameters.wrapMode);
	}

	void setWrapMode(TextureWrapMode wrapMode) noexcept
	{
		mParameters.wrapMode = wrapMode;
		TextureBackupOpenGL backup(glTextureType);

		glBindTexture(glTextureType, mId);
		switch (wrapMode)
		{
		case TextureWrapMode::REPEAT:
		{
			glTexParameteri(glTextureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(glTextureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
			if constexpr (glTextureType == GL_TEXTURE_3D || glTextureType == GL_TEXTURE_CUBE_MAP)
			{
				glTexParameteri(glTextureType, GL_TEXTURE_WRAP_R, GL_REPEAT);
			}
		}
		break;

		case TextureWrapMode::CLAMP_TO_EDGE:
		{
			glTexParameteri(glTextureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(glTextureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			if constexpr (glTextureType == GL_TEXTURE_3D || glTextureType == GL_TEXTURE_CUBE_MAP)
			{
				glTexParameteri(glTextureType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			}
		}
		break;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(wrapMode)
		}
	}

	void bind(u32 slot) const noexcept final
	{
		GLTUT_ASSERT(slot < Texture::TEXTURE_SLOTS);
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(glTextureType, mId);
	}

protected:
	void updateMipmap()
	{
		if (mParameters.minFilter == TextureFilterMode::LINEAR_MIPMAP ||
			mParameters.minFilter == TextureFilterMode::NEAREST_MIPMAP_NEAREST ||
			mParameters.magFilter == TextureFilterMode::LINEAR_MIPMAP ||
			mParameters.magFilter == TextureFilterMode::NEAREST_MIPMAP_NEAREST)
		{
			glGenerateMipmap(glTextureType);
		}
	}

private:
	void setMinFilterMode(TextureFilterMode mode, bool mipmap) noexcept
	{
		TextureBackupOpenGL backup(glTextureType);

		mParameters.minFilter = mode;
		glBindTexture(glTextureType, mId);
		glTexParameteri(glTextureType, GL_TEXTURE_MIN_FILTER, toOpenGLFilterMode(mode));
		if (mipmap)
		{
			updateMipmap();
		}
	}

	void setMagFilterMode(TextureFilterMode mode, bool mipmap) noexcept
	{
		TextureBackupOpenGL backup(glTextureType);

		mParameters.magFilter = mode;
		glBindTexture(glTextureType, mId);
		glTexParameteri(glTextureType, GL_TEXTURE_MAG_FILTER, toOpenGLFilterMode(mode));
		if (mipmap)
		{
			updateMipmap();
		}
	}

	/// Texture parameters
	TextureParameters mParameters;

	/// Texture ID
	GLuint mId;
};

// End of the namespace gltut
}
