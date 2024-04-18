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
};

// End of the namespace gltut
}

#endif
