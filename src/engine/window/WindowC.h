#pragma once

// Includes
#include <deque>
#include <functional>
#include <memory>
#include <string>

#include "engine/core/NonCopyable.h"
#include "engine/window/Window.h"

#include "../core/FPSCounter.h"

namespace gltut
{
// Global classes
/// Forward declarations
class WindowCallback;

/// Implementation of the Window class
class WindowC final : public Window, public NonCopyable
{
public:
	WindowC(u32 width, u32 height);

	/// Virtual destructor
	~WindowC() noexcept final;

	/// Sets the window title
	void setTitle(const char* title) noexcept final;

	/// Shows frames per second (FPS) in the window title
	void showFPS(bool show) noexcept final;

	/// Returns the size of the window in pixels
	const Point2u& getSize() const noexcept final;

	/// Returns the current frames per second (FPS)
	u32 getFPS() noexcept final;

	/// Adds an event handler
	void addEventHandler(EventHandler* handler, bool inFront = false) noexcept final;

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

	/// Returns the window handle
	void* getHandle() const noexcept final
	{
		return mWindow;
	}

	/// Returns the device context
	void* getDeviceContext() const noexcept final
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
	std::deque<EventHandler*> mEventHandlers;

	/// FPS counter
	FPSCounter mFPSCounter;

	/// The size of the window
	Point2u mSize;

	/// Show FPS flag
	bool mShowFPS = false;

	/// FPS
	u32 mFPS = 0;
};

// End of the namespace gltut
}
