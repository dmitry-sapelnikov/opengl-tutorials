#pragma once

// Includes
#include <string>
#include <memory>
#include <functional>

#include "engine/core/NonCopyable.h"
#include "engine/window/Window.h"
#include "FPSCounter.h"

struct GLFWwindow;
class FPSCounter;

namespace gltut
{

///	Forward declarations
class WindowCallback;

/// Implementation of the Window class
class WindowC final : public Window, public NonCopyable
{
public:
	WindowC(u32 width, u32 height);

	/// Virtual destructor
	~WindowC() noexcept final;

	///	Sets the window title
	void setTitle(const char* title) noexcept final;

	/// Shows frames per second (FPS) in the window title
	void showFPS(bool show) noexcept final;

	/// Returns the size of the window in pixels
	Point2u getSize() const noexcept final;

	/// Adds an event handler
	void addEventHandler(EventHandler* handler) noexcept final;

	/// Removes an event handler. Does nothing if the handler is not found.
	void removeEventHandler(EventHandler* handler) noexcept final;

	/// Returns the current cursor position
	Point2i getCursorPosition() const noexcept final;

	/// Sets the cursor position
	void setCursorPosition(const Point2i& position) noexcept final;

	/**
		\brief Updates the window
		\return True if the window is still open, false if the window is closed
	*/
	bool update() noexcept;

	/// Returns the device context
	void* getDeviceContext() const noexcept
	{
		return mDeviceContext;
	}

private:
	/// WindowCallback is a friend class
	friend class WindowCallback;

	/// Cleans up the window resources
	void cleanup() noexcept;

	/// Updates the size of the window
	void updateSize() noexcept;

	/// The window
	void* mWindow = nullptr;

	/// The device context
	void* mDeviceContext = nullptr;

	/// Helper class to invoke callbacks
	std::unique_ptr<WindowCallback> mCallback;

	/// Event handlers
	std::vector<EventHandler*> mEventHandlers;

	/// FPS counter
	std::unique_ptr<FPSCounter> mFPSCounter;

	/// The size of the window
	Point2u mSize;
};

// End of the namespace gltut
}
