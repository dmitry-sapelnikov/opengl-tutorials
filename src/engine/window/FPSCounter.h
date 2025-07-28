#pragma once

// Includes
#include <chrono>

namespace gltut
{
// Global classes
/**
	Class for counting frames per second.
	To use it, create an instance of the class and call the tick() method
	at the end of each frame. If the method returns a value greater than 0,
	display it as the number of frames per second.
*/
class FPSCounter
{
public:
	/// Constructor
	FPSCounter()
	{
		reset();
	}

	/// Resets the counter
	void reset();

	/**
		\brief Updates the counter
		\return The number of frames per second if more than 1 second
		has passed since the last call, 0 otherwise
	*/
	size_t tick();

private:
	/// Start of the ~1-second time interval
	std::chrono::time_point<std::chrono::high_resolution_clock> mStart;

	/// Number of frames during the time interval
	size_t mFrames;
};

// End of the namespace gltut
}
