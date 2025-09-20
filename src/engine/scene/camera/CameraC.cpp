// Includes
#include "CameraC.h"

namespace gltut
{
// Global classes
CameraViewC::CameraViewC(
	const Vector3& position,
	const Vector3& target,
	const Vector3& up) :

	mPosition(position),
	mTarget(target),
	mUp(up)
{
	GLTUT_CHECK(!(mPosition - mTarget).isNearZero(), "The position and target must be different");
	GLTUT_CHECK(!mUp.isNearZero(), "The up vector must not be zero");
	update();
}

void CameraViewC::update() noexcept
{
	mMatrix = Matrix4::lookAtMatrix(mPosition, mTarget, mUp);
}

CameraProjectionC::CameraProjectionC(
	Window& window,
	float fov,
	float nearPlane,
	float farPlane,
	const float* aspectRatio) :

	mWindow(window),
	mFov(fov),
	mNearPlane(nearPlane),
	mFarPlane(farPlane)
{
	GLTUT_CHECK(fov > FLOAT_EPSILON, "The field of view must be greater than 0");
	GLTUT_CHECK(nearPlane > FLOAT_EPSILON, "The near plane must be greater than 0");
	GLTUT_CHECK(farPlane > nearPlane, "The far plane must be greater than the near plane");
	if (aspectRatio != nullptr)
	{
		GLTUT_CHECK(*aspectRatio > FLOAT_EPSILON, "The aspect ratio must be greater than 0");
	}
	setAspectRatio(aspectRatio);
}

CameraProjectionC::~CameraProjectionC() noexcept
{
	mWindow.removeEventHandler(this);
}

void CameraProjectionC::setAspectRatio(const float* aspectRatio) noexcept
{
	mWindow.removeEventHandler(this);

	if (aspectRatio != nullptr)
	{
		mAspectRatio = *aspectRatio;
	}
	else
	{
		mAspectRatio.reset();
		mWindow.addEventHandler(this);
	}
	update();
}

void CameraProjectionC::update() noexcept
{
	float aspectRatio = 0.0f;
	if (!mAspectRatio.has_value())
	{
		const Point2u size = mWindow.getSize();
		GLTUT_ASSERT(size.y != 0);
		aspectRatio = static_cast<float>(size.x) / static_cast<float>(size.y);
	}
	else
	{
		aspectRatio = *mAspectRatio;
	}

	mMatrix = getMatrix(aspectRatio);
}

Matrix4 CameraProjectionC::getMatrix(float aspectRatio) const noexcept
{
	return Matrix4::perspectiveProjectionMatrix(
		toRadians(mFov),
		aspectRatio,
		mNearPlane,
		mFarPlane);
}

// Global functions
Vector3 screenToCameraRay(
	const Point2i& screenPoint,
	const Point2u& windowSize,
	const Vector3& cameraPosition,
	const Matrix4& cameraProjectionViewInverse)
{
	GLTUT_ASSERT(windowSize.x != 0);
	GLTUT_ASSERT(windowSize.y != 0);

	// Convert the screen point to the normalized device coordinates (NDC)
	const Vector3 ndc(
		(2.0f * screenPoint.x) / windowSize.x - 1.0f,
		1.0f - (2.0f * screenPoint.y) / windowSize.y,
		1.0f);
	return cameraProjectionViewInverse * ndc - cameraPosition;
}

// End of the namespace gltut
}
