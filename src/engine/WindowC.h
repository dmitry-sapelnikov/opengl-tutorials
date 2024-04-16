#ifndef OPENGL_TUTORIALS_WINDOW_C_H
#define OPENGL_TUTORIALS_WINDOW_C_H

// Includes
#include <string>
#include <functional>
#include "engine/Window.h"

struct GLFWwindow;

namespace gltut
{

class WindowC final : public Window
{
public:
	///	Resize callback
	using ResizeCallback = std::function<void(u32, u32)>;

	WindowC(
		u32 width,
		u32 height,
		ResizeCallback resizeCallback);

	/// Virtual destructor
	~WindowC() noexcept final;

	///	Sets the window title
	void setTitle(const char* title) noexcept final;

	/// Shows frames per second (FPS) in the window title
	void showFPS(bool show) noexcept final;

	/// Enables or disables vertical synchronization
	void enableVSync(bool vSync) noexcept final;

	///	Updates the window
	void update() noexcept;

	/// Returns if the window should close
	bool shouldClose() const noexcept;

private:
	friend void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	std::string mTitle;

	ResizeCallback mResizeCallback;

	bool mShowFPS = false;

	unsigned long mFrames = 0;

	double mTime = 0.0;

	GLFWwindow* mWindow = nullptr;
};

// End of the namespace gltut
}

#endif
