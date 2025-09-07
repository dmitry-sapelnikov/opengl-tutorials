#pragma once

// Includes
#include "engine/graphics/shader/BindingT.h"
#include "engine/graphics/shader/Shader.h"
#include "engine/renderer/shader/RendererBinding.h"

namespace gltut
{
//	Global classes
class Renderer;

/// Binds shader parameters to renderer parameters
class ShaderRendererBinding : public BindingT<Shader>, public RendererBinding
{
public:
	/// Binds a scene object parameter to a shader parameter
	virtual void bind(
		RendererBinding::Parameter parameter,
		const char* shaderParameter) noexcept = 0;

	/// Returns the name of a shader parameter bound to a scene parameter
	virtual const char* getBoundShaderParameter(
		RendererBinding::Parameter parameter) const noexcept = 0;
};

// Global functions

///	Creates a standard shader binding with common parameters
ShaderRendererBinding* createStandardShaderBinding(
	Renderer* renderer,
	const char* vertexShaderSource,
	const char* fragmentShaderSource,
	const char* modelMatrixName = "model",
	const char* viewMatrixName = "view",
	const char* projectionMatrixName = "projection",
	const char* normalMatrixName = nullptr) noexcept;

// End of the namespace gltut
}
