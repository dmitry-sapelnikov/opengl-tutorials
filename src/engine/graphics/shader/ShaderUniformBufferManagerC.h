#pragma once

// Includes
#include "engine/graphics/Shader/ShaderUniformBufferManager.h"
#include "../../core/ItemManagerT.h"

namespace gltut
{

/// GraphicsDevice base class
class GraphicsDeviceBase;

/// Implementation of the ShaderUniformBufferManager interface
class ShaderUniformBufferManagerC : public ItemManagerT<ShaderUniformBufferManager>
{
public:
	/// Constructor
	ShaderUniformBufferManagerC(GraphicsDeviceBase& device) noexcept :
		mDevice(device)
	{
	}

	/// Creates a shader from strings
	ShaderUniformBuffer* create(u32 size) noexcept final;

private:
	/// Reference to the graphics device
	GraphicsDeviceBase& mDevice;
};

// End of the namespace gltut
}
