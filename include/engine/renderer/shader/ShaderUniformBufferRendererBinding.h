#pragma once

// Includes
#include "engine/graphics/shader/BindingT.h"
#include "engine/graphics/shader/ShaderUniformBuffer.h"
#include "engine/renderer/shader/RendererBinding.h"

namespace gltut
{
//	Global classes
class Renderer;

/// Binds shader parameters to renderer parameters
class ShaderUniformBufferRendererBinding : public BindingT<ShaderUniformBuffer>, public RendererBinding
{
public:
	/// Binds a scene object parameter to a shader parameter
	virtual void bind(
		RendererBinding::Parameter parameter,
		u32 bufferOffsetInBytes) noexcept = 0;

	/// Returns the offset in bytes of the given parameter in the bound shader uniform buffer,
	/// or nullptr if the parameter is not bound
	virtual const u32* getParameterOffset(
		RendererBinding::Parameter parameter) const noexcept = 0;
};

// End of the namespace gltut
}
