#ifndef OPENGL_TUTORIALS_SCENE_C_H
#define OPENGL_TUTORIALS_SCENE_C_H

// Includes
#include <deque>
#include "engine/core/NonCopyable.h"
#include "engine/Scene.h"
#include "RendererBase.h"
#include "MaterialC.h"
#include "MeshC.h"
#include "SceneObjectC.h"
#include "CameraC.h"

namespace gltut
{
// Global classes
/// Implementation of the Scene interface
class SceneC final : public Scene, public NonCopyable
{
public:
	SceneC(
		WindowC& window,
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

	void render() noexcept final;

private:
	/// The window
	WindowC& mWindow;

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

	/// The active camera
	Camera* mActiveCamera = nullptr;
};

// End of the namespace gltut
}

#endif
