#ifndef OPENGL_TUTORIALS_VECTOR3_H
#define OPENGL_TUTORIALS_VECTOR3_H

// Libraries
#include "engine/core/Check.h"
#include "engine/math/Functions.h"

namespace gltut
{
/// Represents a 3D vector.
struct Vector3
{
	// Components of the vector
	float x;
	float y;
	float z;

	// Constructor
	Vector3(
		float x = 0.f,
		float y = 0.f,
		float z = 0.f) noexcept :

		x(x),
		y(y),
		z(z)
	{
	}

	// Constructor
	Vector3(const Vector3& vector) noexcept :
		x(vector.x),
		y(vector.y),
		z(vector.z)
	{
	}

	// + operator
	Vector3 operator+(const Vector3& v) const noexcept
	{
		return { x + v.x, y + v.y, z + v.z };
	}

	// += operator
	Vector3& operator+=(const Vector3& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	// - operator
	Vector3 operator-(const Vector3& v) const noexcept
	{
		return { x - v.x, y - v.y, z - v.z };
	}

	// -= operator
	Vector3& operator-=(const Vector3& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	// *= operator
	Vector3& operator*=(float f) noexcept
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	// * operator
	Vector3 operator*(float f) const noexcept
	{
		return { f * x, f * y, f * z };
	}

	// / operator
	Vector3 operator/(float f) const noexcept
	{
		GLTUT_ASSERT(!isNearZero(f));
		return operator*(1.f / f);
	}

	// /= operator
	Vector3& operator/=(float f) noexcept
	{
		GLTUT_ASSERT(!isNearZero(f));
		return operator*=(1.f / f);
	}

	// - operator
	Vector3 operator-() const noexcept
	{
		return { -x, -y, -z };
	}

	// [] operator
	float& operator[](unsigned i) noexcept
	{
		GLTUT_ASSERT(i < 3);
		return (&x)[i];
	}

	// [] operator
	const float& operator[](unsigned i) const noexcept
	{
		GLTUT_ASSERT(i < 3);
		return (&x)[i];
	}

	// Cross product operator
	Vector3 cross(const Vector3& v) const noexcept
	{
		return {
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x };
	}

	// Dot product operator
	float dot(const Vector3& v) const noexcept
	{
		return x * v.x + y * v.y + z * v.z;
	}

	// Normalize the vector and return it
	Vector3& normalize() noexcept
	{
		return operator/=(length());
	}

	// Return the normalized vector
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

	//// Returns the length of the vector
	float length() const noexcept
	{
		return sqrt(lengthSquared());
	}

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

///	Returns the spherical coordinates of a vector in order (distance, azimuth, inclination)
inline Vector3 getSphericalCoordinates(const Vector3& v) noexcept
{
	const float distance = v.length();
	return isNearZero(distance) ?
		Vector3{ 0.f, 0.f, 0.f } :
		Vector3{ distance, std::atan2(v.y, v.x), std::acos(v.z / distance) };
}

// End of the namespace gltut
}

#endif
