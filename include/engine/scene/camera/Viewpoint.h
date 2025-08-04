#pragma once

// Includes
#include "engine/math/Matrix4.h"

namespace gltut
{
// Global classes
/// The class represents a scene viewpoint
class Viewpoint
{
public:
	/// Virtual destructor
	virtual ~Viewpoint() noexcept = default;

	/// Returns the point position
	virtual Vector3 getPosition() const noexcept = 0;

	/// Returns the view matrix (inverse matrix of the viewer transformation)
	virtual Matrix4 getViewMatrix() const noexcept = 0;

	/// Returns the projection matrix
	virtual Matrix4 getProjectionMatrix() const noexcept = 0;

	/// Returns the projection-view matrix
	Matrix4 getProjectionViewMatrix() const noexcept
	{
		return getProjectionMatrix() * getViewMatrix();
	}

	/// Returns the inverted projection-view matrix
	Matrix4 getProjectionViewInverseMatrix() const noexcept
	{
		return getProjectionViewMatrix().getInverse();
	}
};

// End of the namespace gltut
}
