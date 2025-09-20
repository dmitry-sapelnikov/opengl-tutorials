#pragma once

// Includes
#include <chrono>
#include <deque>

#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"

#include "./camera/CameraC.h"
#include "./nodes/GeometryNodeC.h"
#include "./nodes/GroupNodeC.h"
#include "./nodes/LightNodeC.h"
#include "./shader/SceneShaderBindingC.h"
#include "./texture/SceneTextureSetBindingC.h"

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

	/// Returns the render group for all objects except depth-sorted ones
	const RenderGeometryGroup* getRenderGroup() const noexcept final
	{
		return mOpaqueRenderGroup;
	}

	/// Returns the render group for depth-sorted objects
	const RenderGeometryGroup* getDepthSortedRenderGroup() const noexcept final
	{
		return mDepthSortedRenderGroup;
	}

	/// Creates a binding between a shader and the scene
	SceneShaderBinding* createShaderBinding(Shader* shader) noexcept final;

	/// Removes a shader binding
	void removeShaderBinding(SceneShaderBinding* binding) noexcept final;

	/// Returns the number of shader bindings
	u32 getShaderBindingCount() const noexcept final
	{
		return static_cast<u32>(mShaderBindings.size());
	}

	/// Returns the shader binding at the given index
	SceneShaderBinding* getShaderBinding(u32 index) const noexcept final
	{
		return mShaderBindings[index].get();
	}

	/// Creates a binding between a texture set and the scene
	SceneTextureSetBinding* createTextureSetBinding(
		TextureSet* textureSet) noexcept final;

	/// Removes a texture set binding
	void removeTextureSetBinding(SceneTextureSetBinding* binding) noexcept final;

	/// Returns the number of texture set bindings
	u32 getTextureSetBindingCount() const noexcept final
	{
		return static_cast<u32>(mTextureSetBindings.size());
	}

	/// Returns the texture set binding at the given index
	SceneTextureSetBinding* getTextureSetBinding(u32 index) const noexcept final
	{
		return mTextureSetBindings[index].get();
	}

	/// Creates a group node
	SceneNode* createGeometryGroup(
		const Matrix4& transform = Matrix4::identity(),
		SceneNode* parent = nullptr) noexcept final;

	/// Creates a geometry node
	GeometryNode* createGeometry(
		const Geometry* geometry,
		const Material* material,
		const Matrix4& transform,
		SceneNode* parent,
		bool depthSorted) noexcept final;

	/// Returns the number of geometry nodes
	u32 getGeometryCount() const noexcept final
	{
		return static_cast<u32>(mGeometries.size());
	}

	/// Returns the geometry node at the given index
	GeometryNode* getGeometry(u32 index) const noexcept final
	{
		return &const_cast<GeometryNodeC&>(mGeometries[index]);
	}

	/// Creates a light node
	LightNode* createLight(
		LightNode::Type type,
		const Matrix4& transform = Matrix4::identity(),
		SceneNode* parent = nullptr) noexcept override;

	/// Returns the number of light nodes
	u32 getLightCount() const noexcept final
	{
		return static_cast<u32>(mLights.size());
	}

	/// Returns the light node at the given index
	LightNode* getLight(u32 index) const noexcept final
	{
		return &const_cast<LightNodeC&>(mLights[index]);
	}

	/// Creates a camera
	Camera* createCamera(
		const Vector3& position,
		const Vector3& target,
		const Vector3& up,
		float fovDegrees,
		float nearPlane,
		float farPlane,
		const float* aspectRatio = nullptr) noexcept final;

	/// Returns the active camera
	Camera* getActiveCamera() const noexcept final
	{
		return mActiveCamera;
	}

	/// Returns the viewpoint of the active camera
	const Viewpoint* getActiveCameraViewpoint() const noexcept final
	{
		return &mActiveCameraViewpoint;
	}

	/// Sets the active camera
	void setActiveCamera(Camera* camera) noexcept final;

	/// Adds a camera controller
	void addCameraController(CameraController* controller) noexcept final;

	/// Removes a camera controller
	void removeCameraController(CameraController* controller) noexcept final;

	/// Updates the scene
	void update() noexcept;

private:
	/// The window
	Window& mWindow;

	/// The device
	Renderer& mRenderer;

	/// The render group for opaque objects
	RenderGeometryGroup* mOpaqueRenderGroup = nullptr;

	/// The render group for transparent objects
	RenderGeometryGroup* mDepthSortedRenderGroup = nullptr;

	/// The shader bindings
	std::vector<std::unique_ptr<SceneShaderBindingC>> mShaderBindings;

	/// The texture set bindings
	std::vector<std::unique_ptr<SceneTextureSetBindingC>> mTextureSetBindings;

	/// Group nodes
	std::deque<GroupNodeC> mGroups;

	/// Geometry nodes
	std::deque<GeometryNodeC> mGeometries;

	/// Light nodes
	std::deque<LightNodeC> mLights;

	/// The cameras
	std::deque<CameraC> mCameras;

	/// The camera controllers
	std::vector<CameraController*> mCameraControllers;

	/// The active camera
	Camera* mActiveCamera = nullptr;

	/// The active camera viewpoint
	CameraViewpointC mActiveCameraViewpoint {nullptr};

	/// Creation time
	std::chrono::time_point<std::chrono::high_resolution_clock> mCreationTime;

	/// The last update time
	std::chrono::time_point<std::chrono::high_resolution_clock> mLastUpdateTime;
};

// End of the namespace gltut
}
