#ifndef OPENGL_TUTORIALS_POINT2_H
#define OPENGL_TUTORIALS_POINT2_H

// Libraries
#include "engine/core/Check.h"
#include "engine/core/Types.h"

namespace gltut
{
/// Represents a 2D point with integral components
template <typename T>
struct Point2
{
	static_assert(std::is_integral<T>::value, "T must be an integral type");

	/// Components of the point
	T x;
	T y;

	Point2() :
		x(0), y(0)
	{
	}

	/// Constructor
	Point2(T x, T y) :
		x(x),
		y(y)
	{
	}

	/// + operator
	Point2 operator+(const Point2& v) const
	{
		return { x + v.x, y + v.y };
	}

	/// += operator
	Point2& operator+=(const Point2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	/// - operator
	Point2 operator-(const Point2& v) const
	{
		return { x - v.x, y - v.y };
	}

	/// -= operator
	Point2& operator-=(const Point2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	/// - operator
	Point2 operator-() const
	{
		return { -x, -y };
	}
};

/// Unsigned 32-bit point
using Point2u = Point2<u32>;

/// Signed 32-bit point
using Point2i = Point2<int32>;

// End of the namespace gltut
}

#endif
