#ifndef OPENGL_TUTORIALS_MATH_CONSTANTS_H
#define OPENGL_TUTORIALS_MATH_CONSTANTS_H

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

#endif