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

	/// Sets the window title
	virtual void setTitle(const char* label) noexcept = 0;

	/// Shows frames per second (FPS) in the window title
	virtual void showFPS(bool show) noexcept = 0;

	/// Returns the size of the window in pixels
	virtual void getSize(u32& width, u32& height) const noexcept = 0;
};

// End of the namespace gltut
}

#endif
