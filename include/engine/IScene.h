#ifndef OPENGL_TUTORIALS_ISCENE_H
#define OPENGL_TUTORIALS_ISCENE_H

// Includes
#include "IMesh.h"

namespace gltut
{

/// The class represents a scene
class IScene
{
public:
	/// Virtual destructor
	virtual ~IScene() noexcept = default;

	/**
		\brief Creates a mesh
		\return The mesh if it was created successfully, nullptr otherwise
		\note The caller is NOT responsible for deleting the mesh
	*/
	virtual IMesh* createMesh(
		float* vertices,
		u32 vertexCount,
		u32* indices,
		u32 indexCount) noexcept = 0;

	/// Renders the scene
	virtual void render() noexcept = 0;
};

/**
	Creates a scene
	\return The scene if it was created successfully, nullptr otherwise
	\note The caller is responsible for deleting the scene
*/
IScene* createScene() noexcept;

// End of the namespace gltut
}

#endif
