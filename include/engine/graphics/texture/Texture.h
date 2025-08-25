#pragma once

// Includes
#include "engine/math/Point2.h"
#include "engine/graphics/texture/TextureParameters.h"

namespace gltut
{

/// Represents the format of a texture
enum class TextureFormat
{
	/// Single channel (red)
	R,
	RGB,
	RGBA,
	FLOAT,
	TOTAL_COUNT
};

///	Represents a texture
class Texture
{
public:
	/// The number of texture slots available
	static constexpr u32 TEXTURE_SLOTS = 16;

	/// Virtual destructor
	virtual ~Texture() noexcept = default;

	/// Returns the texture id
	virtual u32 getId() const noexcept = 0;
	
	/// Returns the size of the texture
	virtual const Point2u& getSize() const noexcept = 0;

	/// Returns the texture format
	virtual TextureFormat getFormat() const noexcept = 0;

	/// Returns the texture parameters
	virtual const TextureParameters& getParameters() const noexcept = 0;

	/// Sets the texture parameters
	virtual void setParameters(const TextureParameters& parameters) noexcept = 0;

	/// Binds the texture
	virtual void bind(u32 slot) const noexcept = 0;

	/// Returns the aspect ratio of the texture
	float getAspectRatio() const noexcept
	{
		const auto& size = getSize();
		return size.y != 0 ?
			static_cast<float>(size.x) / static_cast<float>(size.y) :
			1.0f;
	}
};

// End of the namespace gltut
}
