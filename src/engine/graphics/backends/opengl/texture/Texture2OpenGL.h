#pragma once

// Includes
#include <string>
#include <glad/glad.h>
#include "engine/core/NonCopyable.h"
#include "engine/core/Types.h"
#include "engine/graphics/texture/Texture2.h"
#include "TextureTOpenGL.h"

namespace gltut
{

class Texture2OpenGL final : public TextureTOpenGL<Texture2, GL_TEXTURE_2D>
{
public:
	/**
		Constructor
		\throw std::runtime_error If the shader could not be created
	*/
	Texture2OpenGL(
		const TextureData& data,
		const TextureParameters& parameters);

	/// Returns the texture size
	const Point2u& getSize() const noexcept final
	{
		return mSize;
	}

	/// Returns the texture format
	TextureFormat getFormat() const noexcept final
	{
		return mFormat;
	}

	/// Sets the size of the texture, recreating it. The existing texture data will be lost.
	void setSize(const Point2u& size) noexcept final;

private:
	void create(const void* data) noexcept;

	/// Texture size
	Point2u mSize;

	/// Texture format
	TextureFormat mFormat;
};

// End of the namespace gltut
}
