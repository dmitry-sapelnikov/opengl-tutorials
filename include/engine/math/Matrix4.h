// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/Math/Matrix3.h"

namespace gltut
{
// Global classes
/// Represents a 4x4 matrix in column-major order, i.e. m[column][row]
class Matrix4
{
public:
	// Constructor
	constexpr Matrix4(
		float m00 = 0, float m01 = 0, float m02 = 0, float m03 = 0,
		float m10 = 0, float m11 = 0, float m12 = 0, float m13 = 0,
		float m20 = 0, float m21 = 0, float m22 = 0, float m23 = 0,
		float m30 = 0, float m31 = 0, float m32 = 0, float m33 = 0) noexcept
	{
		// The 1st row
		m[0][0] = m00;
		m[1][0] = m01;
		m[2][0] = m02;
		m[3][0] = m03;

		// The 2nd row
		m[0][1] = m10;
		m[1][1] = m11;
		m[2][1] = m12;
		m[3][1] = m13;

		// The 3rd row
		m[0][2] = m20;
		m[1][2] = m21;
		m[2][2] = m22;
		m[3][2] = m23;

		// The 4th row
		m[0][3] = m30;
		m[1][3] = m31;
		m[2][3] = m32;
		m[3][3] = m33;
	}

	/// Data constructor
	Matrix4(const float* data) noexcept
	{
		std::memcpy(m, data, 16 * sizeof(float));
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
					v += m[k][i] * n.m[j][k];
				}
				result.m[j][i] = v;
			}
		}
		return result;
	}

	/// Matrix-vector multiplication operator
	Vector3 operator*(const Vector3& v) const noexcept
	{
		Vector3 u(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0],
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1],
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2]);

		float w = m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3];
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

	// - operator
	Matrix4 operator-() const noexcept
	{
		return {
			-m[0][0], -m[1][0], -m[2][0], -m[3][0],
			-m[0][1], -m[1][1], -m[2][1], -m[3][1],
			-m[0][2], -m[1][2], -m[2][2], -m[3][2],
			-m[0][3], -m[1][3], -m[2][3], -m[3][3]};
	}

	/// Returns the transpose matrix
	Matrix4 getTranspose() const noexcept
	{
		return {
			m[0][0], m[0][1], m[0][2], m[0][3],
			m[1][0], m[1][1], m[1][2], m[1][3],
			m[2][0], m[2][1], m[2][2], m[2][3],
			m[3][0], m[3][1], m[3][2], m[3][3]};
	}

	/// Returns the axis at the specified index
	Vector3 getAxis(u32 i) const noexcept
	{
		GLTUT_ASSERT(i < 3);
		const auto& col = m[i];
		return {col[0], col[1], col[2]};
	}

	/// Sets the axis at the specified index
	void setAxis(u32 i, const Vector3& v) noexcept
	{
		GLTUT_ASSERT(i < 3);
		auto& col = m[i];
		col[0] = v.x;
		col[1] = v.y;
		col[2] = v.z;
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
	float operator()(u32 row, u32 col) const noexcept
	{
		GLTUT_ASSERT(row < 4 && col < 4);
		return m[col][row];
	}

	/// Returns the element at the specified row and column
	float& operator()(u32 row, u32 col) noexcept
	{
		GLTUT_ASSERT(row < 4 && col < 4);
		return m[col][row];
	}

	Matrix4 getInverse() const;

	/// Checks if the matrix is near zero
	bool isNearZero() const noexcept
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (!gltut::isNearZero(m[i][j]))
				{
					return false;
				}
			}
		}
		return true;
	}

	/// Extracts the top-left 3x3 matrix
	Matrix3 getMatrix3() const noexcept
	{
		return {
			m[0][0], m[1][0], m[2][0],
			m[0][1], m[1][1], m[2][1],
			m[0][2], m[1][2], m[2][2]};
	}

	/// Extracts the translation component from the matrix
	Vector3 getTranslation() const noexcept
	{
		return {m[3][0], m[3][1], m[3][2]};
	}

	/// Returns the identity matrix
	static Matrix4 identity() noexcept;

	/// Returns a 4x4 translation matrix
	static Matrix4 translationMatrix(const Vector3& v) noexcept;

	/// Returns a 4x4 rotation matrix
	static Matrix4 rotationMatrix(const Vector3& axisAngle) noexcept;

	/// Returns a 4x4 scale matrix
	static Matrix4 scaleMatrix(const Vector3& s) noexcept;

	static Matrix4 transformMatrix(
		const Vector3& position,
		const Vector3& axisAngle = {0.0f, 0.0f, 0.0f},
		const Vector3& scale = {1.f, 1.f, 1.f}) noexcept;

	/// Returns a 4x4 look-at matrix
	static Matrix4 lookAtMatrix(
		const Vector3& position,
		const Vector3& target,
		const Vector3& up) noexcept;

	/// Returns a 4x4 perspective projection matrix
	static Matrix4 perspectiveProjectionMatrix(
		float fieldOfViewRadians,
		float aspectRatio,
		float nearDistance,
		float farDistance) noexcept;

	/// Returns a 4x4 orthographic projection matrix
	static Matrix4 orthographicProjectionMatrix(
		float width,
		float height,
		float nearDistance,
		float farDistance) noexcept;

