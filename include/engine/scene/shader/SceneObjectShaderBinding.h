#pragma once

// Includes
#include "engine/renderer/shader/Shader.h"

namespace gltut
{
//	Global classes

/// Binds shader parameters to scene parameters
class SceneObjectShaderBinding
{
public:
	enum class SceneObjectParameter
	{
		/// The model matrix
		MODEL = 0,
		/// The normal matrix
		NORMAL,
		/// Total number of body parameters
		TOTAL_COUNT
	};

	/// Binds a scene object parameter to a shader parameter
	virtual void bind(
		SceneObjectParameter sceneObjectParameter,
		const char* shaderParameter) noexcept = 0;

	/// Returns the name of a shader parameter bound to a scene object parameter
	virtual const char* getBoundShaderParameter(
		SceneObjectParameter sceneObjectParameter) const noexcept = 0;
};

// End of the namespace gltut
}
