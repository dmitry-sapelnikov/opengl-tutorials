#ifndef OPENGL_TUTORIALS_VECTOR3_H
#define OPENGL_TUTORIALS_VECTOR3_H

// Libraries
#include "engine/core/Check.h"
#include <cmath>

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
	Vector3(float x = 0.f, float y = 0.f, float z = 0.f)
		: x(x), y(y), z(z)
	{
	}

	// Constructor
	Vector3(const Vector3& vector) : x(vector.x),
		y(vector.y),
		z(vector.z)
	{
	}

	// + operator
	Vector3 operator+(const Vector3& v) const
	{
		return { x + v.x, y + v.y, z + v.z };
	}

	// += operator
	Vector3& operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	// - operator
	Vector3 operator-(const Vector3& v) const
	{
		return { x - v.x, y - v.y, z - v.z };
	}

	// -= operator
	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	// *= operator
	Vector3& operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	// * operator
	Vector3 operator*(float f) const
	{
		return { f * x, f * y, f * z };
	}

	// / operator
	Vector3 operator/(float f) const
	{
		GLTUT_ASSERT(f > std::numeric_limits<float>::epsilon());
		return operator*(1.f / f);
	}

	// /= operator
	Vector3& operator/=(float f)
	{
		GLTUT_ASSERT(f > std::numeric_limits<float>::epsilon());
		return operator*=(1.f / f);
	}

	// - operator
	Vector3 operator-() const
	{
		return { -x, -y, -z };
	}

	// [] operator
	float& operator[](unsigned i)
	{
		GLTUT_ASSERT(i < 3);
		return (&x)[i];
	}

	// [] operator
	const float& operator[](unsigned i) const
	{
		GLTUT_ASSERT(i < 3);
		return (&x)[i];
	}

	// Cross product operator
	Vector3 cross(const Vector3& v) const
	{
		return {
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x };
	}

	// Dot product operator
	float dot(const Vector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	// Normalize the vector and return it
	Vector3 normalize()
	{
		return *this / length();
	}

	bool isZero() const
	{
		return (x == 0.f && y == 0.f && z == 0.f);
	}

	/// Returns the squared length of the vector
	float lengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	//// Returns the length of the vector
	float length() const
	{
		return sqrt(lengthSquared());
	}

	static Vector3 zero() noexcept
	{
		return Vector3(0.f, 0.f, 0.f);
	}
};

/// Scalar-vector multiplication
inline Vector3 operator*(float s, const Vector3& v)
{
	return v * s;
}

// End of the namespace gltut
}

#endif
