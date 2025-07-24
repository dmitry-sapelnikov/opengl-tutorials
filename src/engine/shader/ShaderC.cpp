// Includes
#include "ShaderC.h"
#include "engine/core/Check.h"

namespace gltut
{
// Global classes
const char* ShaderC::getSceneParameterName(SceneParameter parameter) const noexcept
{
	const auto& result = mSceneParameterNames[static_cast<size_t>(parameter)];
	return result.empty() ? nullptr : result.c_str();
}

void ShaderC::setSceneParameterName(SceneParameter parameter, const char* name) noexcept
{
	mSceneParameterNames[static_cast<size_t>(parameter)] = (name != nullptr) ? name : "";
}

// End of the namespace gltut
}
