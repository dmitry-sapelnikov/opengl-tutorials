#pragma once

// Includes
#include "engine/core/Check.h"
#include "ShaderParameters.h"

namespace gltut
{
//	Global classes
///	Represents a shader
class Shader: public ShaderParameters
{
public:
	/// Virtual destructor
	virtual ~Shader() noexcept = default;

	/// Activates the shader
	virtual void activate() const noexcept = 0;
};

// End of the namespace gltut
}
