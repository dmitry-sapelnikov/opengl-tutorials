// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/Check.h"
#include "engine/core/Types.h"

namespace gltut
{
// Global classes
/// Represents a 2D Vector
template <typename T>
struct Vector2T
{
	/// Components of the vector
	T x = 0;
	T y = 0;

	/// Default constructor
	Vector2T() noexcept = default;

	/// Constructor
	constexpr Vector2T(T inX, T inY) noexcept :
		x(inX),
		y(inY)
	{
	}

	/// + operator
	Vector2T operator+(const Vector2T& v) const noexcept
	{
		return { x + v.x, y + v.y };
	}

	/// += operator
	Vector2T& operator+=(const Vector2T& v) noexcept
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	/// - operator
	Vector2T operator-(const Vector2T& v) const noexcept
	{
		return { x - v.x, y - v.y };
	}

	/// -= operator
	Vector2T& operator-=(const Vector2T& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	/// - operator
	Vector2T operator-() const noexcept
	{
		return { -x, -y };
	}

	/// operator []
	T& operator[](u32 i) noexcept
	{
		GLTUT_ASSERT(i < 2);
		return (&x)[i];
	}

	/// operator []
	const T& operator[](u32 i) const noexcept
	{
		GLTUT_ASSERT(i < 2);
		return (&x)[i];
	}

	/// Checks if the point is zero
	bool isZero() const noexcept
	{
		return x == 0 && y == 0;
	}
};

// End of the namespace gltut
}
