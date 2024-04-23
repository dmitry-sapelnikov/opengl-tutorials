#ifndef OPENGL_TUTORIALS_WINDOW_C_H
#define OPENGL_TUTORIALS_WINDOW_C_H

// Includes
#include <string>
#include <memory>
#include <functional>
#include "engine/core/NonCopyable.h"
#include "engine/Window.h"
#include "FPSCounter.h"
#include "WindowResizeCallback.h"

struct GLFWwindow;
class FPSCounter;

namespace gltut
{

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

	/// Enables or disables vertical synchronization
	void enableVSync(bool vSync) noexcept final;

	/// Returns the size of the window in pixels
	void getSize(u32& width, u32& height) const noexcept final;

	///	Updates the window
	void update() noexcept;

	/// Returns if the window should close
	bool shouldClose() const noexcept;

	/// Adds a resize callback
	void addResizeCallback(WindowResizeCallback* callback) noexcept;

	/// Removes a resize callback. Does nothing if the callback is not found
	void removeResizeCallback(WindowResizeCallback* callback) noexcept;

private:
	/// The callback function for the window resize event
	friend void framebufferSizeCallback(
		GLFWwindow* window,
		int width,
		int height);

	/// The GLFW window
	GLFWwindow* mWindow = nullptr;

	/// The window title
	std::string mTitle;

	/// Resize callbacks
	std::vector<WindowResizeCallback*> mResizeCallbacks;

	/// FPS counter
	std::unique_ptr<FPSCounter> mFPSCounter;
};

// End of the namespace gltut
}

#endif
