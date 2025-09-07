#pragma once

// Includes
#include "engine/graphics/shader/BindingT.h"
#include "engine/scene/shader/SceneBinding.h"

namespace gltut
{
//	Global classes
/// The class represents a shader binding for scene parameters
class SceneShaderBinding : public BindingT<Shader>, public SceneBinding
{
public:
	// / The total number of parameters
	static constexpr u32 TOTAL_PARAMETERS = static_cast<u32>(SceneBinding::Parameter::TOTAL_COUNT);

	/// Binds a scene object parameter to a shader parameter
	virtual void bind(
		SceneBinding::Parameter parameter,
		const char* shaderParameter) noexcept = 0;

	/// Returns the name of a shader parameter bound to a scene parameter
	virtual const char* getBoundShaderParameter(SceneBinding::Parameter parameter) const noexcept = 0;
};

// End of the namespace gltut
}
