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
	explicit MaterialC(SceneShaderBinding* shader) noexcept;

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

	/// Activates the material for a scene object
	void activate(const SceneObject* object) const noexcept final;

private:
	/// Binds the textures
	void bindTextures() const noexcept;

	/// The shader binding
	const SceneShaderBinding* mShaderBinding;

	/// The shader arguments
	ShaderArguments mShaderArguments;

	/// The number of texture slots
	static constexpr u32 TEXTURE_SLOTS = 16;

	/// Texture slots
	std::array<Texture*, TEXTURE_SLOTS> mTextures;
};

// End of the namespace gltut
}
