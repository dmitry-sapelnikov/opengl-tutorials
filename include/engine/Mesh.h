#ifndef OPENGL_TUTORIALS_MESH_H
#define OPENGL_TUTORIALS_MESH_H

// Includes
#include "engine/core/Types.h"
#include "Shader.h"
#include "Texture.h"

namespace gltut
{

/// The class represents a triangle mesh
class Mesh
{
public:
	/// Virtual destructor
	virtual ~Mesh() noexcept = default;

	/// Renders the mesh
	virtual void render() const noexcept = 0;

	///	Returns the shader
	virtual Shader* getShader() const noexcept = 0;

	/// Sets a shader
	virtual void setShader(Shader* shader) noexcept = 0;

	/// Sets a texture
	virtual void setTexture(Texture* texture, u32 slot) noexcept = 0;
};

// End of the namespace gltut
}

#endif
