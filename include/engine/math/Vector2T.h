// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/Check.h"
#include "engine/core/Types.h"
#include "engine/math/Functions.h"

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

	/// Operator *=
	Vector2T& operator*=(T f) noexcept
	{
		x *= f;
		y *= f;
		return *this;
	}

	/// Operator *
	Vector2T operator*(T f) const noexcept
	{
		return { f * x, f * y };
	}

	/// Checks if the point is zero
	bool isZero() const noexcept
	{
		return x == 0 && y == 0;
	}

	/// Returns the squared length of the vector
	T lengthSquared() const noexcept
	{
		return x * x + y * y;
	}

	//// Returns the length of the vector
	float length() const noexcept
	{
		return sqrt(lengthSquared());
	}

	// Normalize the vector and return it
	Vector2T& normalize() noexcept
	{
		return operator/=(length());
	}

	// Return the normalized vector
	Vector2T getNormalized() const noexcept
	{
		return *this / length();
	}

	// / operator
	Vector2T operator/(float f) const noexcept
	{
		GLTUT_ASSERT(!gltut::isNearZero(f));
		return operator*(1.f / f);
	}

	// /= operator
	Vector2T& operator/=(float f) noexcept
	{
		GLTUT_ASSERT(!gltut::isNearZero(f));
		return operator*=(1.f / f);
	}
};

// End of the namespace gltut
}
