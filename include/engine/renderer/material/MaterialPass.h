#pragma once

// Includes
#include "engine/graphics/Texture.h"
#include "engine/graphics/shader/ShaderParameters.h"
#include "engine/renderer/material/ShaderMaterialBinding.h"
#include "engine/renderer/texture/TextureSet.h"

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
	virtual ShaderParameters* getShaderArguments() noexcept = 0;

	/// Returns the textures associated with this material pass
	virtual TextureSet* getTextures() noexcept = 0;

	/// Binds the material pass for a render geometry
	virtual void bind(const RenderGeometry* geometry) const noexcept = 0;
};

// End of the namespace gltut
}
