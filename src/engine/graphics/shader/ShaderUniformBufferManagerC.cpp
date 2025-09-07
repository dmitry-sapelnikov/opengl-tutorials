// Includes
#include "ShaderUniformBufferManagerC.h"
#include "../../core/File.h"
#include "../GraphicsDeviceBase.h"

namespace gltut
{

// Global classes
ShaderUniformBuffer* ShaderUniformBufferManagerC::create(u32 size) noexcept
{
	if (!GLTUT_ASSERT(size > 0))
	{
		return nullptr;
	}

	ShaderUniformBuffer* result = nullptr;
	try
	{
		result = add(mDevice.createBackendShaderUniformBuffer(size));
	}
	GLTUT_CATCH_ALL("Failed to create shader uniform buffer")
	return result;
}

// End of the namespace gltut
}
