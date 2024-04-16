#ifndef OPENGL_TUTORIALS_ASSERT_H
#define OPENGL_TUTORIALS_ASSERT_H

// Includes
#include <cassert>

// Macros
/// Assert macro
#define GLTUT_ASSERT(condition) assert(condition)

/// Assert that a string is not empty
inline void GLTUT_ASSERT_STRING(const char* string)
{
	assert(strlen(string) > 0);
}

#define GLTUT_CHECK(condition, message)\
if (!(condition))\
{\
	throw std::runtime_error(message);\
}

#endif
