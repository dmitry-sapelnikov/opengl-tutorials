// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include <limits>

namespace gltut
{
// Constants
/// The value of pi
constexpr float PI = float(3.14159265358979323846);

/// The value of sqrt(2)
constexpr float SQRT2 = float(1.41421356237309504880);

/// Float epsilon
constexpr float FLOAT_EPSILON = std::numeric_limits<float>::epsilon();

// End of namespace gltut
}
