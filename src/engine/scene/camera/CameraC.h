#pragma once

// Includes
#include <optional>

#include "engine/core/Check.h"
#include "engine/core/NonCopyable.h"
#include "engine/scene/camera/Camera.h"

#include "./CameraViewpointC.h"

namespace gltut
{
// Global classes
/// Implementation of the camera view
class CameraViewC : public CameraView, public NonCopyable
{
public:
	/// Constructor
	CameraViewC(
		const Vector3& position,
		const Vector3& target,
		const Vector3& up);

	/// Returns the view matrix
	const Matrix4& getMatrix() const noexcept final
	{
		return mMatrix;
	}

	/// Returns the position of the camera
	const Vector3& getPosition() const noexcept final
	{
		return mPosition;
	}

	/// Sets the position of the camera
	void setPosition(const Vector3& position) noexcept final
	{
		mPosition = position;
		update();
	}

	/// Returns the target of the camera
	const Vector3& getTarget() const noexcept final
	{
		return mTarget;
	}

	/// Sets the target of the camera
	void setTarget(const Vector3& target) noexcept final
	{
		mTarget = target;
		update();
	}

	/// Returns the up vector of the camera
	const Vector3& getUp() const noexcept final
	{
		return mUp;
	}

	/// Sets the up vector of the camera
	void setUp(const Vector3& up) noexcept final
	{
		mUp = up;
		update();
	}

private:
	/// Updates the view matrix
	void update() noexcept;

	/// The view matrix
	Matrix4 mMatrix;

	/// The position of the camera
	Vector3 mPosition;

	/// The target of the camera
	Vector3 mTarget;

	/// The up vector of the camera
	Vector3 mUp;
};

/// Implementation of the camera projection
class CameraProjectionC : public CameraProjection, public EventHandler, public NonCopyable
{
public:
	/// Constructor
	CameraProjectionC(
		Window& window,
		float fov,
		float nearPlane,
		float farPlane,
		const float* aspectRatio);

	~CameraProjectionC() noexcept final;

	/// Returns the window associated with the camera
	Window* getWindow() const noexcept final
	{
		return &mWindow;
	}

	/// Returns the projection matrix
	const Matrix4& getMatrix() const noexcept final
	{
		return mMatrix;
	}

	/// Returns the projection matrix with the given aspect ratio
	Matrix4 getMatrix(float aspectRatio) const noexcept final;

	/// Return the field of view, in degrees
	float getFov() const noexcept final
	{
		return mFov;
	}

	/// Sets the field of view, in degrees
	void setFov(float fov) noexcept final
	{
		mFov = fov;
		update();
	}

	/// Returns the near plane
	float getNearPlane() const noexcept final
	{
		return mNearPlane;
	}

	/// Sets the near plane
	void setNearPlane(float nearPlane) noexcept final
	{
		mNearPlane = nearPlane;
		update();
	}

	/// Returns the far plane
	float getFarPlane() const noexcept final
	{
		return mFarPlane;
	}

	/// Sets the far plane
	void setFarPlane(float farPlane) noexcept final
	{
		mFarPlane = farPlane;
		update();
	}

	/**
		\brief Returns the explicit aspect ratio or
		nullptr if the aspect ratio is calculated from the window size
	*/
	const float* getAspectRatio() const noexcept final
	{
		return mAspectRatio.has_value() ? &mAspectRatio.value() : nullptr;
	}

	/**
		\brief Sets either the explicit aspect ratio or
		nullptr to calculate it from the window size
	*/
	void setAspectRatio(const float* aspectRatio) noexcept final;

	/// Called when the window is resized
	bool onEvent(const Event& event) noexcept final
	{
		if (event.type == Event::Type::WINDOW_RESIZE)
		{
			update();
		}
		// Don't stop event propagation
		return false;
	}

private:
	/// Updates the projection matrix
	void update() noexcept;

	/// The window
	Window& mWindow;

	/// The field of view, in degrees
	float mFov;

	/// The near plane
	float mNearPlane;

	/// The far plane
	float mFarPlane;

	/// The aspect ratio, i.e. width / height
	std::optional<float> mAspectRatio;

	/// The projection matrix
	Matrix4 mMatrix;
};

/// Implementation of the camera
class CameraC : public Camera, public NonCopyable
{
public:
	/// Constructor
	CameraC(
		Window& window,
		const Vector3& position,
		const Vector3& target,
		const Vector3& up,

		float fov,
		float nearPlane,
		float farPlane,
		const float* aspectRatio) noexcept :

		mView(position, target, up),
		mProjection(window, fov, nearPlane, farPlane, aspectRatio),
		mViewpoint(this)
	{
	}

	/// Returns the view (const)
	const CameraView& getView() const noexcept final
	{
		return mView;
	}

	/// Returns the view (non-const)
	CameraView& getView() noexcept final
	{
		return mView;
	}

	/// Returns the projection (const)
	const CameraProjection& getProjection() const noexcept final
	{
		return mProjection;
	}

	/// Returns the projection (non-const)
	CameraProjection& getProjection() noexcept final
	{
		return mProjection;
	}

	/// Returns the viewpoint
	const Viewpoint& getViewpoint() const noexcept final
	{
		return mViewpoint;
	}

private:
	/// The view
	CameraViewC mView;

	/// The projection
	CameraProjectionC mProjection;

	/// The viewpoint
	CameraViewpointC mViewpoint;
};

// End of the namespace gltut
}