private:
	/// The matrix data in column-major order
	float m[4][4];
};

// Inline methods
inline Matrix4 Matrix4::getInverse() const
{
	const auto& M = *this;

	float d =
		(M(0, 0) * M(1, 1) - M(0, 1) * M(1, 0)) * (M(2, 2) * M(3, 3) - M(2, 3) * M(3, 2)) -
		(M(0, 0) * M(1, 2) - M(0, 2) * M(1, 0)) * (M(2, 1) * M(3, 3) - M(2, 3) * M(3, 1)) +
		(M(0, 0) * M(1, 3) - M(0, 3) * M(1, 0)) * (M(2, 1) * M(3, 2) - M(2, 2) * M(3, 1)) +
		(M(0, 1) * M(1, 2) - M(0, 2) * M(1, 1)) * (M(2, 0) * M(3, 3) - M(2, 3) * M(3, 0)) -
		(M(0, 1) * M(1, 3) - M(0, 3) * M(1, 1)) * (M(2, 0) * M(3, 2) - M(2, 2) * M(3, 0)) +
		(M(0, 2) * M(1, 3) - M(0, 3) * M(1, 2)) * (M(2, 0) * M(3, 1) - M(2, 1) * M(3, 0));

	GLTUT_ASSERT(std::abs(d) >= FLOAT_EPSILON);

	d = 1.f / d;

	Matrix4 out;
	out(0, 0) = d * (M(1, 1) * (M(2, 2) * M(3, 3) - M(2, 3) * M(3, 2)) +
					 M(1, 2) * (M(2, 3) * M(3, 1) - M(2, 1) * M(3, 3)) +
					 M(1, 3) * (M(2, 1) * M(3, 2) - M(2, 2) * M(3, 1)));

	out(0, 1) = d * (M(2, 1) * (M(0, 2) * M(3, 3) - M(0, 3) * M(3, 2)) +
					 M(2, 2) * (M(0, 3) * M(3, 1) - M(0, 1) * M(3, 3)) +
					 M(2, 3) * (M(0, 1) * M(3, 2) - M(0, 2) * M(3, 1)));

	out(0, 2) = d * (M(3, 1) * (M(0, 2) * M(1, 3) - M(0, 3) * M(1, 2)) +
					 M(3, 2) * (M(0, 3) * M(1, 1) - M(0, 1) * M(1, 3)) +
					 M(3, 3) * (M(0, 1) * M(1, 2) - M(0, 2) * M(1, 1)));

	out(0, 3) = d * (M(0, 1) * (M(1, 3) * M(2, 2) - M(1, 2) * M(2, 3)) +
					 M(0, 2) * (M(1, 1) * M(2, 3) - M(1, 3) * M(2, 1)) +
					 M(0, 3) * (M(1, 2) * M(2, 1) - M(1, 1) * M(2, 2)));

	out(1, 0) = d * (M(1, 2) * (M(2, 0) * M(3, 3) - M(2, 3) * M(3, 0)) +
					 M(1, 3) * (M(2, 2) * M(3, 0) - M(2, 0) * M(3, 2)) +
					 M(1, 0) * (M(2, 3) * M(3, 2) - M(2, 2) * M(3, 3)));

	out(1, 1) = d * (M(2, 2) * (M(0, 0) * M(3, 3) - M(0, 3) * M(3, 0)) +
					 M(2, 3) * (M(0, 2) * M(3, 0) - M(0, 0) * M(3, 2)) +
					 M(2, 0) * (M(0, 3) * M(3, 2) - M(0, 2) * M(3, 3)));

	out(1, 2) = d * (M(3, 2) * (M(0, 0) * M(1, 3) - M(0, 3) * M(1, 0)) +
					 M(3, 3) * (M(0, 2) * M(1, 0) - M(0, 0) * M(1, 2)) +
					 M(3, 0) * (M(0, 3) * M(1, 2) - M(0, 2) * M(1, 3)));

	out(1, 3) = d * (M(0, 2) * (M(1, 3) * M(2, 0) - M(1, 0) * M(2, 3)) +
					 M(0, 3) * (M(1, 0) * M(2, 2) - M(1, 2) * M(2, 0)) +
					 M(0, 0) * (M(1, 2) * M(2, 3) - M(1, 3) * M(2, 2)));

	out(2, 0) = d * (M(1, 3) * (M(2, 0) * M(3, 1) - M(2, 1) * M(3, 0)) +
					 M(1, 0) * (M(2, 1) * M(3, 3) - M(2, 3) * M(3, 1)) +
					 M(1, 1) * (M(2, 3) * M(3, 0) - M(2, 0) * M(3, 3)));

	out(2, 1) = d * (M(2, 3) * (M(0, 0) * M(3, 1) - M(0, 1) * M(3, 0)) +
					 M(2, 0) * (M(0, 1) * M(3, 3) - M(0, 3) * M(3, 1)) +
					 M(2, 1) * (M(0, 3) * M(3, 0) - M(0, 0) * M(3, 3)));

	out(2, 2) = d * (M(3, 3) * (M(0, 0) * M(1, 1) - M(0, 1) * M(1, 0)) +
					 M(3, 0) * (M(0, 1) * M(1, 3) - M(0, 3) * M(1, 1)) +
					 M(3, 1) * (M(0, 3) * M(1, 0) - M(0, 0) * M(1, 3)));

	out(2, 3) = d * (M(0, 3) * (M(1, 1) * M(2, 0) - M(1, 0) * M(2, 1)) +
					 M(0, 0) * (M(1, 3) * M(2, 1) - M(1, 1) * M(2, 3)) +
					 M(0, 1) * (M(1, 0) * M(2, 3) - M(1, 3) * M(2, 0)));

	out(3, 0) = d * (M(1, 0) * (M(2, 2) * M(3, 1) - M(2, 1) * M(3, 2)) +
					 M(1, 1) * (M(2, 0) * M(3, 2) - M(2, 2) * M(3, 0)) +
					 M(1, 2) * (M(2, 1) * M(3, 0) - M(2, 0) * M(3, 1)));

	out(3, 1) = d * (M(2, 0) * (M(0, 2) * M(3, 1) - M(0, 1) * M(3, 2)) +
					 M(2, 1) * (M(0, 0) * M(3, 2) - M(0, 2) * M(3, 0)) +
					 M(2, 2) * (M(0, 1) * M(3, 0) - M(0, 0) * M(3, 1)));

	out(3, 2) = d * (M(3, 0) * (M(0, 2) * M(1, 1) - M(0, 1) * M(1, 2)) +
					 M(3, 1) * (M(0, 0) * M(1, 2) - M(0, 2) * M(1, 0)) +
					 M(3, 2) * (M(0, 1) * M(1, 0) - M(0, 0) * M(1, 1)));

	out(3, 3) = d * (M(0, 0) * (M(1, 1) * M(2, 2) - M(1, 2) * M(2, 1)) +
					 M(0, 1) * (M(1, 2) * M(2, 0) - M(1, 0) * M(2, 2)) +
					 M(0, 2) * (M(1, 0) * M(2, 1) - M(1, 1) * M(2, 0)));

	return out;
}

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
		0.f, 0.f, 0.f, 1.f};
}

