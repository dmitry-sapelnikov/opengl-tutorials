#pragma once

// Includes
#include "engine/math/Matrix4.h"
#include "engine/renderer/viewpoint/Viewpoint.h"
#include "engine/window/Window.h"

namespace gltut
{
// Global classes
/// The class represents a camera view
class CameraView
{
public:
	/// Virtual destructor
	virtual ~CameraView() noexcept = default;

	/// Returns the view matrix
	virtual const Matrix4& getMatrix() const noexcept = 0;

	/// Returns the position of the camera
	virtual const Vector3& getPosition() const noexcept = 0;

	/// Sets the position of the camera
	virtual void setPosition(const Vector3& position) noexcept = 0;

	/// Returns the target of the camera
	virtual const Vector3& getTarget() const noexcept = 0;

	/// Sets the target of the camera
	virtual void setTarget(const Vector3& target) noexcept = 0;

	/// Returns the up vector of the camera
	virtual const Vector3& getUp() const noexcept = 0;

	/// Sets the up vector of the camera
	virtual void setUp(const Vector3& up) noexcept = 0;

	Vector3 getDirection() const noexcept
	{
		return (getTarget() - getPosition()).normalize();
	}

	Vector3 getRight() const noexcept
	{
		return getDirection().cross(getUp()).normalize();
	}
};

/// The class represents a camera projection
class CameraProjection
{
public:
	/// Virtual destructor
	virtual ~CameraProjection() noexcept = default;

	/// Returns the window associated with the camera
	virtual Window* getWindow() const noexcept = 0;

	/// Returns the projection matrix
	virtual const Matrix4& getMatrix() const noexcept = 0;

	/// Returns the projection matrix with the given aspect ratio
	virtual Matrix4 getMatrix(float aspectRatio) const noexcept = 0;

	/// Return the field of view, in degrees
	virtual float getFov() const noexcept = 0;

	/// Sets the field of view, in degrees
	virtual void setFov(float fov) noexcept = 0;

	/// Returns the near plane
	virtual float getNearPlane() const noexcept = 0;

	/// Sets the near plane
	virtual void setNearPlane(float nearPlane) noexcept = 0;

	/// Returns the far plane
	virtual float getFarPlane() const noexcept = 0;

	/// Sets the far plane
	virtual void setFarPlane(float farPlane) noexcept = 0;

	/**
		\brief Returns the explicit aspect ratio or
		nullptr if the aspect ratio is calculated from the window size
	*/
	virtual const float* getAspectRatio() const noexcept = 0;

	/**
		\brief Sets either the explicit aspect ratio or
		nullptr to calculate it from the window size
	*/
	virtual void setAspectRatio(const float* aspectRatio) noexcept = 0;
};

/// The class represents a camera
class Camera
{
public:
	/// Virtual destructor
	virtual ~Camera() noexcept = default;

	/// Returns the view (const)
	virtual const CameraView& getView() const noexcept = 0;

	/// Returns the view (non-const)
	virtual CameraView& getView() noexcept = 0;

	/// Returns the projection (const)
	virtual const CameraProjection& getProjection() const noexcept = 0;

	/// Returns the projection (non-const)
	virtual CameraProjection& getProjection() noexcept = 0;

	/// Returns the viewpoint
	virtual const Viewpoint& getViewpoint() const noexcept = 0;
};

// Global functions
/**
	\brief Returns a 3d ray which would go through the 2d screen coodinates
	The ray starts at the camera position and ends at the far plane
*/
Vector3 screenToCameraRay(
	const Point2i& screenPoint,
	const Point2u& windowSize,
	const Vector3& cameraPosition,
	const Matrix4& cameraProjectionViewInverse);

// End of the namespace gltut
}
