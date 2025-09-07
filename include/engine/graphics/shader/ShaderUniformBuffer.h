#pragma once

// Includes
#include "engine/core/Types.h"

namespace gltut
{
///	Represents a shader uniform buffer
class ShaderUniformBuffer
{
public:
	/// Virtual destructor
	virtual ~ShaderUniformBuffer() noexcept = default;

	/// Return the id of the uniform buffer
	virtual u32 getId() const noexcept = 0;

	/// Sets the data of the uniform buffer
	virtual void setData(const void* data, u32 size, u32 offset) noexcept = 0;

};

// End of the namespace gltut
}
