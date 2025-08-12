#pragma once

// Includes
#include "engine/graphics/shader/ShaderBinding.h"

namespace gltut
{
//	Global classes
class RenderGeometry;
class Viewpoint;

/// Binds shader parameters to renderer parameters
class ShaderRendererBinding : public ShaderBinding
{
public:
	enum class Parameter
	{
		/// View matrix
		VIEWPOINT_VIEW_MATRIX = 0,

		/// Projection matrix
		VIEWPOINT_PROJECTION_MATRIX,

		/// Viewpoint position
		VIEWPOINT_POSITION,

		/// The model matrix
		GEOMETRY_MATRIX,

		/// The normal matrix
		GEOMETRY_NORMAL_MATRIX,

		/// Total number of parameters
		TOTAL_COUNT
	};

	/// Binds a scene object parameter to a shader parameter
	virtual void bind(
		Parameter parameter,
		const char* shaderParameter) noexcept = 0;

	/// Returns the name of a shader parameter bound to a scene parameter
	virtual const char* getBoundShaderParameter(Parameter parameter) const noexcept = 0;

	/// Updates the shader binding for a viewpoint
	virtual void update(const Viewpoint* viewpoint, float aspectRatio) const noexcept = 0;

	/// Updates the shader binding for a render geometry
	virtual void update(const RenderGeometry* geometry) const noexcept = 0;
};

// End of the namespace gltut
}
