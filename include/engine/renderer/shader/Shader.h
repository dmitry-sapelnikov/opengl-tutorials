#pragma once

// Includes
#include "engine/core/Check.h"
#include "ShaderParameters.h"

namespace gltut
{
///	Represents a shader
class Shader: public ShaderParameters
{
public:
	/// Virtual destructor
	virtual ~Shader() noexcept = default;

	/// Binds the shader
	virtual void bind() const noexcept = 0;
};

// End of the namespace gltut
}
