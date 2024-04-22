#ifndef OPENGL_TUTORIALS_MATH_ANGLES_H
#define OPENGL_TUTORIALS_MATH_ANGLES_H

// Includes
#include "Constants.h"

namespace gltut
{
// Global functions
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

// End of namespace gltut
}

#endif