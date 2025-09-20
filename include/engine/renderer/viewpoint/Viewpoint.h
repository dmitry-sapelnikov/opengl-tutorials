// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/math/Matrix4.h"

namespace gltut
{
// Global classes
/// Represents a viewpoint in the renderer
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
	virtual Matrix4 getProjectionMatrix(float aspectRatio) const noexcept = 0;
};

// End of the namespace gltut
}
