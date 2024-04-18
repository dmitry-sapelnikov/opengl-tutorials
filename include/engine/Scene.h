#ifndef OPENGL_TUTORIALS_ISCENE_H
#define OPENGL_TUTORIALS_ISCENE_H

// Includes
#include "SceneObject.h"
#include "VertexFormat.h"

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
		\brief Creates a material
		\param shader The shader
		\return The material if it was created successfully, nullptr otherwise
	*/
	virtual Material* createMaterial(Shader* shader) noexcept = 0;

	/**
		\brief Creates a mesh
		\return The mesh if it was created successfully, nullptr otherwise
	*/
	virtual Mesh* createMesh(
		VertexFormat vertexFormat,
		float* vertices,
		u32 vertexCount,
		u32* indices,
		u32 indexCount) noexcept = 0;

	/// Creates a scene object
	virtual SceneObject* createObject(
		Mesh* mesh,
		Material* material,
		const Matrix4& transform = Matrix4::identity()) noexcept = 0;

	/// Renders the scene
	virtual void render() noexcept = 0;
};

// End of the namespace gltut
}

#endif
