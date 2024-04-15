// Includes
#include "Window.h"
#include "engine/core/Assert.h"
#include "GLFW/glfw3.h"

namespace gltut
{

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* engineWindow = static_cast<Window*>(
		glfwGetWindowUserPointer(window));

	if (engineWindow)
	{
		engineWindow->mResizeCallback(
			static_cast<u32>(width),
			static_cast<u32>(height));
		engineWindow->update();
	}
}

// Global classes
Window::Window(
	u32 width,
	u32 height,
	const char* title,
	ResizeCallback resizeCallback) :

	mResizeCallback(resizeCallback)
{
	GLTUT_ASSERT(width > 0);
	GLTUT_ASSERT(height > 0);
	GLTUT_ASSERT(title != nullptr);

	mTitle = title;

	mWindow = glfwCreateWindow(
		width,
		height,
		title,
		nullptr,
		nullptr);


	GLTUT_ASSERT(mWindow != nullptr);
	glfwMakeContextCurrent(mWindow);
	glfwSetWindowUserPointer(mWindow, this);
	enableVSync(false);

	// Set the resize callback
	glfwSetFramebufferSizeCallback(mWindow, framebufferSizeCallback);
}

Window::~Window() noexcept
{
	glfwDestroyWindow(mWindow);
}

void Window::showFPS(bool show) noexcept
{
	if (show == mShowFPS)
	{
		return;
	}

	mShowFPS = show;
	if (show)
	{
		mTime = glfwGetTime();
		mFrames = 0;
	}
}

void Window::enableVSync(bool vSync) noexcept
{
	glfwSwapInterval(vSync ? 1 : 0);
}

bool Window::shouldClose() const noexcept
{
	return glfwWindowShouldClose(mWindow) != 0;
}

void Window::update() noexcept
{
	GLTUT_ASSERT(!shouldClose());

	glfwPollEvents();
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, true);
		return;
	}

	glfwSwapBuffers(mWindow);
	if (mShowFPS)
	{
		++mFrames;
		const double currentTime = glfwGetTime();
		if (currentTime - mTime >= 1.0)
		{
			glfwSetWindowTitle(
				mWindow,
				(mTitle + " [FPS: " + std::to_string(mFrames) + "]").c_str());
			mFrames = 0;
			mTime = currentTime;
		}
	}
}

// End of the namespace gltut
}
