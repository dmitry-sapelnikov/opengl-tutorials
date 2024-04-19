#ifndef OPENGL_TUTORIALS_SCENE_OJBECT_C_H
#define OPENGL_TUTORIALS_SCENE_OJBECT_C_H

// Includes
#include "engine/SceneObject.h"
#include "RendererBase.h"
#include "engine/core/NonCopyable.h"

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

	/// Returns the name of the shader transform input
	virtual const char* getShaderTransformInputName() const noexcept final;

	/// Sets the name of the shader transform input
	virtual void setShaderTransformInputName(const char* name) noexcept final;

	/// Renders the object
	void render() const noexcept final;

private:
	/// The renderer
	RendererBase& mRenderer;

	/// The mesh
	Mesh* mMesh = nullptr;

	/// The material
	Material* mMaterial = nullptr;

	/// The shader transform input name
	std::string mShaderTransformInputName = "transform";

	/// The transform
	Matrix4 mTransform = Matrix4::identity();
};

// End of the namespace gltut
}

#endif
