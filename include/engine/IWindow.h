#ifndef OPENGL_TUTORIALS_IWINDOW_H
#define OPENGL_TUTORIALS_IWINDOW_H

// Includes
#include "Core/Types.h"

namespace gltut
{

class IWindow
{
public:
	/// Virtual destructor
	virtual ~IWindow() noexcept = default;

	/// Shows frames per second (FPS) in the window title
	virtual void showFPS(bool show) noexcept = 0;

	/// Enables or disables vertical synchronization
	virtual void enableVSync(bool vSync) noexcept = 0;
};

// End of the namespace gltut
}

#endif
