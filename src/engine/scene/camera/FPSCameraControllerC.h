#pragma once

//	Includes
#include "engine/core/NonCopyable.h"
#include "engine/scene/camera/CameraController.h"

namespace gltut
{

///	RTS-style camera animator
class FPSCameraControllerC final :
	public CameraController,
	public EventHandler,
	public NonCopyable
{
public:
	/// Constructor
	FPSCameraControllerC(
		Camera& camera,
		float translationSpeed,
		float mouseSensitivity);


	///	Destructor
	~FPSCameraControllerC() noexcept final;

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

	///	Translation speed, units per second
	float mTranslationSpeed;

	///	Mouse sensitivity, degrees per pixel
	float mMouseSensitivity;

	///	Front movement flag
	bool mMoveFront = false;

	///	Back movement flag
	bool mMoveBack = false;

	///	Left movement flag
	bool mMoveLeft = false;

	///	Right movement flag
	bool mMoveRight = false;

	/// The current mouse position
	Point2i mMousePosition;

	/// The previous mouse position
	Point2i mPrevMousePosition;

	/// The camera's yaw, in degrees
	float mYaw = 0.0F;

	/// The camera's pitch, in degrees
	float mPitch = 0.0F;

	/// The basis for the pitch and yaw
	Matrix4 mPitchYawBasis = Matrix4::identity();
};

//	End of the namespace gltut
}
