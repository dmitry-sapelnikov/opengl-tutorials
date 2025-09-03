#pragma once

// Includes
#include "engine/graphics/texture/TextureCubemap.h"
#include "TextureTOpenGL.h"

namespace gltut
{

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
