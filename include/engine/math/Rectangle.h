// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/math/Aabb.h"
#include "engine/math/Point2.h"

namespace gltut
{
// Global classes
/// Represents a 2D rectangle with unsigned integral coordinates
using Rectangle2u = AABB<2, Point2u>;

/// Represents a 2D rectangle with signed integral coordinates
using Rectangle2i = AABB<2, Point2i>;

// End of the namespace gltut
}
