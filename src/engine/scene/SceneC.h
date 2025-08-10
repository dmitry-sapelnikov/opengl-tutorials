#pragma once

// Includes
#include <deque>
#include <chrono>
#include "engine/core/NonCopyable.h"
#include "engine/scene/Scene.h"
#include "engine/renderer/Renderer.h"

#include "./camera/CameraC.h"
#include "./shader/SceneShaderBindingC.h"
#include "./nodes/GeometryNodeC.h"
#include "./nodes/LightNodeC.h"

namespace gltut
{
// Global classes
/// Implementation of the Scene interface
class SceneC final : public Scene, public NonCopyable
{
public:
	/// Constructor
	SceneC(
		Window& window,
		Renderer& renderer);

	/// Returns the render object for the scene
	const RenderObject* getRenderObject() const noexcept final
	{
		return mRenderGroup;
	}

	SceneShaderBinding* createShaderBinding(Shader* shader) noexcept final;

	u32 getShaderBindingCount() const noexcept final
	{
		return static_cast<u32>(mShaderBindings.size());
	}

	SceneShaderBinding* getShaderBinding(u32 index) const noexcept final
	{
		return &const_cast<SceneShaderBindingC&>(mShaderBindings[index]);
	}

	GeometryNode* createGeometry(
		const Mesh* mesh,
		const Material* material,
		const Matrix4& transform = Matrix4::identity(),
		SceneNode* parent = nullptr) noexcept final;

	u32 getGeometryCount() const noexcept final
	{
		return static_cast<u32>(mGeometries.size());
	}

	GeometryNode* getGeometry(u32 index) const noexcept final
	{
		return &const_cast<GeometryNodeC&>(mGeometries[index]);
	}

	LightNode* createLight(
		LightNode::Type type,
		const Matrix4& transform = Matrix4::identity(),
		SceneNode* parent = nullptr) noexcept override;

	u32 getLightCount() const noexcept final
	{
		return static_cast<u32>(mLights.size());
	}

	LightNode* getLight(u32 index) const noexcept final
	{
		return &const_cast<LightNodeC&>(mLights[index]);
	}

	Camera* createCamera(
		const Vector3& position,
		const Vector3& target,
		const Vector3& up,
		float fovDegrees,
		float nearPlane,
		float farPlane,
		const float* aspectRatio = nullptr) noexcept final;

	Camera* getActiveCamera() const noexcept final
	{
		return mActiveCamera;
	}

	const Viewpoint* getActiveCameraViewpoint() const noexcept final
	{
		return &mActiveCameraViewpoint;
	}

	void setActiveCamera(Camera* camera) noexcept final;

	void addCameraController(CameraController* controller) noexcept final;

	void removeCameraController(CameraController* controller) noexcept final;

	void update() noexcept;

private:
	/// The window
	Window& mWindow;

	/// The device
	Renderer& mRenderer;

	/// The scene render group
	RenderGroup* mRenderGroup = nullptr;

	/// The shader bindings
	std::deque<SceneShaderBindingC> mShaderBindings;

	/// Geometry nodes
	std::deque<GeometryNodeC> mGeometries;

	/// Light nodes
	std::deque<LightNodeC> mLights;

	///	The cameras
	std::deque<CameraC> mCameras;

	/// The camera controllers
	std::vector<CameraController*> mCameraControllers;

	/// The active camera
	Camera* mActiveCamera = nullptr;

	/// The active camera viewpoint
	CameraViewpointC mActiveCameraViewpoint { nullptr };

	/// Creation time
	std::chrono::time_point<std::chrono::high_resolution_clock> mCreationTime;

	/// The last update time
	std::chrono::time_point<std::chrono::high_resolution_clock> mLastUpdateTime;
};

// End of the namespace gltut
}
