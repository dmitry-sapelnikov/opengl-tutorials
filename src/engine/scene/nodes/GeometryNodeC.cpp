// Includes
#include "GeometryNodeC.h"

namespace gltut
{
// Global classes
GeometryNodeC::GeometryNodeC(
	const Mesh* mesh,
	const Material* material,
	const Matrix4& transform,
	const SceneNode* parent) noexcept :
	
	SceneNodeT<GeometryNode>(transform, parent),
	mMesh(mesh),
	mMaterial(material)
{
}

void GeometryNodeC::setMesh(const Mesh* mesh) noexcept
{
	mMesh = mesh;
}

void GeometryNodeC::setMaterial(const Material* material) noexcept
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
