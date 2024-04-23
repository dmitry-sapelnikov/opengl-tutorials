// Includes
#include "WindowC.h"
#include <iostream>
#include "engine/core/Check.h"
#include "GLFW/glfw3.h"


namespace gltut
{
// Local functions
/// The callback function for the window resize event
static void framebufferSizeCallback(
	GLFWwindow* window,
	int width,
	int height)
{
	WindowC* engineWindow = static_cast<WindowC*>(
		glfwGetWindowUserPointer(window));

	u32 uWidth = static_cast<u32>(width);
	u32 uHeight = static_cast<u32>(height);
	if (engineWindow)
	{
		for (auto callback : engineWindow->mResizeCallbacks)
		{
			callback->onResize(uWidth, uHeight);
		}
		engineWindow->update();
	}
}

// Global classes
WindowC::WindowC(
	u32 width,
	u32 height)
{
	GLTUT_CHECK(width > 0, "Window width must be greater than 0");
	GLTUT_CHECK(height > 0, "Window height must be greater than 0");

	mWindow = glfwCreateWindow(
		width,
		height,
		"",
		nullptr,
		nullptr);

	GLTUT_CHECK(mWindow != nullptr, "Failed to create GLFW window");
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
	if (show)
	{
		if (mFPSCounter == nullptr)
		{
			GLTUT_CATCH_ALL_BEGIN
			mFPSCounter = std::make_unique<FPSCounter>();
			GLTUT_CATCH_ALL_END("Failed to show FPS")
		}
	}
	else
	{
		mFPSCounter.reset();
	}
	
}

void WindowC::enableVSync(bool vSync) noexcept
{
	glfwSwapInterval(vSync ? 1 : 0);
}

void WindowC::getSize(u32& width, u32& height) const noexcept
{
	int intWidth = 0;
	int intHeight = 0;
	glfwGetFramebufferSize(mWindow, &intWidth, &intHeight);
	GLTUT_ASSERT(intWidth > 0);
	GLTUT_ASSERT(intHeight > 0);
	width = static_cast<u32>(intWidth);
	height = static_cast<u32>(intHeight);
}

bool WindowC::shouldClose() const noexcept
{
	return glfwWindowShouldClose(mWindow) != 0;
}

void WindowC::addResizeCallback(WindowResizeCallback* callback) noexcept
{
	GLTUT_ASSERT(callback != nullptr);
	GLTUT_ASSERT(std::find(
		mResizeCallbacks.begin(),
		mResizeCallbacks.end(),
		callback) == mResizeCallbacks.end());

	GLTUT_CATCH_ALL_BEGIN
		mResizeCallbacks.push_back(callback);
	GLTUT_CATCH_ALL_END("Failed to add a resize callback")
}

void WindowC::removeResizeCallback(WindowResizeCallback* callback) noexcept
{
	auto findResult = std::find(
		mResizeCallbacks.begin(),
		mResizeCallbacks.end(),
		callback);

	if (findResult != mResizeCallbacks.end())
	{
		mResizeCallbacks.erase(findResult);
	}
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
	if (mFPSCounter != nullptr)
	{
		if (auto fps = mFPSCounter->tick())
		{
			glfwSetWindowTitle(
				mWindow,
				(mTitle + " [FPS: " + std::to_string(fps) + "]").c_str());
		}
	}
}

// End of the namespace gltut
}
