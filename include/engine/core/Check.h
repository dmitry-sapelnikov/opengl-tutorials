// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include <cassert>
#include <iostream>
#include <stdexcept>

// Macros
/// Assert if macro
#ifdef NDEBUG
#define GLTUT_ASSERT(condition) (condition)
#else
#define GLTUT_ASSERT(condition) (assert(condition), condition)
#endif

/// Assert that a string is not empty
inline void GLTUT_ASSERT_STRING(const char* string)
{
	string;
	assert(strlen(string) > 0);
}

// clang-format off

/// Check if condition is true, throw an exception with the message otherwise
#define GLTUT_CHECK(condition, message)\
if (!(condition))\
{\
	throw std::runtime_error(message);\
}

/// Assert for unexpected switch default case
#define GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(switchValue)\
default:\
	GLTUT_ASSERT(false && "Unexpected value of the switch variable: " #switchValue);\
	break;

/// Catch all begin macro. Equivalent to try {
#define GLTUT_CATCH_ALL_BEGIN \
try \
{

/// Catch all macro. Handles all exceptions, prints the message to std::cerr
#define GLTUT_CATCH_ALL(message)\
catch (std::exception& e)\
{\
	std::cerr << message << ": " << e.what() << std::endl;\
}\
catch (...)\
{\
	std::cerr << message << std::endl;\
}

/// Catch all end macro. Equivalent to GLTUT_CATCH_ALL with }
#define GLTUT_CATCH_ALL_END(message)\
}\
GLTUT_CATCH_ALL(message)

/// Catch all macro for application main function
#define GLTUT_APPLICATION_CATCH \
catch (const std::exception& e)\
{\
	std::cerr << "An ERROR occurred: " << e.what() << std::endl;\
	std::cin.get();\
	return 1;\
}\
catch (...)\
{\
	std::cerr << "An ERROR occurred" << std::endl;\
	std::cin.get();\
	return 1;\
}
// clang-format on
