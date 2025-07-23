#ifndef OPENGL_TUTORIALS_MATERIAL_C_H
#define OPENGL_TUTORIALS_MATERIAL_C_H

// Includes
#include <array>
#include "engine/core/NonCopyable.h"
#include "engine/Material.h"

namespace gltut
{
/// Implementation of the Material class
class MaterialC final : public Material, public NonCopyable
{
public:
	/// Constructor
	MaterialC(Shader* shader) noexcept;

	///	Returns the assigned shader
	Shader* getShader() const noexcept final;

	/// Sets a shader
	void setShader(Shader* shader) noexcept final;

	/// Returns the texture associated with the specified slot
	Texture* getTexture(u32 slot) const noexcept final;

	/// Sets a texture
	void setTexture(Texture* texture, u32 slot) noexcept final;

	/// Use the material
	void activate() noexcept final;

private:
	/// The number of texture slots
	static constexpr u32 TEXTURE_SLOTS = 16;

	/// The shader
	Shader* mShader = nullptr;

	/// Texture slots
	std::array<Texture*, TEXTURE_SLOTS> mTextures;
};

// End of the namespace gltut
}

#endif
