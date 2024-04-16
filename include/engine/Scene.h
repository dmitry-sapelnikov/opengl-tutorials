#ifndef OPENGL_TUTORIALS_ISCENE_H
#define OPENGL_TUTORIALS_ISCENE_H

// Includes
#include "Mesh.h"

namespace gltut
{
// Global classes
/// The class represents a scene
class Scene
{
public:
	/// Virtual destructor
	virtual ~Scene() noexcept = default;

	/**
		\brief Creates a mesh
		\return The mesh if it was created successfully, nullptr otherwise
	*/
	virtual Mesh* createMesh(
		float* vertices,
		u32 vertexCount,
		u32* indices,
		u32 indexCount) noexcept = 0;

	/// Renders the scene
	virtual void render() noexcept = 0;
};

// End of the namespace gltut
}

#endif
