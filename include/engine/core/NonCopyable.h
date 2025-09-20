// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

namespace gltut
{
// Global classes
/**
	The class provides
	non-copyable and non-movable properties to a derived class
	Inspired by boost::noncopyable
*/
class NonCopyable
{
public:
	///  Deleted copy constructor
	NonCopyable(const NonCopyable&) = delete;

	///  Deleted copy assignment operator
	void operator=(const NonCopyable&) = delete;

	/// Deleted move constructor
	NonCopyable(NonCopyable&& other) = delete;

	/// Deleted move operator
	NonCopyable& operator=(NonCopyable&& other) = delete;

protected:
	/// Default constructor
	NonCopyable() = default;

	/// Destructor
	~NonCopyable() = default;
};

// End of the namespace gltut
}
