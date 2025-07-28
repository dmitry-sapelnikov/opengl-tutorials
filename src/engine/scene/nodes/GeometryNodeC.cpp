// Includes
#include "GeometryNodeC.h"

namespace gltut
{
// Global classes
GeometryNodeC::GeometryNodeC(
	Mesh* mesh,
	Material* material,
	const Matrix4& transform,
	SceneNode* parent) noexcept :
	
	SceneNodeT<GeometryNode>(transform, parent),
	mMesh(mesh),
	mMaterial(material)
{
}

Mesh* GeometryNodeC::getMesh() const noexcept
{
	return mMesh;
}

void GeometryNodeC::setMesh(Mesh* mesh) noexcept
{
	mMesh = mesh;
}

Material* GeometryNodeC::getMaterial() const noexcept
{
	return mMaterial;
}

void GeometryNodeC::setMaterial(Material* material) noexcept
{
	mMaterial = material;
}

void GeometryNodeC::render() const noexcept
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

// End of the namespace gltut
}
