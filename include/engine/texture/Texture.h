#ifndef OPENGL_TUTORIALS_TEXTURE_H
#define OPENGL_TUTORIALS_TEXTURE_H

// Includes
#include "engine/core/Types.h"

namespace gltut
{
///	Represents a texture
class Texture
{
public:
	enum class WrapMode
	{
		REPEAT,
		CLAMP_TO_EDGE
	};

	/// Virtual destructor
	virtual ~Texture() noexcept = default;

	/// Returns the wrap mode of the texture
	virtual WrapMode getWrapMode() const noexcept = 0;

	/// Sets the wrap mode of the texture
	virtual void setWrapMode(WrapMode mode) noexcept = 0;

	/// Binds the texture
	virtual void bind(u32 slot) const noexcept = 0;
};

// End of the namespace gltut
}

#endif
