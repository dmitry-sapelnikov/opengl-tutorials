//	Includes
#include "MouseCameraControllerC.h"
#include <algorithm>
#include "engine/core/Check.h"

namespace gltut
{
//	Global classes
MouseCameraControllerC::MouseCameraControllerC(
	Camera& camera,
	float mouseSpeed,
	float zoomSpeed,
	float targetMinDistance,
	float targetMaxDistance) :

	mCamera(camera),
	mMouseSpeed(mouseSpeed),
	mZoomSpeed(zoomSpeed),
	mTargetMinDistance(targetMinDistance),
	mTargetMaxDistance(targetMaxDistance)
{
	GLTUT_CHECK(mMouseSpeed > 0.0F, "The rotation speed must be positive");
	GLTUT_CHECK(mZoomSpeed > 0.0F, "The zoom speed must be positive");
	GLTUT_CHECK(mTargetMinDistance > 0.0F, "The minimum target distance must be positive");
	GLTUT_CHECK(mTargetMaxDistance > mTargetMinDistance, 
		"The maximum target distance must be greater than the minimum target distance");

	const auto& view = camera.getView();
	mPrevZoom = std::clamp(
		(view.getPosition() - view.getTarget()).length(),
		mTargetMinDistance,
		mTargetMaxDistance);

	mCurrentZoom = mPrevZoom;

	const Vector3 up = view.getUp();
	const Vector3 right = view.getRight();
	const Vector3 front = up.cross(right).normalize();

	mPitchYawBasis.setAxis(0, front);
	mPitchYawBasis.setAxis(1, right);
	mPitchYawBasis.setAxis(2, up);

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

	//	Zoom
	if (mPrevZoom != mCurrentZoom)
	{
		view.setPosition(view.getTarget() - view.getDirection() * mCurrentZoom);
		mPrevZoom = mCurrentZoom;
	}

	//	Rotation
	if (mMouseButtons.left)
	{
		if (!mRotating)
		{
			mMouseStart = mMousePosition;
			mRotating = true;
		}
		else
		{
			const Point2i mouseDelta = mMousePosition - mMouseStart;

			mYaw += mouseDelta.x * mMouseSpeed;

			// The pitch is inverted because the mouse Y-axis is inverted
			mPitch -= mouseDelta.y * mMouseSpeed;

			// Clamp the pitch to prevent the camera from flipping
			mPitch = std::clamp(mPitch, -89.0f, 89.0f);

			const Vector3 localDir = setDistanceAzimuthInclination(
				{ 1.0f, toRadians(mYaw), toRadians(mPitch) });

			const Vector3 direction = mPitchYawBasis * localDir;
			view.setPosition(view.getTarget() - direction * mCurrentZoom);

			mMouseStart = mMousePosition;
			return;
		}
	}
	else
	{
		mRotating = false;
	}

	//	Translation
	if (mMouseButtons.middle)
	{
		if (!mTranslating)
		{
			mMouseStart = mMousePosition;
			mTranslating = true;
			mInitialTarget = view.getTarget();
			mInitialPosition = view.getPosition();
			mProjectionViewInv = camera.getProjectionViewInverse();
			mWindowSize = camera.getProjection().getWindow()->getSize();
			mDragStart = screenToCameraRay(mMouseStart, mWindowSize, mInitialPosition, mProjectionViewInv);
		}
		else
		{
			const Vector3 currentDrag = screenToCameraRay(
				mMousePosition,
				mWindowSize,
				mInitialPosition,
				mProjectionViewInv);
			
			const Vector3 distance = mInitialTarget - mInitialPosition;
			const float proj = distance.dot(currentDrag);
			GLTUT_ASSERT(proj > 0.0F);
			const Vector3 deltaWorld = (distance.lengthSquared() / proj) * (mDragStart - currentDrag);
			view.setTarget(mInitialTarget + deltaWorld);
			view.setPosition(mInitialPosition + deltaWorld);
		}
		return;
	}
	else
	{
		mTranslating = false;
	}
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
	float targetMinDistance,
	float targetMaxDistance) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		return new MouseCameraControllerC(
			camera,
			rotationSpeed,
			zoomSpeed,
			targetMinDistance,
			targetMaxDistance);

	GLTUT_CATCH_ALL_END("Cannot create a mouse camera controller")
	return nullptr;
}

} // end namespace
