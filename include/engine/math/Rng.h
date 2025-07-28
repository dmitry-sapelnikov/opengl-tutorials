#pragma once

//	Includes
#include <random>
#include "engine/core/Check.h"
#include "engine/core/Types.h"

namespace gltut
{
// Global classes
///	 Represents a random-number generator with the uniform distribution
class Rng
{
public:
	/// Constructor
	explicit Rng(u32 seed = 0) :
		// Increase the seed by 1 since mt19937 cannot work with zero seed
		mImplementation(seed + 1)
	{
	}

	/// Generates a random u32 value
	u32 nextUnsigned() noexcept
	{
		return mImplementation();
	}

	///	Generates a random float in the range [0, 1)
	float nextFloat() noexcept
	{
		return std::generate_canonical<float, std::numeric_limits<float>::digits>(
			mImplementation);
	}

	///	Generates a random float in the range [lowerLimit, upperLimit)
	float nextFloat(float lowerLimit, float upperLimit) noexcept
	{
		GLTUT_ASSERT(lowerLimit <= upperLimit);
		return std::lerp(lowerLimit, upperLimit, nextFloat());
	}

private:
	///	Implementation
	std::mt19937 mImplementation;
};

//	End of the namespace gltut
}
