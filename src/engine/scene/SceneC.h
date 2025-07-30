#pragma once

// Includes
#include <deque>
#include <chrono>
#include "engine/core/NonCopyable.h"
#include "engine/scene/Scene.h"

#include "../renderer/RendererBase.h"

#include "./camera/CameraC.h"
#include "./material/MaterialC.h"
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
	SceneC(
		Window& window,
		RendererBase& renderer);

	SceneShaderBinding* createShaderBinding(Shader* shader) noexcept final;

	Material* createMaterial(SceneShaderBinding* shader) noexcept final;

	GeometryNode* createGeometry(
		const Mesh* mesh,
		const Material* material,
		const Matrix4& transform = Matrix4::identity(),
		SceneNode* parent = nullptr) noexcept final;

	LightNode* createLight(
		LightNode::Type type,
		const Matrix4& transform = Matrix4::identity(),
		const SceneNode* parent = nullptr) noexcept override;

	Camera* createCamera(
		const Vector3& position,
		const Vector3& target,
		const Vector3& up,
		float fovDegrees,
		float nearPlane,
		float farPlane,
		const float* aspectRatio = nullptr) noexcept final;

	Camera* getActiveCamera() const noexcept final;

	void setActiveCamera(Camera* camera) noexcept final;

	void addCameraController(CameraController* controller) noexcept final;

	void removeCameraController(CameraController* controller) noexcept final;

	void update() noexcept;

	void render() noexcept;

private:
	/// The window
	Window& mWindow;

	/// The renderer
	RendererBase& mRenderer;

	/// The shader bindings
	std::deque<SceneShaderBindingC> mShaderBindings;

	/// The materials
	std::deque<MaterialC> mMaterials;

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

	/// Creation time
	std::chrono::time_point<std::chrono::high_resolution_clock> mCreationTime;

	/// The last update time
	std::chrono::time_point<std::chrono::high_resolution_clock> mLastUpdateTime;
};

// End of the namespace gltut
}
