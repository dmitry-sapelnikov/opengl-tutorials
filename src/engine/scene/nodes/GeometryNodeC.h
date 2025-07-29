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
		const SceneNode* parent) noexcept :

		SceneNodeT<GeometryNode>(transform, parent),
		mMesh(mesh),
		mMaterial(material)
	{
	}

	/// Adds a mesh
	void setMesh(const Mesh* mesh) noexcept final
	{
		mMesh = mesh;
	}

	/// Sets a material
	void setMaterial(const Material* material) noexcept final
	{
		mMaterial = material;
	}

	/// Renders the object
	void render() const noexcept final
	{
		if (mMesh != nullptr)
		{
			if (mMaterial != nullptr)
			{
				mMaterial->activate(this);
			}
			mMesh->render();
		}
	}

private:
	/// The mesh
	const Mesh* mMesh = nullptr;

	/// The material
	const Material* mMaterial = nullptr;
};

// End of the namespace gltut
}
