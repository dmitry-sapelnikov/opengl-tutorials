#pragma once

// Includes
#include "ShaderParameters.h"
#include "engine/core/Check.h"

namespace gltut
{
/// Represents a shader (shader program in OpenGL terminology)
class Shader : public ShaderParameters
{
public:
	/// Virtual destructor
	virtual ~Shader() noexcept = default;

	/// Binds the shader
	virtual void bind() const noexcept = 0;
};

// End of the namespace gltut
}
