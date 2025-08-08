#pragma once

// Includes
#include "engine/core/Types.h"
#include "engine/math/Point2.h"

namespace gltut
{
///	Represents a texture
class Texture
{
public:
	enum class Format
	{
		RGB,
		RGBA,
		FLOAT,
		TOTAL_COUNT
	};

	enum class WrapMode
	{
		REPEAT,
		CLAMP_TO_EDGE
	};

	enum class FilterMode
	{
		NEAREST,
		LINEAR,
		NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP
	};

	/// The number of texture slots available
	static constexpr u32 TEXTURE_SLOTS = 16;

	/// Virtual destructor
	virtual ~Texture() noexcept = default;

	/// Returns the texture id
	virtual u32 getId() const noexcept = 0;
	
	/// Returns the size of the texture
	virtual const Point2u& getSize() const noexcept = 0;

	/// Returns the texture format
	virtual Format getFormat() const noexcept = 0;

	/// Returns the filter mode of the texture
	virtual FilterMode getMinFilterMode() const noexcept = 0;

	/// Sets the filter mode of the texture
	virtual void setMinFilterMode(FilterMode mode) noexcept = 0;

	/// Returns the mag filter mode of the texture
	virtual FilterMode getMagFilterMode() const noexcept = 0;

	/// Sets the mag filter mode of the texture
	virtual void setMagFilterMode(FilterMode mode) noexcept = 0;

	/// Returns the wrap mode of the texture
	virtual WrapMode getWrapMode() const noexcept = 0;

	/// Sets the wrap mode of the texture
	virtual void setWrapMode(WrapMode mode) noexcept = 0;

	/// Binds the texture
	virtual void bind(u32 slot) const noexcept = 0;
};

// End of the namespace gltut
}
