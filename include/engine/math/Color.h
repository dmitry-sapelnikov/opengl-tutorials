// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/math/Vector3.h"

namespace gltut
{

// Global classes
/// Represents a color with red, green, blue and alpha components
struct Color
{
	/// Red component
	float r = 0.0f;
	/// Green component
	float g = 0.0f;
	/// Blue component
	float b = 0.0f;
	/// Alpha component
	float a = 1.0f;

	/// Default constructor
	Color() noexcept = default;

	/// Constructor with parameters
	constexpr Color(
		float red,
		float green,
		float blue,
		float alpha = 1.0f) noexcept :

		r(red),
		g(green),
		b(blue),
		a(alpha)
	{
	}
};

// Global functions
/// Converts a Color to a Vector3 (drops the alpha component)
inline Vector3 toVector3(const Color& color) noexcept
{
	return {color.r, color.g, color.b};
}

// End of the namespace gltut
}
