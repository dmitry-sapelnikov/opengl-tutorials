#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/scene/camera/Camera.h"

namespace gltut
{
// Global classes
/// A viewpoint that uses a camera to provide the position and matrices
class CameraViewpointC : public Viewpoint, public NonCopyable
{
public:
	/// Constructor
	explicit CameraViewpointC(const Camera* camera) noexcept :
		mCamera(camera)
	{
	}

	/// Returns the position of the camera
	Vector3 getPosition() const noexcept final
	{
		return mCamera != nullptr ?
			mCamera->getView().getPosition() :
			Vector3::zero();
	}

	/// Returns the view matrix
	Matrix4 getViewMatrix() const noexcept final
	{
		return mCamera != nullptr ?
			mCamera->getView().getMatrix() :
			Matrix4::identity();
	}

	/// Returns the projection matrix
	Matrix4 getProjectionMatrix(float aspectRatio) const noexcept final
	{
		return mCamera != nullptr ?
			mCamera->getProjection().getMatrix(aspectRatio) :
			Matrix4::identity();
	}

	/// Returns the camera
	const Camera* getCamera() const noexcept
	{
		return mCamera;
	}

	/// Sets the camera
	void setCamera(const Camera* camera) noexcept
	{
		mCamera = camera;
	}

private:
	/// The camera
	const Camera* mCamera;
};

// End of the namespace gltut
}
