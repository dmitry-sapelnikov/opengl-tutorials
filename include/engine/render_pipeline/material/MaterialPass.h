#pragma once

// Includes
#include "engine/graphics/Texture.h"
#include "engine/graphics/shader/ShaderParameters.h"
#include "engine/render_pipeline/material/ShaderMaterialBinding.h"

namespace gltut
{

// Global classes
/// The class represents a material for a single render pass
class MaterialPass
{
public:
	///	Virtual destructor
	virtual ~MaterialPass() noexcept = default;

	/// Returns the shader
	virtual const ShaderMaterialBinding* getShader() const noexcept = 0;

	/// Sets the shader
	virtual void setShader(const ShaderMaterialBinding* shader) noexcept = 0;

	/// Returns the shader arguments object, i.e. values of shader parameters
	virtual ShaderParameters* getShaderArguments() = 0;

	/// Returns the texture associated with the specified slot
	virtual const Texture* getTexture(u32 slot) const noexcept = 0;

	/// Sets a texture to a slot If the slot >= current texture count, does nothing.
	virtual void setTexture(const Texture* texture, u32 slot) noexcept = 0;

	/// Returns the number of textures
	virtual u32 getTextureSlotsCount() const noexcept = 0;

	/// Sets the number of used texture slots
	/// The number is truncated to Texture::TEXTURE_SLOTS
	virtual void setTextureSlotsCount(u32 count) noexcept = 0;

	/// Binds the material pass for a render geometry
	virtual void bind(const RenderGeometry* geometry) const noexcept = 0;
};

// End of the namespace gltut
}
