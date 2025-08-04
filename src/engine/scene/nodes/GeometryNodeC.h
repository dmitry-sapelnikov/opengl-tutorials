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
		const Mesh* mesh,
		const Material* material,
		const Matrix4& transform,
		SceneNode* parent) noexcept :

		SceneNodeT<GeometryNode>(transform, parent),
		mMesh(mesh),
		mMaterial(material)
	{
	}

	/// Returns the mesh of this geometry node
	const Mesh* getMesh() const noexcept final
	{
		return mMesh;
	}

	/// Sets a mesh
	void setMesh(const Mesh* mesh) noexcept final
	{
		mMesh = mesh;
	}

	/// Returns the material for a specific render pass
	const Material* getMaterial() const noexcept final
	{
		return mMaterial;
	}

	/// Sets a material
	void setMaterial(const Material* material) noexcept final
	{
		mMaterial = material;
	}

private:
	/// The mesh
	const Mesh* mMesh = nullptr;

	/// Material passes
	const Material* mMaterial;
};

// End of the namespace gltut
}
