// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "FPSCounter.h"

namespace gltut
{
// Global classes
void FPSCounter::reset()
{
	mStart = std::chrono::high_resolution_clock::now();
	mFrames = 0;
}

size_t FPSCounter::tick()
{
	++mFrames;
	const auto end = std::chrono::high_resolution_clock::now();
	const auto time_milliseconds =
		std::chrono::duration_cast<std::chrono::milliseconds>(end - mStart).count();

	if (time_milliseconds >= 1000)
	{
		auto result = (mFrames * 1000) / time_milliseconds;
		mStart = end;
		mFrames = 0;
		return result;
	}
	return 0;
}

// End of the namespace gltut
}
