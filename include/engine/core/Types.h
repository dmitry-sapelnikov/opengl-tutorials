#ifndef OPENGL_TUTORIALS_TYPES_H
#define OPENGL_TUTORIALS_TYPES_H

namespace gltut
{

using int32 = __int32;
static_assert(sizeof(int32) == 4, "The size of int32 is not 4 bytes");

using u32 = unsigned __int32;
static_assert(sizeof(u32) == 4, "The size of u32 is not 4 bytes");

static_assert(sizeof(float) == 4, "The size of float is not 4 bytes");

// End of the namespace gltut
}

#endif
