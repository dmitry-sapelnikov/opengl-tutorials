#ifndef OPENGL_TUTORIALS_ASSERT_H
#define OPENGL_TUTORIALS_ASSERT_H

// Includes
#include <cassert>

// Macros
/// Assert macro
#define GLTUT_ASSERT(condition) assert(condition)

#define GLTUT_CHECK(condition, message)\
if (!(condition))\
{\
	throw std::runtime_error(message);\
}

#endif
