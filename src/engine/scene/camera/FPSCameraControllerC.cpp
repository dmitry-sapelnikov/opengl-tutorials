//	Includes
#include <algorithm>
#include "FPSCameraControllerC.h"
#include "engine/core/Check.h"

namespace gltut
{

//	Global classes
FPSCameraControllerC::FPSCameraControllerC(
	Camera& camera,
	float translationSpeed) :

	mCamera(camera),
	mTranslationSpeed(translationSpeed)
{
	GLTUT_CHECK(mTranslationSpeed > 0.0F, "The translation speed must be positive");
	mCamera.getProjection().getWindow()->addEventHandler(this);
}

FPSCameraControllerC::~FPSCameraControllerC() noexcept
{
	mCamera.getProjection().getWindow()->removeEventHandler(this);
}

void FPSCameraControllerC::updateCamera(
	u64,
	u32 timeDeltaMs) noexcept
{
	Vector3 movement(
		static_cast<float>(right) - static_cast<float>(left),
		0.0f,
		static_cast<float>(front) - static_cast<float>(back));

	/*if (movement.isZero() && !mLeftMouseButtonPressed && !mMouseDrag)
	{
		return;
	}*/

	auto& camera = getCamera();
	auto& view = camera.getView();

	auto direction = view.getDirection();
	auto right = view.getRight();
	//if (mLeftMouseButtonPressed)
	//{
	//	//if (!mMouseDrag)
	//	{
	//		mStartMousePosition = mMousePosition;
	//		mInitialCameraDirection = direction;
	//		mMouseDrag = true;
	//	}
	//	else
	//	{
			const auto delta = mMousePosition - mStartMousePosition;
			const float yaw = -delta.x * mMouseSensitivity;
			const float pitch = std::clamp(delta.y * mMouseSensitivity, -89.0f, 89.0f);

			Matrix4 yawRotation = Matrix4::rotationMatrix(view.getUp() * toRadians(yaw));
			direction = yawRotation * mInitialCameraDirection;
			right = direction.cross(view.getUp()).normalize();

			Matrix4 pitchRotation = Matrix4::rotationMatrix(-right * toRadians(pitch));
			direction = pitchRotation * direction;
	/*	}
	}
	else
	{
		mMouseDrag = false;
	}*/

	if (!movement.isZero())
	{
		movement.normalize();
		movement *= mTranslationSpeed * (timeDeltaMs / 1000.0F);
		view.setPosition(view.getPosition() + movement.x * right + movement.z * direction);
	}
	view.setTarget(view.getPosition() + direction);
}

void FPSCameraControllerC::onEvent(const Event& event) noexcept
{
	switch (event.type)
	{
	case Event::Type::KEYBOARD:
	{
		// Using WASD keys for movement
		switch (event.keyboard.key)
		{
		case KeyCode::W:
			front = event.keyboard.pressedDown;
			break;

		case KeyCode::S:
			back = event.keyboard.pressedDown;
			break;

		case KeyCode::A:
			left = event.keyboard.pressedDown;
			break;

		case KeyCode::D:
			right = event.keyboard.pressedDown;
			break;

		default:
			break;
		}
	}
	break;

	case Event::Type::MOUSE:
	{
		mLeftMouseButtonPressed = event.mouse.buttons.left;
		mMousePosition = event.mouse.position;
		if (mFirstMouseMove)
		{
			mStartMousePosition = mMousePosition;
			mFirstMouseMove = false;
			mInitialCameraDirection = mCamera.getView().getDirection();
		}
	}
	break;

	default:
		break;
	}
}

//	Global functions
CameraController* createFPSCameraController(
	Camera& camera,
	float translationSpeed) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		return new FPSCameraControllerC(
			camera,
			translationSpeed);

	GLTUT_CATCH_ALL_END("Cannot create a FPS camera controller")
	return nullptr;
}

} // end namespace
