// Includes
#include "SceneC.h"
#include "engine/core/Check.h"

namespace gltut
{

SceneC::SceneC(
	Window& window,
	Renderer& renderer) :

	mWindow(window),
	mRenderer(renderer)
{
	mRenderGroup = mRenderer.createGroup();
	GLTUT_CHECK(mRenderGroup != nullptr,
		"Cannot create a render group for the scene");

	// Get creation time in ms using high resolution clock
	mCreationTime = std::chrono::high_resolution_clock::now();
	mLastUpdateTime = mCreationTime;
}

SceneShaderBinding* SceneC::createShaderBinding(Shader* shader) noexcept
{
	SceneShaderBinding* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = mShaderBindings.emplace_back(
			std::make_unique<SceneShaderBindingC>(shader)).get();
	GLTUT_CATCH_ALL_END("Cannot create a shader binding")
	return result;
}

void SceneC::removeShaderBinding(SceneShaderBinding* binding) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		auto it = std::find_if(
			mShaderBindings.begin(),
			mShaderBindings.end(),
			[binding](const auto& b) {
				return b.get() == binding;
			});
		if (it != mShaderBindings.end())
		{
			mShaderBindings.erase(it);
		}
	GLTUT_CATCH_ALL_END("Cannot remove a shader binding")
}

SceneTextureSetBinding* SceneC::createTextureSetBinding(
	TextureSet* textureSet) noexcept
{
	SceneTextureSetBinding* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = mTextureSetBindings.emplace_back(
			std::make_unique<SceneTextureSetBindingC>(textureSet)).get();
	GLTUT_CATCH_ALL_END("Cannot create a texture set binding")
	return result;
}

void SceneC::removeTextureSetBinding(SceneTextureSetBinding* binding) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		auto it = std::find_if(
			mTextureSetBindings.begin(),
			mTextureSetBindings.end(),
			[binding](const auto& b)
			{
				return b.get() == binding;
			});
		if (it != mTextureSetBindings.end())
		{
			mTextureSetBindings.erase(it);
		}
	GLTUT_CATCH_ALL_END("Cannot remove a texture set binding")
}

GeometryNode* SceneC::createGeometry(
	const Mesh* mesh,
	const Material* material,
	const Matrix4& transform,
	SceneNode* parent) noexcept
{
	RenderGeometry* renderGeometry = mRenderer.createGeometry(
		mesh,
		material,
		Matrix4::identity());

	if (renderGeometry == nullptr)
	{
		return nullptr;
	}

	mRenderGroup->addObject(renderGeometry);
	GeometryNode* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = &mGeometries.emplace_back(*renderGeometry, transform, parent);
	GLTUT_CATCH_ALL_END("Cannot create a scene geometry");
	return result;
}

LightNode* SceneC::createLight(
	LightNode::Type type,
	const Matrix4& transform,
	SceneNode* parent) noexcept
{
	LightNode* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = &mLights.emplace_back(type, transform, parent);
	GLTUT_CATCH_ALL_END("Cannot create a light")
	return result;
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
	Camera* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = &mCameras.emplace_back(
			mWindow,
			position,
			target,
			up,
			fovDegrees,
			nearPlane,
			farPlan,
			aspectRatio);
		// Set the active camera if it is not set yet
		if (getActiveCamera() == nullptr)
		{
			setActiveCamera(result);
		}
	GLTUT_CATCH_ALL_END("Cannot create a camera")
	return result;
}

void SceneC::setActiveCamera(Camera* camera) noexcept
{
	mActiveCamera = camera;
	mActiveCameraViewpoint.setCamera(camera);
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

	for (auto& shaderBinding : mShaderBindings)
	{
		shaderBinding->update(this);
	}

	for (auto& textureSetBinding : mTextureSetBindings)
	{
		textureSetBinding->update(this);
	}
}

// End of the namespace gltut
}
