#ifndef OPENGL_TUTORIALS_WINDOW_H
#define OPENGL_TUTORIALS_WINDOW_H

// Includes
#include "engine/Core/Types.h"
#include "engine/Math/Point2.h"
#include "engine/EventHandler.h"

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
	virtual Point2u getSize() const noexcept = 0;

	/// Adds an event handler
	virtual void addEventHandler(EventHandler* handler) noexcept = 0;

	/// Removes an event handler. Does nothing if the handler is not found.
	virtual void removeEventHandler(EventHandler* handler) noexcept = 0;

	/// Returns the current cursor position
	virtual Point2i getCursorPosition() const noexcept = 0;

	/// Sets the cursor position
	virtual void setCursorPosition(const Point2i& position) noexcept = 0;
};

// End of the namespace gltut
}

#endif
