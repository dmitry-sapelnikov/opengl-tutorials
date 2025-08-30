#pragma once

// Includes
#include "engine/renderer/objects/RenderGeometryGroup.h"
#include "engine/scene/camera/CameraController.h"
#include "engine/scene/shader/SceneShaderBinding.h"
#include "engine/scene/texture/SceneTextureSetBinding.h"
#include "engine/scene/nodes/GeometryNode.h"
#include "engine/scene/nodes/LightNode.h"

namespace gltut
{
// Global classes
/// The class represents a scene
class Scene
{
public:
	/// Virtual destructor
	virtual ~Scene() noexcept = default;

	/// Returns the render group for all objects except depth-sorted ones
	virtual const RenderGeometryGroup* getRenderGroup() const noexcept = 0;

	/// Returns the render group for depth-sorted objects
	virtual const RenderGeometryGroup* getDepthSortedRenderGroup() const noexcept = 0;

	/// Returns the active camera
	virtual Camera* getActiveCamera() const noexcept = 0;

	/// Returns the active camera viewpoint
	virtual const Viewpoint* getActiveCameraViewpoint() const noexcept = 0;

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

	/// Removes a shader binding from the scene
	virtual void removeShaderBinding(SceneShaderBinding* binding) noexcept = 0;

	/// Returns the number of shader bindings in the scene
	virtual u32 getShaderBindingCount() const noexcept = 0;

	/// Returns the shader binding at the specified index
	virtual SceneShaderBinding* getShaderBinding(u32 index) const noexcept = 0;

	/// Creates a binding between a texture set and the scene
	virtual SceneTextureSetBinding* createTextureSetBinding(
		TextureSet* textureSet) noexcept = 0;

	/// Returns the number of texture set bindings in the scene
	virtual u32 getTextureSetBindingCount() const noexcept = 0;

	/// Returns the texture set binding at the specified index
	virtual SceneTextureSetBinding* getTextureSetBinding(u32 index) const noexcept = 0;

	/// Removes a texture set binding from the scene
	virtual void removeTextureSetBinding(SceneTextureSetBinding* binding) noexcept = 0;

	/// Creates a scene group node
	virtual SceneNode* createGeometryGroup(
		const Matrix4& transform = Matrix4::identity(),
		SceneNode* parent = nullptr) noexcept = 0;

	/// Creates a scene object
	virtual GeometryNode* createGeometry(
		const Geometry* geometry,
		const Material* material,
		const Matrix4& transform = Matrix4::identity(),
		SceneNode* parent = nullptr,
		bool depthSorted = false) noexcept = 0;

	/// Returns the number of geometries in the scene
	virtual u32 getGeometryCount() const noexcept = 0;

	/// Returns the geometry at the specified index
	virtual GeometryNode* getGeometry(u32 index) const noexcept = 0;

	/// Creates a scene light
	virtual LightNode* createLight(
		LightNode::Type type,
		const Matrix4& transform = Matrix4::identity(),
		SceneNode* parent = nullptr) noexcept = 0;

	/// Returns the number of lights in the scene
	virtual u32 getLightCount() const noexcept = 0;

	/// Returns the light at the specified index
	virtual LightNode* getLight(u32 index) const noexcept = 0;
};

// End of the namespace gltut
}
