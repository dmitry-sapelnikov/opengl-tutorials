// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

/// Libraries
#include "Vector2.h"
#include "engine/core/Check.h"
#include "engine/math/Functions.h"

namespace gltut
{
/// Represents a 3D vector.
/// \todo Make it a template class
struct Vector3
{
	/// Components of the vector
	float x;
	float y;
	float z;

	/// Default constructor
	constexpr Vector3() noexcept :
		x(0.f),
		y(0.f),
		z(0.f)
	{
	}

	/// Construct from a single value
	constexpr explicit Vector3(float value) noexcept :
		x(value),
		y(value),
		z(value)
	{
	}

	/// Construct from three values
	constexpr Vector3(
		float x,
		float y,
		float z) noexcept :

		x(x),
		y(y),
		z(z)
	{
	}

	/// Copy constructor
	Vector3(const Vector3& vector) noexcept :
		x(vector.x),
		y(vector.y),
		z(vector.z)
	{
	}

	/// + operator
	Vector3 operator+(const Vector3& v) const noexcept
	{
		return {x + v.x, y + v.y, z + v.z};
	}

	/// += operator
	Vector3& operator+=(const Vector3& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	/// - operator
	Vector3 operator-(const Vector3& v) const noexcept
	{
		return {x - v.x, y - v.y, z - v.z};
	}

	/// -= operator
	Vector3& operator-=(const Vector3& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	/// *= operator
	Vector3& operator*=(float f) noexcept
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	/// * operator
	Vector3 operator*(float f) const noexcept
	{
		return {f * x, f * y, f * z};
	}

	/// / operator
	Vector3 operator/(float f) const noexcept
	{
		GLTUT_ASSERT(!gltut::isNearZero(f));
		return operator*(1.f / f);
	}

	/// /= operator
	Vector3& operator/=(float f) noexcept
	{
		GLTUT_ASSERT(!gltut::isNearZero(f));
		return operator*=(1.f / f);
	}

	/// - operator
	Vector3 operator-() const noexcept
	{
		return {-x, -y, -z};
	}

	/// [] operator
	float& operator[](unsigned i) noexcept
	{
		GLTUT_ASSERT(i < 3);
		return (&x)[i];
	}

	/// [] operator
	const float& operator[](unsigned i) const noexcept
	{
		GLTUT_ASSERT(i < 3);
		return (&x)[i];
	}

	/// Cross product operator
	Vector3 cross(const Vector3& v) const noexcept
	{
		return {
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x};
	}

	/// Dot product operator
	float dot(const Vector3& v) const noexcept
	{
		return x * v.x + y * v.y + z * v.z;
	}

	/// Normalize the vector and return it
	Vector3& normalize() noexcept
	{
		return operator/=(length());
	}

	/// Return the normalized vector
	Vector3 getNormalized() const noexcept
	{
		return *this / length();
	}

	/// Returns if the vector is exactly zero
	bool isZero() const noexcept
	{
		return (x == 0.f && y == 0.f && z == 0.f);
	}

	/// Returns if the vector's length <= FLOAT_EPSILON
	bool isNearZero() const noexcept
	{
		return lengthSquared() <= FLOAT_EPSILON * FLOAT_EPSILON;
	}

	/// Returns the squared length of the vector
	float lengthSquared() const noexcept
	{
		return x * x + y * y + z * z;
	}

	/// Returns the length of the vector
	float length() const noexcept
	{
		return sqrt(lengthSquared());
	}

	/// Returns a zero vector
	static Vector3 zero() noexcept
	{
		return Vector3(0.f, 0.f, 0.f);
	}
};

/// Scalar-vector multiplication
inline Vector3 operator*(float s, const Vector3& v) noexcept
{
	return v * s;
}

/**
	\brief Returns the distance, azimuth, and inclination of the vector,
	the angles are in radians.
*/
inline Vector3 getDistanceAzimuthInclination(const Vector3& v) noexcept
{
	const float distance = v.length();
	return isNearZero(distance) ? 
		Vector3(0.f, 0.f, 0.f) :
		Vector3(distance, std::atan2(v.y, v.x), std::asin(v.z / distance));
}

/**
	\brief Sets the distance, azimuth, and inclination to a vector,
	the angles are in radians.
*/
inline Vector3 setDistanceAzimuthInclination(const Vector3& dai) noexcept
{
	const float d = dai.x;
	const float cosInclination = std::cos(dai.z);
	return Vector3 {
		d * std::cos(dai.y) * cosInclination,
		d * std::sin(dai.y) * cosInclination,
		d * std::sin(dai.z)};
}

/**
	\brief Computes the tangent and bitangent vectors for the triangle
	defined by the three vertices and their texture coordinates.
	\param v1 The first vertex position
	\param v2 The second vertex position
	\param v3 The third vertex position
	\param uv1 The first vertex texture coordinate
	\param uv2 The second vertex texture coordinate
	\param uv3 The third vertex texture coordinate

	\param[out] tangent The computed tangent vector
	\param[out] bitangent The computed bitangent vector
*/
inline void getTangentSpace(
	const Vector3& v1,
	const Vector3& v2,
	const Vector3& v3,
	const Vector2& uv1,
	const Vector2& uv2,
	const Vector2& uv3,
	Vector3& tangent,
	Vector3& bitangent) noexcept
{
	const Vector3 deltaPos1 = v2 - v1;
	const Vector3 deltaPos2 = v3 - v1;
	const Vector2 deltaUV1 = uv2 - uv1;
	const Vector2 deltaUV2 = uv3 - uv1;
	const float r = 1.f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
	tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
	bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

	GLTUT_ASSERT(!tangent.isNearZero());
	GLTUT_ASSERT(!bitangent.isNearZero());
}

// End of the namespace gltut
}
