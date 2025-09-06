#pragma once

// Includes
#include "engine/graphics/texture/Texture.h"
#include "engine/graphics/shader/ShaderParameters.h"
#include "engine/renderer/shader/ShaderRendererBinding.h"
#include "engine/renderer/texture/TextureSet.h"
#include "engine/graphics/FaceCullingMode.h"

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
	virtual const ShaderRendererBinding* getShader() const noexcept = 0;

	/// Sets the shader
	virtual void setShader(const ShaderRendererBinding* shader) noexcept = 0;

	/// Returns the shader arguments object, i.e. values of shader parameters
	virtual ShaderParameters* getShaderArguments() noexcept = 0;

	/// Returns the textures associated with this material pass
	virtual TextureSet* getTextures() noexcept = 0;

	/// Returns the material cull mode
	virtual FaceCullingMode getFaceCullingMode() const noexcept = 0;

	/// Sets the material cull mode
	virtual void setFaceCullingMode(FaceCullingMode mode) noexcept = 0;

	/// Returns the transparency flag
	virtual bool isTransparent() const noexcept = 0;

	/// Sets the transparency flag
	virtual void setTransparent(bool transparent) noexcept = 0;

	/// Binds the material pass for a render geometry
	virtual void bind(const RenderGeometry* geometry) const noexcept = 0;
};

// End of the namespace gltut
}
