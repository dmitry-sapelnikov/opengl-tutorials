#ifndef OPENGL_TUTORIALS_MATERIAL_H
#define OPENGL_TUTORIALS_MATERIAL_H

// Includes
#include "engine/renderer/shader/Shader.h"
#include "engine/renderer/Texture.h"

namespace gltut
{

/// The class represents a material
class Material
{
public:
	///	Virtual destructor
	virtual ~Material() noexcept = default;

	/// Returns the shader
	virtual Shader* getShader() const noexcept = 0;

	/// Sets the shader
	virtual void setShader(Shader* shader) noexcept = 0;

	/// Returns the shader arguments object, i.e. values of shader parameters
	virtual ShaderParameters* getShaderArguments() = 0;

	/// Returns the texture associated with the specified slot
	virtual Texture* getTexture(u32 slot) const noexcept = 0;

	/// Sets a texture
	virtual void setTexture(Texture* texture, u32 slot) noexcept = 0;

	/// Activates the material
	virtual void activate() const noexcept = 0;
};

// End of the namespace gltut
}

#endif
