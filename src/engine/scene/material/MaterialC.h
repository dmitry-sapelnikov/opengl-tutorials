#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/scene/material/Material.h"
#include "../../renderer/shader/ShaderArguments.h"

namespace gltut
{
/// Implementation of the Material class
class MaterialC final : public Material, public NonCopyable
{
public:
	/// Constructor
	explicit MaterialC(
		SceneShaderBinding* shader,
		u32 textureSlotsCount) noexcept;

	/// Returns the shader binding
	const SceneShaderBinding* getShader() const noexcept final;

	/// Sets the shader binding
	void setShader(const SceneShaderBinding* shader) noexcept final;

	/// Returns the shader controller
	ShaderParameters* getShaderArguments() final
	{
		return &mShaderArguments;
	}

	/// Returns the texture associated with the specified slot
	Texture* getTexture(u32 slot) const noexcept final;

	/// Sets a texture
	void setTexture(Texture* texture, u32 slot) noexcept final;

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

	/// Activates the material for a scene node
	void activate(const GeometryNode* node) const noexcept final;

private:
	/// The shader binding
	const SceneShaderBinding* mShaderBinding;

	/// The shader arguments
	ShaderArguments mShaderArguments;

	/// Texture slots
	std::array<Texture*, Texture::TEXTURE_SLOTS> mTextures;

	/// The number of texture slots
	u32 mTextureSlotsCount = 0;
};

// End of the namespace gltut
}
