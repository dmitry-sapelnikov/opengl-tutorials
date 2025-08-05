#pragma once

// Includes
#include "engine/renderer/shader/ShaderBinding.h"

namespace gltut
{
//	Global classes
class RenderGeometry;

/// Binds geometry material parameters to shader
class ShaderMaterialBinding : public ShaderBinding
{
public:
	enum class Parameter
	{
		/// The model matrix
		GEOMETRY_MATRIX = 0,
		/// The normal matrix
		GEOMETRY_NORMAL_MATRIX,
		/// Total number of body parameters
		TOTAL_COUNT
	};

	/// Binds a scene object parameter to a shader parameter
	virtual void bind(
		Parameter parameter,
		const char* shaderParameter) noexcept = 0;

	/// Returns the name of a shader parameter bound to a scene parameter
	virtual const char* getBoundShaderParameter(Parameter parameter) const noexcept = 0;

	/// Updates the shader binding for a render geometry
	virtual void update(const RenderGeometry* geometry) const noexcept = 0;
};

// End of the namespace gltut
}
