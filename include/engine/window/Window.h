#pragma once

// Includes
#include "engine/core/Types.h"
#include "engine/math/Point2.h"
#include "engine/window/EventHandler.h"

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
	virtual const Point2u& getSize() const noexcept = 0;

	/// Adds an event handler
	virtual void addEventHandler(EventHandler* handler) noexcept = 0;

	/// Removes an event handler. Does nothing if the handler is not found.
	virtual void removeEventHandler(EventHandler* handler) noexcept = 0;

	/// Returns the current cursor position
	virtual Point2i getCursorPosition() const noexcept = 0;

	/// Sets the cursor position
	virtual void setCursorPosition(const Point2i& position) noexcept = 0;

	/// Returns the device context for the window
	virtual void* getDeviceContext() const noexcept = 0;

private:
	friend class WindowCallback;
};

// End of the namespace gltut
}
