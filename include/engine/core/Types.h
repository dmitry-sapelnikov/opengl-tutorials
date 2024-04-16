#ifndef OPENGL_TUTORIALS_TYPES_H
#define OPENGL_TUTORIALS_TYPES_H

namespace gltut
{

// 32-bit integer
using int32 = __int32;
static_assert(sizeof(int32) == 4, "The size of int32 is not 4 bytes");

// 32-bit unsigned integer
using u32 = unsigned __int32;
static_assert(sizeof(u32) == 4, "The size of u32 is not 4 bytes");

// 32-bit float
static_assert(sizeof(float) == 4, "The size of float is not 4 bytes");

// End of the namespace gltut
}

#endif
