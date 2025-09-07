#pragma once

// Includes
#include <vector>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/material/Material.h"
#include "engine/graphics/GraphicsDevice.h"

namespace gltut
{
/// Implementation of the Material class
class MaterialC final : public Material, public NonCopyable
{
public:
	/// Constructor
	MaterialC(GraphicsDevice& device) noexcept :
		mDevice(device)
	{
	}

	/// Creates a material pass by index
	MaterialPass* createPass(
		u32 index,
		const ShaderRendererBinding* shader,
		u32 textureSlotsCount,
		u32 shaderBindingPointsCount) noexcept final;

	/// Removes a material pass by index
	void removePass(u32 index) noexcept final;

	/// Returns a material pass by index. Returns nullptr if the pass does not exist.
	MaterialPass* getPass(u32 index) const noexcept final;

private:
	/// Graphics device reference
	GraphicsDevice& mDevice;

	/// List of material passes
	std::vector<std::unique_ptr<MaterialPass>> mPasses;
};

// End of the namespace gltut
}
