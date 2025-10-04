#pragma once

// Includes
#include <vector>

#include "engine/math/Vector2.h"

namespace gltut
{

struct Wave
{
	float amplitude;
	float period;
	float phase;
	gltut::Vector2 direction;

	Wave() noexcept :
		amplitude(0.0f),
		period(1.0f),
		phase(0.0f),
		direction(1.0f, 0.0f)
	{
	}

	Wave(
		float inAmplitude, 
		float inPeriod, 
		float inPhase, 
		const gltut::Vector2& inDirection) noexcept :
		amplitude(inAmplitude),
		period(inPeriod),
		phase(inPhase),
		direction(inDirection)
	{
		direction.normalize();
	}
};

}