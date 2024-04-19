// Includes
#include "SceneObjectC.h"

namespace gltut
{
// Global classes
SceneObjectC::SceneObjectC(
	RendererBase& renderer,
	Mesh* mesh,
	Material* material,
	const Matrix4& transform) noexcept :
	
	mRenderer(renderer),
	mMesh(mesh),
	mMaterial(material),
	mTransform(transform)
{
}

const Matrix4& SceneObjectC::getTransform() const noexcept
{
	return mTransform;
}

void SceneObjectC::setTransform(const Matrix4& transform) noexcept
{
	mTransform = transform;
}

Mesh* SceneObjectC::getMesh() const noexcept
{
	return mMesh;
}

void SceneObjectC::setMesh(Mesh* mesh) noexcept
{
	mMesh = mesh;
}

Material* SceneObjectC::getMaterial() const noexcept
{
	return mMaterial;
}

void SceneObjectC::setMaterial(Material* material) noexcept
{
	mMaterial = material;
}

const char* SceneObjectC::getShaderTransformInputName() const noexcept
{
	return mShaderTransformInputName.c_str();
}

void SceneObjectC::setShaderTransformInputName(const char* name) noexcept
{
	mShaderTransformInputName = name;
}

void SceneObjectC::render() const noexcept
{
	if (mMaterial != nullptr)
	{
		mMaterial->use();
		if (mMaterial->getShader() != nullptr &&
			!mShaderTransformInputName.empty())
		{
			mMaterial->getShader()->setMat4(
				mShaderTransformInputName.c_str(),
				mTransform.data());
		}
	}

	if (mMesh != nullptr)
	{
		mRenderer.renderMesh(mMesh->getIndexInRenderer());
	}
}

// End of the namespace gltut
}
