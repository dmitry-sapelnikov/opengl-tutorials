#pragma once

// Includes
#include <vector>

#include "engine/core/NonCopyable.h"
#include "engine/graphics/GraphicsDevice.h"
#include "engine/renderer/shader/ShaderUniformBufferSet.h"

namespace gltut
{

// Global classes
class ShaderUniformBufferSetC final : public ShaderUniformBufferSet, public NonCopyable
{
public:
	/// Constructor
	ShaderUniformBufferSetC(
		GraphicsDevice& device,
		u32 bindingPointsCount);

	/// Returns the uniform buffer at the given binding point, or nullptr if none is set
	const ShaderUniformBuffer* get(u32 bindingPoint) const noexcept final;

	/// Sets a uniform buffer at the given binding point
	void set(const ShaderUniformBuffer* uniformBuffer, u32 bindingPoint) noexcept final;

	/// Returns the number of binding points
	u32 getBindingPointsCount() const noexcept final;

	/// Sets the number of binding points
	void setBindingPointsCount(u32 count) noexcept final;

	/// Binds the uniform buffers
	void bind() const noexcept final;

private:
	/// Reference to the graphics device
	GraphicsDevice& mDevice;

	/// Binding points
	std::vector<const ShaderUniformBuffer*> mBindingPoints;
};

// End of the namespace gltut
}
