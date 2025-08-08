#pragma once

// Libraries
#include "engine/math/Vector2T.h"

namespace gltut
{
/// Represents a 2D point with integral components
/// Unsigned 32-bit point
using Point2u = Vector2T<u32>;

/// Signed 32-bit point
using Point2i = Vector2T<int32>;

// End of the namespace gltut
}
