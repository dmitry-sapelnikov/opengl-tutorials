#ifndef OPENGL_TUTORIALS_MATRIX3_H
#define OPENGL_TUTORIALS_MATRIX3_H

// Includes
#include "engine/Core/Types.h"
#include "engine/Math/Functions.h"
#include "engine/Math/Vector3.h"

namespace gltut
{
// Global classes
/// Represents a 3x3 matrix
class Matrix3
{
public:
	// Constructor
	Matrix3(
		float m00 = 0, float m01 = 0, float m02 = 0,
		float m10 = 0, float m11 = 0, float m12 = 0,
		float m20 = 0, float m21 = 0, float m22 = 0) noexcept
	{
		m[0][0] = m00; m[1][0] = m01; m[2][0] = m02;
		m[0][1] = m10; m[1][1] = m11; m[2][1] = m12;
		m[0][2] = m20; m[1][2] = m21; m[2][2] = m22;
	}

	// += operator
	Matrix3& operator+=(const Matrix3& n) noexcept
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m[i][j] += n.m[i][j];
			}
		}
		return *this;
	}

	// + operator
	Matrix3 operator+(const Matrix3& n) const noexcept
	{
		return Matrix3(*this) += n;
	}

	/// -= operator
	Matrix3& operator-=(const Matrix3& n) noexcept
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m[i][j] -= n.m[i][j];
			}
		}
		return *this;
	}

	/// - operator
	Matrix3 operator-(const Matrix3& n) const noexcept
	{
		return Matrix3(*this) -= n;
	}

	/// Matrix multiplication operator
	Matrix3 operator*(const Matrix3& n) const noexcept
	{
		Matrix3 result;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				float v = 0;
				for (int k = 0; k < 3; k++)
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
		return {
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z
		};
	}

	/// *= operator
	Matrix3& operator*=(float f) noexcept
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m[i][j] *= f;
			}
		}
		return *this;
	}

	/// * operator
	Matrix3 operator*(float f) const noexcept
	{
		return Matrix3(*this) *= f;
	}

	// - operator
	Matrix3 operator-() const noexcept
	{
		return {
			-m[0][0], -m[1][0], -m[2][0],
			-m[0][1], -m[1][1], -m[2][1],
			-m[0][2], -m[1][2], -m[2][2]
		};
	}

	/// Returns the transpose matrix
	Matrix3 getTranspose() const noexcept
	{
		return {
			m[0][0], m[0][1], m[0][2],
			m[1][0], m[1][1], m[1][2],
			m[2][0], m[2][1], m[2][2] };
	}

	/// Returns the axis at the specified index
	Vector3 getAxis(u32 i) const noexcept
	{
		GLTUT_ASSERT(i < 3);
		const auto& col = m[i];
		return { col[0], col[1], col[2] };
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
	Matrix3& setToIdentity() noexcept
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
		GLTUT_ASSERT(row < 3 && col < 3);
		return m[col][row];
	}

	/// Returns the element at the specified row and column
	float& operator()(u32 row, u32 col) noexcept
	{
		GLTUT_ASSERT(row < 3 && col < 3);
		return m[col][row];
	}

	/**
		\brief Returns the inverse of the matrix.
		Asserts if the matrix is invertible.
	*/
	Matrix3 getInverse() const;

	/// Returns if the matrix is near zero
	bool isNearZero() const noexcept
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (!gltut::isNearZero(m[i][j]))
				{
					return false;
				}
			}
		}
		return true;
	}

	/// Returns the identity matrix
	static Matrix3 identity() noexcept;

private:
	/// The matrix data in the column-major order
	float m[3][3];
};

//	Inline methods
inline Matrix3 Matrix3::getInverse() const
{
	// Determinant
	float d =
		m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
		m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) +
		m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1]);

	GLTUT_ASSERT(std::abs(d) >= FLOAT_EPSILON);

	// Inverse of the determinant
	d = 1.f / d;

	return {
		// 0th row
		(m[1][1] * m[2][2] - m[1][2] * m[2][1]) * d,
		(m[2][0] * m[1][2] - m[1][0] * m[2][2]) * d,
		(m[1][0] * m[2][1] - m[2][0] * m[1][1]) * d,

		// 1st row
		(m[2][1] * m[0][2] - m[0][1] * m[2][2]) * d,
		(m[0][0] * m[2][2] - m[2][0] * m[0][2]) * d,
		(m[0][1] * m[2][0] - m[0][0] * m[2][1]) * d,

		// 2nd row
		(m[0][1] * m[1][2] - m[0][2] * m[1][1]) * d,
		(m[0][2] * m[1][0] - m[0][0] * m[1][2]) * d,
		(m[0][0] * m[1][1] - m[0][1] * m[1][0]) * d
	};
}

// Global functions
// * operator
inline Matrix3 operator*(float f, const Matrix3& m) noexcept
{
	return m * f;
}

/// Returns the identity matrix
inline Matrix3 Matrix3::identity() noexcept
{
	return {
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f };
}

/// Returns the normal matrix for a rotation-scale matrix
inline Matrix3 getNormalMatrix(const Matrix3& rotationScale) noexcept
{
	return rotationScale.getInverse().getTranspose();
}

// End of the namespace gltut
}

#endif
