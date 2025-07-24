#ifndef OPENGL_TUTORIALS_SCENE_OJBECT_C_H
#define OPENGL_TUTORIALS_SCENE_OJBECT_C_H

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/scene/SceneObject.h"
#include "../renderer/RendererBase.h"

namespace gltut
{
// Global classes
/// Implementation of the Scene interface
class SceneObjectC final : public SceneObject, public NonCopyable
{
public:
	SceneObjectC(
		RendererBase& renderer,
		Mesh* mesh,
		Material* material,
		const Matrix4& transform) noexcept;

	/// Returns the transform
	const Matrix4& getTransform() const noexcept final;

	/// Sets the transform
	void setTransform(const Matrix4& transform) noexcept final;

	/// Returns the mesh
	Mesh* getMesh() const noexcept final;

	/// Adds a mesh
	void setMesh(Mesh* mesh) noexcept final;

	/// Returns the material
	Material* getMaterial() const noexcept final;

	/// Sets a material
	void setMaterial(Material* material) noexcept final;

	/// Renders the object
	void render() const noexcept final;

private:
	/// The renderer
	RendererBase& mRenderer;

	/// The mesh
	Mesh* mMesh = nullptr;

	/// The material
	Material* mMaterial = nullptr;

	/// The transform
	Matrix4 mTransform = Matrix4::identity();
};

// End of the namespace gltut
}

#endif
