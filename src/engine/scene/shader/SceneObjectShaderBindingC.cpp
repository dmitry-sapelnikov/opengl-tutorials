// Includes
#include "SceneObjectShaderBindingC.h"

namespace gltut
{
// Global classes
const char* SceneObjectShaderBindingC::getBoundShaderParameter(
	SceneObjectParameter parameter) const noexcept
{
	const auto& result = mShaderParameterNames[static_cast<size_t>(parameter)];
	return result.empty() ? nullptr : result.c_str();
}

void SceneObjectShaderBindingC::bind(
	SceneObjectParameter sceneObjectParameter,
	const char* shaderParameter) noexcept
{
	mShaderParameterNames[static_cast<size_t>(sceneObjectParameter)] =
		(shaderParameter != nullptr) ? shaderParameter : "";
}

// End of the namespace gltut
}
