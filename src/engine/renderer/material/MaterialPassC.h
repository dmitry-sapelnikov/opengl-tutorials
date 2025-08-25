#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/renderer/material/MaterialPass.h"
#include "../../graphics/shader/ShaderArguments.h"
#include "../texture/TextureSetC.h"

namespace gltut
{
/// Implementation of the Material class
class MaterialPassC final : public MaterialPass, public NonCopyable
{
public:
	/// Constructor
	explicit MaterialPassC(
		GraphicsDevice& device,
		const ShaderRendererBinding* shader,
		u32 textureSlotsCount) noexcept;

	/// Returns the shader binding
	const ShaderRendererBinding* getShader() const noexcept final;

	/// Sets the shader binding
	void setShader(const ShaderRendererBinding* shader) noexcept final;

	/// Returns the shader controller
	ShaderParameters* getShaderArguments() noexcept final
	{
		return &mShaderArguments;
	}

	/// Returns the texture associated with the specified slot
	TextureSet* getTextures() noexcept final
	{
		return &mTextures;
	}

	/// Binds the material pass for a render geometry
	void bind(const RenderGeometry* geometry) const noexcept final;

private:
	/// The shader binding
	const ShaderRendererBinding* mShaderBinding;

	/// The shader arguments
	ShaderArguments mShaderArguments;

	/// The textures
	TextureSetC mTextures;
};

// End of the namespace gltut
}
