// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/Check.h"
#include <glad/glad.h>

namespace gltut
{

/// A RAII class to backup the currently bound texture of a specific type
class TextureBackupOpenGL
{
public:
	/// Constructor, saves the currently bound texture of the given type
	TextureBackupOpenGL(GLenum textureType) noexcept :
		mTextureType(textureType)
	{
		GLTUT_ASSERT(
			textureType == GL_TEXTURE_2D ||
			textureType == GL_TEXTURE_CUBE_MAP ||
			textureType == GL_TEXTURE_3D);
		glGetIntegerv(mTextureType, &mTexture);
	}

	/// Destructor, restores the previously bound texture
	~TextureBackupOpenGL() noexcept
	{
		glBindTexture(mTextureType, mTexture);
	}

private:
	/// The texture type
	GLenum mTextureType = 0;

	/// The texture id
	GLint mTexture = 0;
};

// End of the namespace gltut
}
