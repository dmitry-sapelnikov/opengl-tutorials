#pragma once

// Includes
#include "engine/graphics/shader/Shader.h"

namespace gltut
{
//	Global classes
/// The class represents a binding of shader parameters
class ShaderBinding
{
public:
	/// Virtual destructor
	virtual ~ShaderBinding() noexcept = default;

	/// Returns the shader associated with this binding
	virtual Shader* getShader() const noexcept = 0;

	/**
		\brief Sets the shader associated with this binding
		\param shader The shader to set
		\param resetParameters If true, clears all bound shader parameters
	*/
	virtual void setShader(
		Shader* shader,
		bool resetParameters = false) noexcept = 0;
};

// End of the namespace gltut
}
