#ifndef OPENGL_TUTORIALS_TYPES_H
#define OPENGL_TUTORIALS_TYPES_H

namespace gltut
{

// 8-bit integer
using int8 = __int8;
static_assert(sizeof(int8) == 1, "The size of int8 is not 1 byte");

// 16-bit integer
using int16 = __int16;
static_assert(sizeof(int16) == 2, "The size of int16 is not 2 bytes");

// 32-bit integer
using int32 = __int32;
static_assert(sizeof(int32) == 4, "The size of int32 is not 4 bytes");

// 64-bit integer
using int64 = __int64;
static_assert(sizeof(int64) == 8, "The size of int64 is not 8 bytes");

// 8-bit unsigned integer
using u8 = unsigned __int8;
static_assert(sizeof(u8) == 1, "The size of u8 is not 1 byte");

// 16-bit unsigned integer
using u16 = unsigned __int16;
static_assert(sizeof(u16) == 2, "The size of u16 is not 2 bytes");

// 32-bit unsigned integer
using u32 = unsigned __int32;
static_assert(sizeof(u32) == 4, "The size of u32 is not 4 bytes");

// 64-bit unsigned integer
using u64 = unsigned __int64;
static_assert(sizeof(u64) == 8, "The size of u64 is not 8 bytes");

// 32-bit float
static_assert(sizeof(float) == 4, "The size of float is not 4 bytes");

// End of the namespace gltut
}

#endif
