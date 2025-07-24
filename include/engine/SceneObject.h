#ifndef OPENGL_TUTORIALS_SCENE_OBJECT_H
#define OPENGL_TUTORIALS_SCENE_OBJECT_H

// Includes
#include "Mesh.h"
#include "./material/Material.h"
#include "./engine/math/Matrix4.h"

namespace gltut
{
// Global classes
/// The class represents a scene object
class SceneObject
{
public:
	/// Virtual destructor
	virtual ~SceneObject() noexcept = default;

	/// Returns the transform
	virtual const Matrix4& getTransform() const noexcept = 0;

	/// Sets the transform
	virtual void setTransform(const Matrix4& transform) noexcept = 0;

	/// Returns the mesh
	virtual Mesh* getMesh() const noexcept = 0;

	/// Adds a mesh
	virtual void setMesh(Mesh* mesh) noexcept = 0;

	/// Returns the material
	virtual Material* getMaterial() const noexcept = 0;

	/// Sets a material
	virtual void setMaterial(Material* material) noexcept = 0;

	/// Renders the object
	virtual void render() const noexcept = 0;
};

// End of the namespace gltut
}

#endif
