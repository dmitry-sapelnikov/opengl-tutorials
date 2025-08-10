#pragma once

// Includes
#include "engine/graphics/shader/ShaderBinding.h"
#include "engine/renderer/viewpoint/Viewpoint.h"

namespace gltut
{
//	Global classes
/// Binds geometry material parameters to shader
class ShaderViewpointBinding : public ShaderBinding
{
public:
	enum class Parameter
	{
		/// View matrix
		VIEW_MATRIX = 0,

		/// Projection matrix
		PROJECTION_MATRIX,

		/// Viewpoint position
		POSITION,

		/// Total number of viewpoint parameters
		TOTAL_COUNT
	};

	/// Binds a geometry material parameter to a shader parameter
	virtual void bind(
		Parameter parameter,
		const char* shaderParameter) noexcept = 0;

	/// Returns the name of a shader parameter bound to a geometry material parameter
	virtual const char* getBoundShaderParameter(Parameter parameter) const noexcept = 0;

	/// Updates the shader binding for a viewpoint
	virtual void update(const Viewpoint* viewpoint, float aspectRatio) const noexcept = 0;
};

// End of the namespace gltut
}
