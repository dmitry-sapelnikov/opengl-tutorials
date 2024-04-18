#ifndef OPENGL_TUTORIALS_MATRIX4_H
#define OPENGL_TUTORIALS_MATRIX4_H

// Includes
#include "Constants.h"
#include "Vector3.h"

namespace gltut
{
// Global classes
/// Represents a 4x4 matrix
class Matrix4
{
public:
	// Constructor
	Matrix4(
		float m00 = 0, float m01 = 0, float m02 = 0, float m03 = 0,
		float m10 = 0, float m11 = 0, float m12 = 0, float m13 = 0,
		float m20 = 0, float m21 = 0, float m22 = 0, float m23 = 0,
		float m30 = 0, float m31 = 0, float m32 = 0, float m33 = 0) noexcept
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}

	// += operator
	Matrix4& operator+=(const Matrix4& n) noexcept
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] += n.m[i][j];
			}
		}
		return *this;
	}

	// + operator
	Matrix4 operator+(const Matrix4& n) const noexcept
	{
		return Matrix4(*this) += n;
	}

	/// -= operator
	Matrix4& operator-=(const Matrix4& n) noexcept
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] -= n.m[i][j];
			}
		}
		return *this;
	}

	/// - operator
	Matrix4 operator-(const Matrix4& n) const noexcept
	{
		return Matrix4(*this) -= n;
	}

	/// Matrix multiplication operator
	Matrix4 operator*(const Matrix4& n) const noexcept
	{
		Matrix4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				float v = 0;
				for (int k = 0; k < 4; k++)
				{
					v += m[i][k] * n.m[k][j];
				}
				result.m[i][j] = v;
			}
		}
		return result;
	}

	/// Matrix-vector multiplication operator
	Vector3 operator*(const Vector3& v) const noexcept
	{
		Vector3 u(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]);

		float w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];
		return u / w;
	}

	/// *= operator
	Matrix4& operator*=(float f) noexcept
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] *= f;
			}
		}
		return *this;
	}

	/// * operator
	Matrix4 operator*(float f) const noexcept
	{
		return Matrix4(*this) *= f;
	}

	/// /= operator
	Matrix4& operator/=(float f) noexcept
	{
		GLTUT_ASSERT(f > std::numeric_limits<float>::epsilon());
		return operator*=(1.f / f);
	}

	/// /= operator
	Matrix4 operator/(float f) const noexcept
	{
		return Matrix4(*this) /= f;
	}

	// - operator
	Matrix4 operator-() const noexcept
	{
		return {
			-m[0][0], -m[0][1], -m[0][2], -m[0][3],
			-m[1][0], -m[1][1], -m[1][2], -m[1][3],
			-m[2][0], -m[2][1], -m[2][2], -m[2][3],
			-m[3][0], -m[3][1], -m[3][2], -m[3][3] };
	}

	/// Returns the transpose matrix
	Matrix4 getTranspose() const noexcept
	{
		return {
			m[0][0], m[1][0], m[2][0], m[3][0],
			m[0][1], m[1][1], m[2][1], m[3][1],
			m[0][2], m[1][2], m[2][2], m[3][2],
			m[0][3], m[1][3], m[2][3], m[3][3] };
	}

	/// Sets the matrix to the identity matrix
	Matrix4& setToIdentity() noexcept
	{
		return *this = identity();
	}

	/// Returns a pointer to the matrix data (non-const version)
	float* data() noexcept
	{
		return m[0];
	}

	/// Returns a pointer to the matrix data (const version)
	const float* data() const noexcept
	{
		return m[0];
	}

	/// Returns the element at the specified row and column
	float operator()(unsigned row, unsigned col) const noexcept
	{
		GLTUT_ASSERT(row < 4 && col < 4);
		return m[row][col];
	}

	/// Returns the identity matrix
	static Matrix4 identity() noexcept;

	/// Returns a 4x4 translation matrix
	static Matrix4 translationMatrix(const Vector3& v) noexcept;

	/// Returns a 4x4 rotation matrix
	static Matrix4 rotationMatrix(const Vector3& axis, float angle) noexcept;

	/// Returns a 4x4 perspective projection matrix
	static Matrix4 perspectiveProjectionMatrix(
		float near,
		float far,
		unsigned width,
		unsigned height,
		float fieldOfView) noexcept;

private:
	/// The matrix data
	float m[4][4];
};

// Global functions
// * operator
inline Matrix4 operator*(float f, const Matrix4& m) noexcept
{
	return m * f;
}

/// Returns the identity matrix
inline Matrix4 Matrix4::identity() noexcept
{
	return {
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f };
}

/// Returns a 4x4 translation matrix
inline Matrix4 Matrix4::translationMatrix(const Vector3& v) noexcept
{
	return {
		1.f, 0.f, 0.f, v.x,
		0.f, 1.f, 0.f, v.y,
		0.f, 0.f, 1.f, v.z,
		0.f, 0.f, 0.f, 1.f };
}

/// Returns a 4x4 rotation matrix
inline Matrix4 Matrix4::rotationMatrix(const Vector3& axis, float angle) noexcept
{
	const float sinA = std::sin(angle);
	const float cosA = std::cos(angle);
	return {
		cosA + (1.f - cosA) * axis.x * axis.x,
		(1.f - cosA) * axis.x * axis.y - axis.z * sinA,
		(1.f - cosA) * axis.x * axis.z + axis.y * sinA,
		0.f,

		(1.f - cosA) * axis.x * axis.y + axis.z * sinA,
		cosA + (1.f - cosA) * axis.y * axis.y,
		(1.f - cosA) * axis.y * axis.z - axis.x * sinA,
		0.f,

		(1.f - cosA) * axis.x * axis.z - axis.y * sinA,
		(1.f - cosA) * axis.y * axis.z + axis.x * sinA,
		cosA + (1.f - cosA) * axis.z * axis.z,
		0.f,

		0.f,
		0.f,
		0.f,
		1.f };
}

/// Returns a 4x4 perspective projection matrix
inline Matrix4 Matrix4::perspectiveProjectionMatrix(
	float nearDistance,
	float farDistance,
	unsigned width,
	unsigned height,
	float fieldOfView) noexcept
{
	// Compute the aspect ratio
	float aspect = float(width) / float(height);

	const float top = nearDistance * std::tan((fieldOfView / 2.f) * (PI / 180.f));
	const float bottom = -top;
	const float left = bottom * aspect;
	const float right = top * aspect;

	const float fx = 2.f * nearDistance / (right - left);
	const float fy = 2.f * nearDistance / (top - bottom);
	const float fz = -(farDistance + nearDistance) / (farDistance - nearDistance);
	const float fw = -2.f * farDistance * nearDistance / (farDistance - nearDistance);

	// Compute the projection matrix
	return {
		fx, 0.f, 0.f, 0.f,
		0.f, fy, 0.f, 0.f,
		0.f, 0.f, fz, fw,
		0.f, 0.f, -1.f, 0.f };
}

// End of the namespace gltut
}

#endif
