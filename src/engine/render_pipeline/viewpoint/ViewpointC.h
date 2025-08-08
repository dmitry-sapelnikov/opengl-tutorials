#pragma once

// Includes
#include "engine/render_pipeline/viewpoint/Viewpoint.h"

namespace gltut
{
// Global classes
/// Basic implementation of the Viewpoint interface
class ViewpointC final : public Viewpoint
{
public:
	/// Default constructor
	ViewpointC() noexcept = default;

	/// Returns the point position
	Vector3 getPosition() const noexcept final
	{
		return mPosition;
	}

	/// Sets the point position
	void setPosition(const Vector3& position) noexcept
	{
		mPosition = position;
	}

	/// Returns the view matrix (inverse matrix of the viewer transformation)
	Matrix4 getViewMatrix() const noexcept final
	{
		return mViewMatrix;
	}

	/// Sets the view matrix
	void setViewMatrix(const Matrix4& viewMatrix) noexcept
	{
		mViewMatrix = viewMatrix;
	}

	/// Returns the projection matrix
	Matrix4 getProjectionMatrix(float aspectRatio) const noexcept final
	{
		return mProjectionMatrix;
	}

	/// Sets the projection matrix
	void setProjectionMatrix(const Matrix4& projectionMatrix) noexcept
	{
		mProjectionMatrix = projectionMatrix;
	}

private:
	/// The position of the viewpoint
	Vector3 mPosition = Vector3::zero();

	/// The view matrix of the viewpoint
	Matrix4 mViewMatrix = Matrix4::identity();

	/// The projection matrix of the viewpoint
	Matrix4 mProjectionMatrix = Matrix4::identity();
};

// End of the namespace gltut
}
