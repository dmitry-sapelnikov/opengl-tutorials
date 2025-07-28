#pragma once

// Includes
#include "engine/scene/SceneObject.h"
#include "engine/scene/material/Material.h"
#include "engine/scene/camera/CameraController.h"
#include "engine/scene/shader/SceneShaderBinding.h"


namespace gltut
{
// Global classes
/// The class represents a scene
class Scene
{
public:
	/// Virtual destructor
	virtual ~Scene() noexcept = default;

	/// Returns the active camera
	virtual Camera* getActiveCamera() const noexcept = 0;

	/// Sets the active camera
	virtual void setActiveCamera(Camera* camera) noexcept = 0;

	/**
		\brief Adds a camera to the scene.

		\param position The position of the camera
		\param target The target of the camera
		\param up The up vector of the camera
		\param fov The field of view, in degrees
		\param nearPlane The near plane
		\param farPlane The far plane
		\param aspectRatio The aspect ratio, i.e. width / height.
		If nullptr, the aspect ratio is calculated from the window size.
		
		\return The camera if it was added successfully, nullptr otherwise

		\note If there is no active camera, the added camera becomes the active camera.
	*/
	virtual Camera* createCamera(
		const Vector3& position,
		const Vector3& target,
		const Vector3& up,
		float fovDegrees,
		float nearPlane,
		float farPlanee,
		const float* aspectRatio = nullptr) noexcept = 0;

	/**
		\brief Adds a camera controller to the scene
		\param controller The controller
	*/
	virtual void addCameraController(CameraController* controller) noexcept = 0;

	/**
		\brief Removes a camera controller from the scene
		Does nothing if the controller is not in the scene
		\param controller The controller
	*/
	virtual void removeCameraController(CameraController* controller) noexcept = 0;

	///	Creates a binding between a shader and the scene
	virtual SceneShaderBinding* createShaderBinding(Shader* shader) noexcept = 0;

	/**
		\brief Creates a material
		\param shaderBinding The shader binding to use for the material
	*/
	virtual Material* createMaterial(SceneShaderBinding* shaderBinding) noexcept = 0;

	/// Creates a scene object
	virtual SceneObject* createObject(
		Mesh* mesh,
		Material* material,
		const Matrix4& transform = Matrix4::identity()) noexcept = 0;
};

// End of the namespace gltut
}
