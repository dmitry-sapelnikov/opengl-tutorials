#ifndef GLTUT_MOUSE_CAMERA_CONTROLLER_C_H
#define GLTUT_MOUSE_CAMERA_CONTROLLER_C_H

//	Includes
#include "engine/core/NonCopyable.h"
#include "engine/math/Point2.h"
#include "engine/scene/camera/CameraController.h"

namespace gltut
{

///	RTS-style camera animator
class MouseCameraControllerC final :
	public CameraController,
	public EventHandler,
	public NonCopyable
{
public:
	/// Constructor
	MouseCameraControllerC(
		Camera& camera,
		float rotationSpeed,
		float zoomSpeed,
		float translationSpeed,
		float targetMinDistance,
		float targetMaxDistance);

	///	Destructor
	~MouseCameraControllerC() noexcept final;

	/// Returns the camera
	Camera& getCamera() noexcept final
	{
		return mCamera;
	}

	/// Updates the camera
	virtual void updateCamera() noexcept final;

	///	Event handler
	virtual void onEvent(const Event& event) noexcept final;

private:
	///	Checks if a specific mouse button is pressed
	bool isMouseButtonDown(Event::MouseEvent::Button button) noexcept;

	/// The camera
	Camera& mCamera;

	///	Translation speed
	float mTranslationSpeed;

	///	Rotation speed
	float mRotationSpeed;

	///	Zoom speed
	float mZoomSpeed;

	///	Camera position
	Vector3 mPosition;

	///	Camera target
	Vector3 mTarget;

	///	Old camera target
	Vector3 mOldTarget;

	///	Value of the rotation about the X and Y axes
	Vector3 mRotation;

	///	Camera up vector
	Vector3 mUpVector;

	///	Min allowed distance to the camera target
	float mTargetMinDistance = 0.1f;

	///	Max allowed distance from the camera target
	float mTargetMaxDistance = 10000.0f;

	///	Rotation process flag
	bool mRotating = false;

	///	Translation process flag
	bool mTranslating = false;

	///	Rotation start point in the screen coordinates
	Point2i mRotateStart;

	///	Translation start point in the screen coordinates
	Point2i mTranslateStart;

	///	Current zoom value
	float mCurrentZoom = 100.0f;

	///	Mouse position in the screen coordinates
	Point2i mMousePosition;

	///	Table of pressed mouse buttons
	bool mMouseButtons[3]{false, false, false};
};

//	End of the namespace irr::scene
}

#endif
