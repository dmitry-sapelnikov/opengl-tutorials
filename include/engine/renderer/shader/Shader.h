#pragma once

// Includes
#include "engine/core/Check.h"
#include "ShaderParameters.h"

namespace gltut
{
//	Global classes
class Renderer;

///	Represents a shader
class Shader: public ShaderParameters
{
public:
	/// Virtual destructor
	virtual ~Shader() noexcept = default;

	/// Returns the renderer associated with this shader
	virtual Renderer* getRenderer() const noexcept = 0;

	/// Binds the shader
	virtual void bind() const noexcept = 0;
};

// End of the namespace gltut
}
