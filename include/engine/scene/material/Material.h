#pragma once

// Includes
#include "engine/renderer/Texture.h"
#include "engine/scene/shader/SceneShaderBinding.h"

namespace gltut
{

// Global classes
/// The class represents a material
class Material
{
public:
	///	Virtual destructor
	virtual ~Material() noexcept = default;

	/// Returns the shader
	virtual const SceneShaderBinding* getShader() const noexcept = 0;

	/// Sets the shader
	virtual void setShader(const SceneShaderBinding* shader) noexcept = 0;

	/// Returns the shader arguments object, i.e. values of shader parameters
	virtual ShaderParameters* getShaderArguments() = 0;

	/// Returns the texture associated with the specified slot
	virtual Texture* getTexture(u32 slot) const noexcept = 0;

	/// Sets a texture
	virtual void setTexture(Texture* texture, u32 slot) noexcept = 0;

	/// Activates the material for a scene geometry
	virtual void activate(const GeometryNode* node) const noexcept = 0;
};

// End of the namespace gltut
}
