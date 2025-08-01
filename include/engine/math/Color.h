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
inline Vector3 toVector3(const Color& color) noexcept
{
	return { color.r, color.g, color.b };
}

// End of the namespace gltut
}
