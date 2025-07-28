// Includes
#include "SceneC.h"
#include <stdexcept>
#include "engine/core/Check.h"

namespace gltut
{

SceneC::SceneC(
	Window& window,
	RendererBase& renderer) :

	mWindow(window),
	mRenderer(renderer)
{
	// Set the background color
	mRenderer.setClearColor(0.1f, 0.3f, 0.3f, 1.0f);

	// Get creation time in ms using high resolution clock
	mCreationTime = std::chrono::high_resolution_clock::now();
	mLastUpdateTime = mCreationTime;
}

SceneShaderBinding* SceneC::createShaderBinding(Shader* shader) noexcept
{
	SceneShaderBinding* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = &mShaderBindings.emplace_back(shader);
	GLTUT_CATCH_ALL_END("Cannot create a shader binding")
	return result;
}

Material* SceneC::createMaterial(SceneShaderBinding* shaderBinding) noexcept
{
	Material* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = &mMaterials.emplace_back(shaderBinding);
	GLTUT_CATCH_ALL_END("Cannot create a material")
	return result;
}

SceneObject* SceneC::createObject(
	Mesh* mesh,
	Material* material,
	const Matrix4& transform) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		return &mObjects.emplace_back(mRenderer, mesh, material, transform);
	GLTUT_CATCH_ALL_END("Cannot create a scene object")
		return nullptr;
}

Camera* SceneC::createCamera(
	const Vector3& position,
	const Vector3& target,
	const Vector3& up,
	float fovDegrees,
	float nearPlane,
	float farPlan,
	const float* aspectRatio) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		auto* camera = &mCameras.emplace_back(
			mWindow,
			position,
			target,
			up,
			fovDegrees,
			nearPlane,
			farPlan,
			aspectRatio);

	if (mActiveCamera == nullptr)
	{
		mActiveCamera = camera;
	}
	return camera;
	GLTUT_CATCH_ALL_END("Cannot create a camera")

		return nullptr;
}

Camera* SceneC::getActiveCamera() const noexcept
{
	return mActiveCamera;
}

void SceneC::setActiveCamera(Camera* camera) noexcept
{
	mActiveCamera = camera;
}

void SceneC::addCameraController(CameraController* controller) noexcept
{
	GLTUT_ASSERT(controller != nullptr);
	GLTUT_CATCH_ALL_BEGIN
		mCameraControllers.push_back(controller);
	GLTUT_CATCH_ALL_END("Cannot add a camera controller")
}

void SceneC::removeCameraController(CameraController* controller) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		auto it = std::find(
			mCameraControllers.begin(),
			mCameraControllers.end(),
			controller);

		if (it != mCameraControllers.end())
		{
			mCameraControllers.erase(it);
		}
	GLTUT_CATCH_ALL_END("Cannot remove a camera controller")
}

void SceneC::update() noexcept
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto timeMs = std::chrono::duration_cast<std::chrono::milliseconds>(
		currentTime - mCreationTime).count();

	const auto timeDeltaMs = static_cast<u32>(
		std::chrono::duration_cast<std::chrono::milliseconds>(
		currentTime - mLastUpdateTime).count());

	if (timeDeltaMs == 0)
	{
		return;
	}

	for (auto* controller : mCameraControllers)
	{
		controller->updateCamera(timeMs, timeDeltaMs);
	}
	mLastUpdateTime = currentTime;
}

void SceneC::render() noexcept
{
	for (auto& shaderBinding: mShaderBindings)
	{
		shaderBinding.activate(this);
	}

	for (const auto& object : mObjects)
	{
		object.render();
	}
}

// End of the namespace gltut
}