/// Returns a 4x4 translation matrix
inline Matrix4 Matrix4::translationMatrix(const Vector3& v) noexcept
{
	return {
		1.f, 0.f, 0.f, v.x,
		0.f, 1.f, 0.f, v.y,
		0.f, 0.f, 1.f, v.z,
		0.f, 0.f, 0.f, 1.f};
}

/// Returns a 4x4 rotation matrix
inline Matrix4 Matrix4::rotationMatrix(const Vector3& axisAngle) noexcept
{
	const float angle = axisAngle.length();
	if (angle < std::numeric_limits<float>::epsilon())
	{
		return identity();
	}
	const Vector3 axis = axisAngle * (1.f / angle);

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
		1.f};
}

inline Matrix4 Matrix4::scaleMatrix(const Vector3& s) noexcept
{
	return {
		s.x, 0.f, 0.f, 0.f,
		0.f, s.y, 0.f, 0.f,
		0.f, 0.f, s.z, 0.f,
		0.f, 0.f, 0.f, 1.f};
}

inline Matrix4 Matrix4::transformMatrix(
	const Vector3& position,
	const Vector3& axisAngle,
	const Vector3& scale) noexcept
{
	return translationMatrix(position) *
		   rotationMatrix(axisAngle) *
		   scaleMatrix(scale);
}

