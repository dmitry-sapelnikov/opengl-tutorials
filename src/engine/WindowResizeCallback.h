#ifndef OPENGL_TUTORIALS_WINDOW_RESIZE_CALLBACK_H
#define OPENGL_TUTORIALS_WINDOW_RESIZE_CALLBACK_H

// Includes
#include "engine/core/Types.h"

namespace gltut
{

/// Callback for the window resize event
class WindowResizeCallback
{
public:
	/// Virtual destructor
	virtual ~WindowResizeCallback() noexcept = default;

	/// Called when the window is resized
	virtual void onResize(u32 width, u32 height) noexcept = 0;
};

// End of the namespace gltut
}

#endif
