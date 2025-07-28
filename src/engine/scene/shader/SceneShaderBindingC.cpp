// Includes
#include "SceneShaderBindingC.h"
#include "engine/renderer/shader/Shader.h"
#include "engine/scene/Scene.h"

namespace gltut
{

// Global classes
Shader* SceneShaderBindingC::getShader() const noexcept
{
	return mShader;
}

void SceneShaderBindingC::setShader(
	Shader* shader,
	bool resetParameters) noexcept
{
	mShader = shader;
	if (resetParameters)
	{
		for (auto& name : mShaderParameters)
		{
			name.clear();
		}
	}
}

const char* SceneShaderBindingC::getBoundShaderParameter(
	Parameter parameter) const noexcept
{
	const auto& result = mShaderParameters[static_cast<size_t>(parameter)];
	return result.empty() ? nullptr : result.c_str();
}

void SceneShaderBindingC::bind(
	Parameter parameter,
	const char* shaderParameter) noexcept
{
	mShaderParameters[static_cast<size_t>(parameter)] =
		(shaderParameter != nullptr) ? shaderParameter : "";
}

void SceneShaderBindingC::activate(const Scene* scene) const noexcept
{
	if (mShader == nullptr ||
		scene == nullptr ||
		scene->getActiveCamera() == nullptr)
	{
		return;
	}

	mShader->activate();

	const Camera* camera = scene->getActiveCamera();

	if (const char* cameraView = getBoundShaderParameter(Parameter::CAMERA_VIEW_MATRIX);
		cameraView != nullptr)
	{
		mShader->setMat4(cameraView, camera->getView().getMatrix().data());
	}

	if (const char* cameraProjection = getBoundShaderParameter(Parameter::CAMERA_PROJECTION_MATRIX);
		cameraProjection != nullptr)
	{
		mShader->setMat4(cameraProjection, camera->getProjection().getMatrix().data());
	}

	if (const char* cameraPosition = getBoundShaderParameter(Parameter::CAMERA_POSITION);
		cameraPosition != nullptr)
	{
		const Vector3& position = camera->getView().getPosition();
		mShader->setVec3(cameraPosition, position.x, position.y, position.z);
	}
}

/// Activates the shader binding for a scene object
void SceneShaderBindingC::activate(const SceneObject* sceneObject) const noexcept
{
	if (mShader == nullptr || sceneObject == nullptr)
	{
		return;
	}

	mShader->activate();

	if (const char* objectMatrix = getBoundShaderParameter(Parameter::OBJECT_MATRIX);
		objectMatrix != nullptr)
	{
		mShader->setMat4(objectMatrix, sceneObject->getTransform().data());
	}

	if (const char* objectNormalMatrix = getBoundShaderParameter(Parameter::OBJECT_NORMAL_MATRIX);
		objectNormalMatrix != nullptr)
	{
		const Matrix3 normalMatrix = getNormalMatrix(sceneObject->getTransform().getMatrix3());
		mShader->setMat3(objectNormalMatrix, normalMatrix.data());
	}
}

// End of the namespace gltut
}
