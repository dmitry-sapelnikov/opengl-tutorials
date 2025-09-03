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

/// Represents raw texture data
struct TextureData
{
	/// Pointer to the texture data
	const u8* data = nullptr;

	/// Size of the texture
	Point2u size = { 0, 0 };

	/// Format of the texture
	TextureFormat format = TextureFormat::FLOAT;
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

	/// Returns the texture parameters
	virtual const TextureParameters& getParameters() const noexcept = 0;

	/// Sets the texture parameters
	virtual void setParameters(const TextureParameters& parameters) noexcept = 0;

	/// Binds the texture
	virtual void bind(u32 slot) const noexcept = 0;
};

// End of the namespace gltut
}
