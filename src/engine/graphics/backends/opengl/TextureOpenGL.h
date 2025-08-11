#pragma once

// Includes
#include <string>
#include <glad/glad.h>
#include "engine/core/NonCopyable.h"
#include "engine/core/Types.h"
#include "engine/graphics/texture/Texture.h"

namespace gltut
{

class TextureOpenGL final : public Texture, public NonCopyable
{
public:
	/**
		Constructor
		\throw std::runtime_error If the shader could not be created
	*/
	TextureOpenGL(
		const void* data,
		const Point2u& size,
		TextureFormat format,
		const TextureParameters& parameters);

	/// Destructor
	~TextureOpenGL() noexcept final;

	/// Returns the texture ID
	u32 getId() const noexcept final
	{
		return static_cast<u32>(mId);
	}

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

	/// Returns the texture parameters
	const TextureParameters& getParameters() const noexcept final
	{
		return mParameters;
	}

	/// Sets the texture parameters
	void setParameters(const TextureParameters& parameters) noexcept final;

	/// Binds the texture
	void bind(u32 slot) const noexcept final;

private:
	void setMinFilterMode(TextureFilterMode mode) noexcept;

	void setMagFilterMode(TextureFilterMode mode) noexcept;

	void setWrapMode(TextureWrapMode mode) noexcept;

	void updateMipmap();

	/// Texture size
	Point2u mSize;

	/// Texture format
	TextureFormat mFormat;

	/// Texture parameters
	TextureParameters mParameters;

	/// Texture ID
	GLuint mId;
};

// End of the namespace gltut
}
