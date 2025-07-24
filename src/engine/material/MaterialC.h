#ifndef OPENGL_TUTORIALS_MATERIAL_C_H
#define OPENGL_TUTORIALS_MATERIAL_C_H

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/material/Material.h"

#include "../shader/ShaderArguments.h"

namespace gltut
{
/// Implementation of the Material class
class MaterialC final : public Material, public NonCopyable
{
public:
	/// Constructor
	explicit MaterialC(Shader* shader) noexcept;

	/// Return the shader
	virtual Shader* getShader() const noexcept final;

	/// Sets the shader
	void setShader(Shader* shader) noexcept final;

	/// Returns the shader controller
	ShaderParameters* getShaderArguments() final
	{
		return &mShaderArguments;
	}

	/// Returns the texture associated with the specified slot
	Texture* getTexture(u32 slot) const noexcept final;

	/// Sets a texture
	void setTexture(Texture* texture, u32 slot) noexcept final;

	/// Use the material
	void activate() const noexcept final;

private:
	/// Binds the textures
	void bindTextures() const noexcept;

	/// The shader arguments
	ShaderArguments mShaderArguments;

	/// The number of texture slots
	static constexpr u32 TEXTURE_SLOTS = 16;

	/// Texture slots
	std::array<Texture*, TEXTURE_SLOTS> mTextures;
};

// End of the namespace gltut
}

#endif
