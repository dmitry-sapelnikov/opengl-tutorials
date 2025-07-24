#ifndef OPENGL_TUTORIALS_SCENE_C_H
#define OPENGL_TUTORIALS_SCENE_C_H

// Includes
#include <deque>
#include <chrono>
#include "engine/core/NonCopyable.h"
#include "engine/Scene.h"

#include "./scene/camera/CameraC.h"
#include "./material/MaterialC.h"
#include "MeshC.h"
#include "SceneObjectC.h"
#include "RendererBase.h"

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

	Material* createMaterial(Shader* shader) noexcept final;

	Mesh* createMesh(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertexData,
		u32 indexCount,
		const u32* indexData) noexcept final;

	SceneObject* createObject(
		Mesh* mesh,
		Material* material,
		const Matrix4& transform = Matrix4::identity()) noexcept final;

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

	/// The materials
	std::deque<MaterialC> mMaterials;

	/// The meshes
	std::deque<MeshC> mMeshes;

	/// The scene objects
	std::deque<SceneObjectC> mObjects;

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

#endif
