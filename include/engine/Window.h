#ifndef OPENGL_TUTORIALS_WINDOW_H
#define OPENGL_TUTORIALS_WINDOW_H

// Includes
#include "Core/Types.h"

namespace gltut
{
// Global classes
class Window
{
public:
	/// Virtual destructor
	virtual ~Window() noexcept = default;

	/// Shows frames per second (FPS) in the window title
	virtual void showFPS(bool show) noexcept = 0;

	/// Enables or disables the vertical synchronization
	virtual void enableVSync(bool vSync) noexcept = 0;
};

// End of the namespace gltut
}

#endif