inline Matrix4 Matrix4::lookAtMatrix(
	const Vector3& position,
	const Vector3& target,
	const Vector3& up) noexcept
{
	// Row-major gluLookAt
	const Vector3 f = (target - position).normalize();
	const Vector3 s = f.cross(up).normalize();
	const Vector3 u = s.cross(f);
	return {
		s.x, s.y, s.z, -s.dot(position),
		u.x, u.y, u.z, -u.dot(position),
		-f.x, -f.y, -f.z, f.dot(position),
		0.f, 0.f, 0.f, 1.f};
}

inline Matrix4 Matrix4::perspectiveProjectionMatrix(
	float fieldOfViewRadians,
	float aspectRatio,
	float nearDistance,
	float farDistance) noexcept
{
	GLTUT_ASSERT(fieldOfViewRadians > FLOAT_EPSILON);
	GLTUT_ASSERT(aspectRatio > FLOAT_EPSILON);
	GLTUT_ASSERT(nearDistance > FLOAT_EPSILON);
	GLTUT_ASSERT(farDistance > nearDistance);

	const float top = nearDistance * std::tan(fieldOfViewRadians / 2.0f);
	const float bottom = -top;
	const float left = bottom * aspectRatio;
	const float right = top * aspectRatio;

	const float fx = 2.f * nearDistance / (right - left);
	const float fy = 2.f * nearDistance / (top - bottom);
	const float fz = -(farDistance + nearDistance) / (farDistance - nearDistance);
	const float fw = -2.f * farDistance * nearDistance / (farDistance - nearDistance);

	// Compute the projection matrix
	return {
		fx, 0.f, 0.f, 0.f,
		0.f, fy, 0.f, 0.f,
		0.f, 0.f, fz, fw,
		0.f, 0.f, -1.f, 0.f};
}

inline Matrix4 Matrix4::orthographicProjectionMatrix(
	float width,
	float height,
	float nearDistance,
	float farDistance) noexcept
{
	GLTUT_ASSERT(width > FLOAT_EPSILON);
	GLTUT_ASSERT(height > FLOAT_EPSILON);
	GLTUT_ASSERT(nearDistance > FLOAT_EPSILON);
	GLTUT_ASSERT(farDistance > nearDistance);

	const float fx = 2.f / width;
	const float fy = 2.f / height;
	const float fz = -2.f / (farDistance - nearDistance);
	const float fw = -(farDistance + nearDistance) / (farDistance - nearDistance);

	// Compute the projection matrix
	return {
		fx, 0.f, 0.f, 0.f,
		0.f, fy, 0.f, 0.f,
		0.f, 0.f, fz, fw,
		0.f, 0.f, 0.f, 1.f};
}

// End of the namespace gltut
}
