//	Includes
#include <algorithm>
#include "FPSCameraControllerC.h"
#include "engine/core/Check.h"

namespace gltut
{
//	Global classes
FPSCameraControllerC::FPSCameraControllerC(
	Camera& camera,
	float translationSpeed,
	float mouseSensitivity) :

	mCamera(camera),
	mTranslationSpeed(translationSpeed),
	mMouseSensitivity(mouseSensitivity)
{
	GLTUT_CHECK(
		mTranslationSpeed > 0.0F,
		"The translation speed must be positive");

	GLTUT_CHECK(
		mMouseSensitivity > 0.0F,
		"The mouse sensitivity must be positive");

	auto* window = mCamera.getProjection().getWindow();

	const auto windowSize = window->getSize();
	mPrevMousePosition = { (int32)windowSize.x / 2, (int32)windowSize.y / 2 };
	mMousePosition = mPrevMousePosition;
	window->setCursorPosition(mPrevMousePosition);

	const auto& view = mCamera.getView();
	const Vector3 up = view.getUp();
	const Vector3 right = view.getRight();
	const Vector3 front = up.cross(right).normalize();

	mPitchYawBasis.setAxis(0, front);
	mPitchYawBasis.setAxis(1, right);
	mPitchYawBasis.setAxis(2, up);

	Matrix4 pitchYawBasisInv = mPitchYawBasis.getInverse();
	const Vector3 directionLocal = pitchYawBasisInv * view.getDirection();
	const Vector3 distanceAzimuthInclination =
		getDistanceAzimuthInclination(directionLocal);
	mYaw = toDegrees(distanceAzimuthInclination.y);
	mPitch = toDegrees(distanceAzimuthInclination.z);

	window->addEventHandler(this);
}

FPSCameraControllerC::~FPSCameraControllerC() noexcept
{
	mCamera.getProjection().getWindow()->removeEventHandler(this);
}

void FPSCameraControllerC::updateCamera(
	u64,
	u32 timeDeltaMs) noexcept
{
	auto& view = mCamera.getView();
	const Point2i mouseDelta = mMousePosition - mPrevMousePosition;
	if (!mouseDelta.isZero())
	{
		mYaw += mouseDelta.x * mMouseSensitivity;
		// The pitch is inverted because the mouse Y-axis is inverted
		mPitch -= mouseDelta.y * mMouseSensitivity;

		// Clamp the pitch to prevent the camera from flipping
		mPitch = std::clamp(mPitch, -89.0f, 89.0f);
		const Vector3 localDir = setDistanceAzimuthInclination(
			{ 1.0f, toRadians(mYaw), toRadians(mPitch) });

		const Vector3 direction = mPitchYawBasis * localDir;
		view.setTarget(view.getPosition() + direction);
		mPrevMousePosition = mMousePosition;
	}

	if (mMoveRight - mMoveLeft != 0 ||
		mMoveFront - mMoveBack != 0)
	{
		Vector3 movement(
			static_cast<float>(mMoveRight - mMoveLeft),
			static_cast<float>(mMoveFront - mMoveBack),
			0.0f);
		movement.normalize();
		movement *= mTranslationSpeed * (timeDeltaMs / 1000.0f);

		const Vector3 positionDelta =
			view.getRight() * movement.x +
			view.getDirection() * movement.y;

		view.setPosition(view.getPosition() + positionDelta);
		view.setTarget(view.getTarget() + positionDelta);
	}
}

bool FPSCameraControllerC::onEvent(const Event& event) noexcept
{
	switch (event.type)
	{
	case Event::Type::KEYBOARD:
		switch (event.keyboard.key)
		{
		case KeyCode::W:
			mMoveFront = event.keyboard.pressedDown;
			break;

		case KeyCode::S:
			mMoveBack = event.keyboard.pressedDown;
			break;

		case KeyCode::A:
			mMoveLeft = event.keyboard.pressedDown;
			break;

		case KeyCode::D:
			mMoveRight = event.keyboard.pressedDown;
			break;
		}
		break;

	case Event::Type::MOUSE:
		mMousePosition = event.mouse.position;
		break;
	}
	/// Dont't stop the event propagation
	return false;
}

//	Global functions
CameraController* createFPSCameraController(
	Camera& camera,
	float translationSpeed,
	float mouseSensitivity) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		return new FPSCameraControllerC(
			camera,
			translationSpeed,
			mouseSensitivity);
	GLTUT_CATCH_ALL_END("Cannot create a FPS camera controller");
	return nullptr;
}

} // end namespace
