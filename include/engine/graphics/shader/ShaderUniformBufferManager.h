#pragma once

// Includes
#include "engine/core/ItemManager.h"
#include "engine/graphics/shader/ShaderUniformBuffer.h"

namespace gltut
{

// Global classes
/// Interface for shader uniform buffer management
class ShaderUniformBufferManager : public ItemManager<ShaderUniformBuffer>
{
public:
	/// Creates a shader uniform buffer of the given size in bytes
	virtual ShaderUniformBuffer* create(u32 sizeInBytes) noexcept = 0;
};

// End of the namespace gltut
}
