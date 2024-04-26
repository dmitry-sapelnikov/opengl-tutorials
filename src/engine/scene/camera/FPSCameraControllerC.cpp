//	Includes
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
	auto& camera = getCamera();
	auto& view = camera.getView();

	Vector3 movement(
		static_cast<float>(right) - static_cast<float>(left),
		0.0f,
		static_cast<float>(back) - static_cast<float>(front));

	if (movement.isZero())
	{
		return;
	}
	
	movement.normalize();
	movement *= mTranslationSpeed * (timeDeltaMs / 1000.0F);
	const auto newPosition = view.getPosition() + movement;
	const auto newTarget = view.getTarget() + movement;

	view.setPosition(newPosition);
	view.setTarget(newTarget);
}

void FPSCameraControllerC::onEvent(const Event& event) noexcept
{
	if (event.type == Event::Type::KEYBOARD)
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
