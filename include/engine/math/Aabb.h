#pragma once

// Includes
#include "engine/core/Check.h"

namespace gltut
{
// Global classes
/**
	\brief Represents an axis-aligned bounding box (AABB)
	\tparam D The number of space dimensions
	\tparam PointType The point type,
	must support operator[] and arithmetic operations
*/
template <u32 D, typename PointType>
class AABB
{
public:
	/// Default constructor
	AABB() noexcept = default;

	/*
		\brief 1-point constructor.
		Assigns a point to both min and max
	*/
	explicit AABB(const PointType& minMax) noexcept :
		mMin(minMax),
		mMax(minMax)
	{
	}

	/**
		\brief 2-points constructor.
		Creates an empty AABB if the points are invalid.
	*/
	AABB(
		const PointType& min,
		const PointType& max) noexcept
	{
		if (isValid(min, max))
		{
			mMin = min;
			mMax = max;
		}
	}

	/// Sets the min point. Does nothing if the result is invalid.
	void setMin(const PointType& min)
	{
		if (isValid(min, mMax))
		{
			mMin = min;
		}
	}

	/// Sets the max point. Does nothing if the result is invalid.
	void setMax(const PointType& max)
	{
		if (isValid(mMin, max))
		{
			mMax = max;
		}
	}

	/// Returns the min point
	const PointType& getMin() const noexcept
	{
		return mMin;
	}

	/// Returns the max point
	const PointType& getMax() const noexcept
	{
		return mMax;
	}

	/// Returns the AABB size
	PointType getSize() const noexcept
	{
		return mMax - mMin;
	}

private:
	/// Checks if 2 points are valid for an AABB
	static bool isValid(const PointType& min, const PointType& max) noexcept
	{
		for (u32 i = 0; i < D; ++i)
		{
			if (min[i] > max[i])
			{
				return false;
			}
		}
		return true;
	}

	/// The min point
	PointType mMin;

	/// The max point
	PointType mMax;
};

// End of the namespace gltut
}
