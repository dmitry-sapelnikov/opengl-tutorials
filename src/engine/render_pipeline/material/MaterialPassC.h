#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/render_pipeline/material/MaterialPass.h"
#include "../../renderer/shader/ShaderArguments.h"

namespace gltut
{
/// Implementation of the Material class
class MaterialPassC final : public MaterialPass, public NonCopyable
{
public:
	/// Constructor
	explicit MaterialPassC(
		ShaderMaterialBinding* shader,
		u32 textureSlotsCount) noexcept;

	/// Returns the shader binding
	const ShaderMaterialBinding* getShader() const noexcept final;

	/// Sets the shader binding
	void setShader(const ShaderMaterialBinding* shader) noexcept final;

	/// Returns the shader controller
	ShaderParameters* getShaderArguments() final
	{
		return &mShaderArguments;
	}

	/// Returns the texture associated with the specified slot
	const Texture* getTexture(u32 slot) const noexcept final;

	/// Sets a texture
	void setTexture(const Texture* texture, u32 slot) noexcept final;

	/// Returns the number of textures
	u32 getTextureSlotsCount() const noexcept final
	{
		return mTextureSlotsCount;
	}

	/// Sets the number of used texture slots
	/// The number is truncated to Texture::TEXTURE_SLOTS
	void setTextureSlotsCount(u32 count) noexcept final
	{
		mTextureSlotsCount = std::min(count, Texture::TEXTURE_SLOTS);
	}

	/// Binds the material pass for a render geometry
	void bind(const RenderGeometry* geometry) const noexcept final;

private:
	/// The shader binding
	const ShaderMaterialBinding* mShaderBinding;

	/// The shader arguments
	ShaderArguments mShaderArguments;

	/// Texture slots
	std::array<const Texture*, Texture::TEXTURE_SLOTS> mTextures;

	/// The number of texture slots
	u32 mTextureSlotsCount = 0;
};

// End of the namespace gltut
}
