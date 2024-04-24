// Includes
#include "WindowC.h"

#include <iostream>
#include <Windows.h>

#include "engine/core/Check.h"

namespace gltut
{

//	Local classes
class WindowCallback
{
public:
	WindowCallback(WindowC& window) noexcept
		: mWindow(window)
	{
	}

	/// The callback function for the window resize event
	void onResize(int width, int height) noexcept
	{
		GLTUT_ASSERT(width > 0);
		GLTUT_ASSERT(height > 0);

		u32 uWidth = static_cast<u32>(width);
		u32 uHeight = static_cast<u32>(height);

		for (auto callback : mWindow.mResizeCallbacks)
		{
			callback->onResize(uWidth, uHeight);
		}
	}

private:
	WindowC& mWindow;
};

namespace
{
//	Local constants
//	Window class name
constexpr const wchar_t* WINDOW_CLASS_NAME = L"OpenGLWindow";

// Local functions
/// Retrieves the WindowCallback object from the window handle
WindowCallback* getWindowCallback(HWND hwnd)
{
	return reinterpret_cast<WindowCallback*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
}

/// The window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		if (auto* callback = getWindowCallback(hwnd))
		{
			callback->onResize(LOWORD(lParam), HIWORD(lParam));
		}
		break;

	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

// End of the anonymous namespace
}

// Global classes
WindowC::WindowC(
	u32 width,
	u32 height) :

	mCallback(std::make_unique<WindowCallback>(*this))
{
	GLTUT_CHECK(width > 0, "Window width must be greater than 0");
	GLTUT_CHECK(height > 0, "Window height must be greater than 0");

	try
	{
		// Register window class
		WNDCLASS wc = {};
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.lpszClassName = WINDOW_CLASS_NAME;
		GLTUT_CHECK(RegisterClass(&wc), "Failed to register window class");

		// Create full-screen window
		mWindow = CreateWindow(
			WINDOW_CLASS_NAME,
			L"",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, width, height,
			nullptr, nullptr, GetModuleHandle(nullptr), nullptr);

		GLTUT_CHECK(mWindow != nullptr, "Failed to create window");

		// Set this object as the user data of the window
		SetWindowLongPtr((HWND)mWindow, GWLP_USERDATA, (LONG_PTR)mCallback.get());

		mDeviceContext = GetDC((HWND)mWindow);
		GLTUT_CHECK(mDeviceContext != nullptr, "Failed to get the device context");

		ShowWindow((HWND)mWindow, SW_SHOW);
	}
	catch (...)
	{
		cleanup();
		throw;
	}
}

WindowC::~WindowC() noexcept
{
	cleanup();
}

void WindowC::setTitle(const char* title) noexcept
{
	SetWindowTextA((HWND)mWindow, title);
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

void WindowC::getSize(u32& width, u32& height) const noexcept
{
	RECT rect = {};
	const bool result = GetClientRect((HWND)mWindow, &rect);
	GLTUT_ASSERT(result);

	int intWidth = rect.right - rect.left;
	int intHeight = rect.bottom - rect.top;

	GLTUT_ASSERT(intWidth > 0);
	GLTUT_ASSERT(intHeight > 0);
	width = static_cast<u32>(intWidth);
	height = static_cast<u32>(intHeight);
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

bool WindowC::update() noexcept
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	SwapBuffers((HDC)mDeviceContext);

	if (mFPSCounter != nullptr)
	{
		if (auto fps = mFPSCounter->tick())
		{
			setTitle((" [FPS: " + std::to_string(fps) + "]").c_str());
		}
	}

	return true;
}

void WindowC::cleanup() noexcept
{
	ReleaseDC((HWND)mWindow, (HDC)mDeviceContext);
	DestroyWindow((HWND)mWindow);
	UnregisterClass(WINDOW_CLASS_NAME, GetModuleHandle(nullptr));
}

// End of the namespace gltut
}
