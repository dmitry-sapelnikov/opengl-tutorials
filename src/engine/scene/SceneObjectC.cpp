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

void SceneObjectC::render() const noexcept
{
	if (mMaterial != nullptr)
	{
		mMaterial->activate();
		
		if (Shader* shader = mMaterial->getShader();
			shader != nullptr)
		{
			if (const char* modelMatrixName = shader->getSceneParameterName(Shader::SceneParameter::MODEL);
				modelMatrixName != nullptr)
			{
				shader->setMat4(modelMatrixName, mTransform.data());
			}

			if (const char* normalMatrixName = shader->getSceneParameterName(Shader::SceneParameter::NORMAL);
				normalMatrixName != nullptr)
			{
				shader->setMat3(
					normalMatrixName,
					getNormalMatrix(mTransform.getMatrix3()).data());
			}
		}
	}

	if (mMesh != nullptr)
	{
		mRenderer.renderMesh(mMesh->getIndexInRenderer());
	}
}

// End of the namespace gltut
}
