// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once
#include "engine/core/Types.h"
#include "engine/math/Matrix4.h"

namespace gltut
{
// Global classes
/// Represents a base class for render objects
class RenderObject
{
public:
	/// Virtual destructor
	virtual ~RenderObject() noexcept = default;

	/// Renders the object
	virtual void render(u32 materialPass) const noexcept = 0;
};

// End of the namespace gltut
}
