// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/graphics/geometry/VertexFormat.h"

namespace gltut
{

/// The class represents a geometry to render
class Geometry
{
public:
	/// Virtual destructor
	virtual ~Geometry() noexcept = default;

	/// Renders the geometry
	virtual void render() const noexcept = 0;
};

// End of the namespace gltut
}
