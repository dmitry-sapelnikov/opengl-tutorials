// Includes
#include "WindowC.h"
#include "engine/core/Assert.h"
#include "GLFW/glfw3.h"

namespace gltut
{

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	WindowC* engineWindow = static_cast<WindowC*>(
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
WindowC::WindowC(
	u32 width,
	u32 height,
	ResizeCallback resizeCallback) :

	mResizeCallback(resizeCallback)
{
	GLTUT_ASSERT(width > 0);
	GLTUT_ASSERT(height > 0);
	GLTUT_ASSERT(title != nullptr);

	mWindow = glfwCreateWindow(
		width,
		height,
		"",
		nullptr,
		nullptr);

	GLTUT_ASSERT(mWindow != nullptr);
	glfwMakeContextCurrent(mWindow);
	glfwSetWindowUserPointer(mWindow, this);
	enableVSync(false);

	// Set the resize callback
	glfwSetFramebufferSizeCallback(mWindow, framebufferSizeCallback);
}

WindowC::~WindowC() noexcept
{
	glfwDestroyWindow(mWindow);
}

void WindowC::setTitle(const char* title) noexcept
{
	GLTUT_ASSERT(title != nullptr);
	mTitle = title;
	glfwSetWindowTitle(mWindow, title);
}

void WindowC::showFPS(bool show) noexcept
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

void WindowC::enableVSync(bool vSync) noexcept
{
	glfwSwapInterval(vSync ? 1 : 0);
}

bool WindowC::shouldClose() const noexcept
{
	return glfwWindowShouldClose(mWindow) != 0;
}

void WindowC::update() noexcept
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
