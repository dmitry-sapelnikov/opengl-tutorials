#pragma once

// Includes
#include <string>
#include <glad/glad.h>
#include "engine/core/NonCopyable.h"
#include "engine/core/Types.h"
#include "engine/renderer/Texture.h"

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
		u32 width,
		u32 height,
		Texture::Format format,
		Texture::FilterMode minFilter,
		Texture::FilterMode magFilter,
		Texture::WrapMode wrapMode);

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

	/// Returns the wrap mode of the texture
	WrapMode getWrapMode() const noexcept final
	{
		return mWrapMode;
	}

	/// Sets the wrap mode of the texture
	void setWrapMode(WrapMode mode) noexcept final;

	/// Returns the texture format
	Format getFormat() const noexcept final
	{
		return mFormat;
	}

	/// Returns the min filter mode of the texture
	FilterMode getMinFilterMode() const noexcept final
	{
		return mMinFilter;
	}

	/// Sets the min filter mode of the texture
	void setMinFilterMode(FilterMode mode) noexcept final;

	/// Returns the mag filter mode of the texture
	FilterMode getMagFilterMode() const noexcept final
	{
		return mMagFilter;
	}

	/// Sets the mag filter mode of the texture
	void setMagFilterMode(FilterMode mode) noexcept final;

	/// Binds the texture
	void bind(u32 slot) const noexcept final;

private:
	/// Texture size
	Point2u mSize;

	/// Texture format
	Format mFormat;

	/// Min filter mode
	FilterMode mMinFilter;

	/// Mag filter mode
	FilterMode mMagFilter;

	/// Wrap mode
	WrapMode mWrapMode;

	/// Texture ID
	GLuint mId;
};

// End of the namespace gltut
}
