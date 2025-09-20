// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "Constants.h"
#include <algorithm>
#include <cmath>

namespace gltut
{
// Global functions
/// Returns if a float value is near zero
inline bool isNearZero(float value) noexcept
{
	return std::abs(value) <= FLOAT_EPSILON;
}

/// Converts degrees to radians
inline float toRadians(float degrees) noexcept
{
	return degrees * PI / 180.0f;
}

/// Converts radians to degrees
inline float toDegrees(float radians) noexcept
{
	return radians * 180.0f / PI;
}

/// Clamps a float value between min and max
inline float clamp(float value, float min, float max) noexcept
{
	return std::max(min, std::min(value, max));
}

// End of namespace gltut
}
