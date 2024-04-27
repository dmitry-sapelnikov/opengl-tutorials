//	Includes
#include "MouseCameraControllerC.h"

#include <algorithm>
#include "engine/core/Check.h"

namespace gltut
{

namespace
{
//	Local functions
///	Returns the rotation offset from a pixel offset
Vector3 getRotationOffset(const Point2i& pixelOffset)
{
	static constexpr float ROTATION_OFFSET_SCALE = 0.002F;
	return
	{
		static_cast<float>(pixelOffset.x) * ROTATION_OFFSET_SCALE,
		static_cast<float>(pixelOffset.y) * ROTATION_OFFSET_SCALE,
		0.0f
	};
}

// End of anonymous namespace
}

//	Global classes
MouseCameraControllerC::MouseCameraControllerC(
	Camera& camera,
	float rotationSpeed,
	float zoomSpeed,
	float translationSpeed,
	float targetMinDistance,
	float targetMaxDistance) :

	mCamera(camera),
	mRotationSpeed(rotationSpeed),
	mZoomSpeed(zoomSpeed),
	mTranslationSpeed(translationSpeed),
	mTargetMinDistance(targetMinDistance),
	mTargetMaxDistance(targetMaxDistance),
	mUpVector(camera.getView().getUp())
{
	GLTUT_CHECK(mRotationSpeed > 0.0F, "The rotation speed must be positive");
	GLTUT_CHECK(mZoomSpeed > 0.0F, "The zoom speed must be positive");
	GLTUT_CHECK(mTranslationSpeed > 0.0F, "The translation speed must be positive");
	GLTUT_CHECK(mTargetMinDistance > 0.0F, "The minimum target distance must be positive");
	GLTUT_CHECK(mTargetMaxDistance > mTargetMinDistance, 
		"The maximum target distance must be greater than the minimum target distance");

	const auto& view = camera.getView();
	mPosition = view.getPosition();
	mTarget = view.getTarget();

	const Vector3 spherical = getDistanceAzimuthInclination(mPosition - mTarget);
	mRotation = { spherical.y, spherical.z, 0.0F };
	mCurrentZoom = spherical.x;

	mCamera.getProjection().getWindow()->addEventHandler(this);
}

MouseCameraControllerC::~MouseCameraControllerC() noexcept
{
	mCamera.getProjection().getWindow()->removeEventHandler(this);
}

void MouseCameraControllerC::updateCamera(u64, u32) noexcept
{
	auto& camera = getCamera();
	auto& view = camera.getView();

	//	Rotation values
	Vector3 rotation = mRotation;

	//	Rotation 
	if (mMouseButtons.left)
	{
		if (!mRotating)
		{
			mRotateStart = mMousePosition;
			mRotating = true;
			rotation = mRotation;
		}
		else
		{
			const auto mouseDelta = mRotateStart - mMousePosition;
			rotation -= getRotationOffset(mouseDelta) * mRotationSpeed;
		}
	}
	else if (mRotating)
	{
		const auto mouseDelta = mRotateStart - mMousePosition;
		mRotation -= getRotationOffset(mouseDelta) * mRotationSpeed;
		rotation = mRotation;
		mRotating = false;
	}

	//	Translation
	if (mMouseButtons.middle)
	{
		if (!mTranslating)
		{
			mTranslateStart = mMousePosition;
			mTranslating = true;
			mOldTarget = mTarget;
		}
		else
		{
			const auto startPoint = screenToCameraRay(mTranslateStart, camera);
			const auto endPoint = screenToCameraRay(mMousePosition, camera);

			const Vector3 cameraDirection = mPosition - mTarget;

			const auto targetDelta =
				(startPoint - endPoint) *
				(cameraDirection.length() / camera.getProjection().getFarPlane()) *
				(mTranslationSpeed / 100.0F);

			mTarget = mOldTarget + targetDelta;
		}
	}
	else if (mTranslating)
	{
		mTranslating = false;
	}

	mPosition.x = mCurrentZoom + mTarget.x;
	mPosition.y = mTarget.y;
	mPosition.z = mTarget.z;

	const auto& viewMatrix = view.getMatrix();
	{
		Matrix4 rotation1 = Matrix4::rotationAboutPoint(viewMatrix.getAxis(1) * toRadians(rotation.y), mTarget);
		Matrix4 rotation2 = Matrix4::rotationAboutPoint(viewMatrix.getAxis(0) * toRadians(rotation.x), mTarget);
		mPosition = rotation2 * (rotation1 * mPosition);
	}

	// Correct a possible rotation error
	Vector3 up = mUpVector;
	{
		const Matrix4 rotation1 =
			Matrix4::rotationMatrix(viewMatrix.getAxis(1) * toRadians(-rotation.y));

		const Matrix4 rotation2 =
			Matrix4::rotationMatrix(viewMatrix.getAxis(0) * toRadians(-rotation.x + 180.0F));

		up = rotation2 * (rotation1 * up);
		up.normalize();
	}

	//	If the up and direction vectors are the same, correct the up vector
	Vector3 direction = mTarget - mPosition;
	direction.normalize();

	float projection = direction.dot(up);
	if ((projection > -1.0001F && projection < -0.9999F) ||
		(projection < 1.0001F && projection >  0.9999F))
	{
		up.x += 1.0F;
		up.normalize();
	}

	view.setUp(up);
	view.setTarget(mTarget);
	view.setPosition(mPosition);
}

void MouseCameraControllerC::onEvent(const Event& event) noexcept
{
	if (event.type != Event::Type::MOUSE)
	{
		return;
	}

	mMousePosition = event.mouse.position;
	mMouseButtons = event.mouse.buttons;

	if (event.mouse.type == Event::MouseEvent::Type::WHEEL)
	{
		mCurrentZoom *= std::pow(
			2.0f,
			-event.mouse.wheel * 0.25f * (mZoomSpeed / 100.0f));

		mCurrentZoom = std::clamp(
			mCurrentZoom,
			mTargetMinDistance,
			mTargetMaxDistance);
	}
}

//	Global functions
CameraController* createMouseCameraController(
	Camera& camera,
	float rotationSpeed,
	float zoomSpeed,
	float translationSpeed,
	float targetMinDistance,
	float targetMaxDistance) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		return new MouseCameraControllerC(
			camera,
			rotationSpeed,
			zoomSpeed,
			translationSpeed,
			targetMinDistance,
			targetMaxDistance);

	GLTUT_CATCH_ALL_END("Cannot create a mouse camera controller")
	return nullptr;
}

} // end namespace
