#pragma once

// Includes
#include "engine/graphics/shader/ShaderBinding.h"

namespace gltut
{
//	Global classes
class Scene;

/// The class represents a shader binding for scene parameters
class SceneShaderBinding : public ShaderBinding
{
public:
	/// Enum of standard matrices
	enum class Parameter
	{
		/// Directional light position
		DIRECTIONAL_LIGHT_POSITION,
		/// Directional light direction
		DIRECTIONAL_LIGHT_DIRECTION,
		/// Directional light linear attenuation
		DIRECTIONAL_LIGHT_LINEAR_ATTENUATION,
		/// Directional light quadratic attenuation
		DIRECTIONAL_LIGHT_QUADRATIC_ATTENUATION,
		/// Directional light ambient color
		DIRECTIONAL_LIGHT_AMBIENT_COLOR,
		/// Directional light diffuse color
		DIRECTIONAL_LIGHT_DIFFUSE_COLOR,
		/// Directional light specular color
		DIRECTIONAL_LIGHT_SPECULAR_COLOR,
		/// Directional light shadow matrix
		DIRECTIONAL_LIGHT_SHADOW_MATRIX,

		/// Point light position
		POINT_LIGHT_POSITION,
		/// Point light linear attenuation
		POINT_LIGHT_LINEAR_ATTENUATION,
		/// Point light quadratic attenuation
		POINT_LIGHT_QUADRATIC_ATTENUATION,
		/// Point light ambient color
		POINT_LIGHT_AMBIENT_COLOR,
		/// Point light diffuse color
		POINT_LIGHT_DIFFUSE_COLOR,
		/// Point light specular color
		POINT_LIGHT_SPECULAR_COLOR,

		/// Spot light position
		SPOT_LIGHT_POSITION,
		/// Spot light direction
		SPOT_LIGHT_DIRECTION,
		/// Spot light inner angle cosine
		SPOT_LIGHT_INNER_ANGLE_COS,
		/// Spot light outer angle cosine
		SPOT_LIGHT_OUTER_ANGLE_COS,
		/// Spot light linear attenuation
		SPOT_LIGHT_LINEAR_ATTENUATION,
		/// Spot light quadratic attenuation
		SPOT_LIGHT_QUADRATIC_ATTENUATION,
		/// Spot light ambient color
		SPOT_LIGHT_AMBIENT_COLOR,
		/// Spot light diffuse color
		SPOT_LIGHT_DIFFUSE_COLOR,
		/// Spot light specular color
		SPOT_LIGHT_SPECULAR_COLOR,
		/// Spot light shadow matrix
		SPOT_LIGHT_SHADOW_MATRIX,

		/// Total number of scene parameters
		TOTAL_COUNT
	};

	// / The total number of parameters
	static constexpr u32 TOTAL_PARAMETERS = static_cast<u32>(Parameter::TOTAL_COUNT);

	/// Binds a scene object parameter to a shader parameter
	virtual void bind(
		Parameter parameter,
		const char* shaderParameter) noexcept = 0;

	/// Returns the name of a shader parameter bound to a scene parameter
	virtual const char* getBoundShaderParameter(Parameter parameter) const noexcept = 0;

	/// Updates the shader binding for a scene
	virtual void update(const Scene* scene) const noexcept = 0;
};

// End of the namespace gltut
}
