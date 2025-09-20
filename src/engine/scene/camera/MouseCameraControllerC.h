// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/math/Point2.h"
#include "engine/scene/camera/CameraController.h"

namespace gltut
{

/// Implementation of the mouse camera controller
class MouseCameraControllerC final : public CameraController, public EventHandler, public NonCopyable
{
public:
	/// Constructor
	MouseCameraControllerC(
		Camera& camera,
		float mouseSpeed,
		float zoomSpeed,
		float targetMinDistance,
		float targetMaxDistance);

	/// Destructor
	~MouseCameraControllerC() noexcept final;

	/// Returns the camera
	Camera& getCamera() noexcept final
	{
		return mCamera;
	}

	/// Updates the camera
	virtual void updateCamera(
		u64 timeMs,
		u32 timeDeltaMs) noexcept final;

	/**
		\brief Called when an event occurs
		\return True if the event was handled, false to continue processing
	*/
	virtual bool onEvent(const Event& event) noexcept final;

private:
	/// The camera
	Camera& mCamera;

	/// Rotation speed
	float mMouseSpeed;

	/// Zoom speed
	float mZoomSpeed;

	/// Camera position
	Vector3 mPosition;

	/// Camera target
	Vector3 mInitialTarget;

	/// Camera position
	Vector3 mInitialPosition;

	Point2u mWindowSize;

	Matrix4 mProjectionViewInv;

	Vector3 mDragStart;

	/// The camera's yaw, in degrees
	float mYaw = 0.0F;

	/// The camera's pitch, in degrees
	float mPitch = 0.0F;

	/// The basis for the pitch and yaw
	Matrix4 mPitchYawBasis = Matrix4::identity();

	/// Min allowed distance to the camera target
	float mTargetMinDistance = 0.1f;

	/// Max allowed distance from the camera target
	float mTargetMaxDistance = 10000.0f;

	/// Rotation process flag
	bool mRotating = false;

	/// Translation process flag
	bool mTranslating = false;

	/// Translation start point in the screen coordinates
	Point2i mMouseStart;

	float mPrevZoom = 0.0f;

	/// Current zoom value
	float mCurrentZoom = 0.0f;

	/// Mouse position in the screen coordinates
	Point2i mMousePosition;

	Event::MouseEvent::Buttons mMouseButtons;
};

// End of the namespace gltut
}
