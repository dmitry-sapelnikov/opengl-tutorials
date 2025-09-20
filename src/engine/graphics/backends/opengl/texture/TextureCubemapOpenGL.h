#pragma once

// Includes
#include "TextureTOpenGL.h"
#include "engine/graphics/texture/TextureCubemap.h"

namespace gltut
{

// Global classes
/// OpenGL implementation of a cubemap texture
class TextureCubemapOpenGL final : public TextureTOpenGL<TextureCubemap, GL_TEXTURE_CUBE_MAP>
{
public:
	/**
		Constructor
		\throw std::runtime_error If the texture could not be created
	*/
	TextureCubemapOpenGL(
		const TextureData& minusXData,
		const TextureData& plusXData,
		const TextureData& minusYData,
		const TextureData& plusYData,
		const TextureData& minusZData,
		const TextureData& plusZData,
		const TextureParameters& parameters);
};

// End of the namespace gltut
}
