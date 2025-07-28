#pragma once

// Includes
#include "engine/scene/nodes/GeometryNode.h"
#include "../../renderer/RendererBase.h"
#include "./SceneNodeT.h"


namespace gltut
{
// Global classes
/// Implementation of the Scene interface
class GeometryNodeC final : public SceneNodeT<GeometryNode>
{
public:
	GeometryNodeC(
		Mesh* mesh,
		Material* material,
		const Matrix4& transform,
		SceneNode* parent) noexcept;

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
	/// The mesh
	Mesh* mMesh = nullptr;

	/// The material
	Material* mMaterial = nullptr;
};

// End of the namespace gltut
}
