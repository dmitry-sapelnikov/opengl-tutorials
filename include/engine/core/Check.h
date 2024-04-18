#ifndef OPENGL_TUTORIALS_ASSERT_H
#define OPENGL_TUTORIALS_ASSERT_H

// Includes
#include <cassert>
#include <stdexcept>
#include <iostream>

// Macros
/// Assert macro
#define GLTUT_ASSERT(condition) assert(condition)

/// Assert that a string is not empty
inline void GLTUT_ASSERT_STRING(const char* string)
{
	string;
	assert(strlen(string) > 0);
}

#define GLTUT_CHECK(condition, message)\
if (!(condition))\
{\
	throw std::runtime_error(message);\
}

#define GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(switchValue)\
default:\
	GLTUT_ASSERT(false && "Unexpected value of the switch variable: " #switchValue);\
	break;


#define GLTUT_CATCH_ALL_BEGIN \
try\
{

#define GLTUT_CATCH_ALL_END(message)\
}\
catch (std::exception& e)\
{\
	std::cerr << message << ": " << e.what() << std::endl;\
}\
catch (...)\
{\
	std::cerr << message << std::endl;\
}\

#endif
