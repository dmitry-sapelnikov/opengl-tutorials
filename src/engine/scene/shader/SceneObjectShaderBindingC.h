#pragma once

// Includes
#include <array>
#include <string>
#include "engine/core/NonCopyable.h"
#include "engine/scene/shader/SceneObjectShaderBinding.h"

namespace gltut
{

class SceneObjectShaderBindingC : public SceneObjectShaderBinding, public NonCopyable
{
public:
	/// Binds a scene object parameter to a shader parameter
	void bind(
		SceneObjectParameter sceneObjectParameter,
		const char* shaderParameter) noexcept final;

	/// Returns the name of a shader parameter bound to a scene object parameter
	const char* getBoundShaderParameter(
		SceneObjectParameter sceneObjectParameter) const noexcept final;

private:
	/// Names of scene parameters
	std::array<std::string, static_cast<size_t>(SceneObjectParameter::TOTAL_COUNT)> mShaderParameterNames;
};

// End of the namespace gltut
}
