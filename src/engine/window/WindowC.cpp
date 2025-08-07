// Includes
#include "WindowC.h"

#include <iostream>
#include <Windows.h>

#include "engine/core/Check.h"

namespace gltut
{

#define CALL_WINAPI_WITH_ASSERT(apiCall) \
{\
	const auto apiCallResult = (apiCall);\
	GLTUT_ASSERT(apiCallResult);\
}

//	Local classes
class WindowCallback : public EventHandler
{
public:
	WindowCallback(WindowC& window) noexcept
		: mWindow(window)
	{
	}

	void onEvent(const Event& event) noexcept override
	{
		for (auto callback : mWindow.mEventHandlers)
		{
			callback->onEvent(event);
		}

		if (event.type == Event::Type::WINDOW_RESIZE)
		{
			mWindow.updateSize();
		}
	}

	void swapBuffers() noexcept
	{
		SwapBuffers((HDC)mWindow.mDeviceContext);
	}

private:
	WindowC& mWindow;
};

//	Local constants
//	Window class name
static constexpr const wchar_t* WINDOW_CLASS_NAME = L"OpenGLWindow";

// Local functions
/// Retrieves the WindowCallback object from the window handle
static WindowCallback* getWindowCallback(HWND hwnd)
{
	return reinterpret_cast<WindowCallback*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
}

/// The window procedure
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	{
		gltut::Event event;
		event.type = gltut::Event::Type::MOUSE;
		event.mouse.position = { LOWORD(lParam), HIWORD(lParam) };
		event.mouse.buttons.left = (wParam & MK_LBUTTON) != 0;
		event.mouse.buttons.right = (wParam & MK_RBUTTON) != 0;
		event.mouse.buttons.middle = (wParam & MK_MBUTTON) != 0;

		switch (message)
		{
		case WM_MOUSEMOVE:
			event.mouse.type = gltut::Event::MouseEvent::Type::MOVE;
			break;

		case WM_LBUTTONDOWN:
			event.mouse.type = gltut::Event::MouseEvent::Type::LEFT_BUTTON_DOWN;
			break;

		case WM_LBUTTONUP:
			event.mouse.type = gltut::Event::MouseEvent::Type::LEFT_BUTTON_UP;
			break;

		case WM_RBUTTONDOWN:
			event.mouse.type = gltut::Event::MouseEvent::Type::RIGHT_BUTTON_DOWN;
			break;

		case WM_RBUTTONUP:
			event.mouse.type = gltut::Event::MouseEvent::Type::RIGHT_BUTTON_UP;
			break;

		case WM_MBUTTONDOWN:
			event.mouse.type = gltut::Event::MouseEvent::Type::MIDDLE_BUTTON_DOWN;
			break;

		case WM_MBUTTONUP:
			event.mouse.type = gltut::Event::MouseEvent::Type::MIDDLE_BUTTON_UP;
			break;

		case WM_MOUSEWHEEL:
		{
			event.mouse.type = gltut::Event::MouseEvent::Type::WHEEL;
			/// Here is the fix for the mouse position when the mouse wheel is scrolled.
			POINT p = { 0, 0 };
			ClientToScreen(hWnd, &p);
			event.mouse.position -= { p.x, p.y };
			event.mouse.wheel = 
				static_cast<float>(static_cast<short>(HIWORD(wParam))) / 
				static_cast<float>(WHEEL_DELTA);
		}
		break;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(message)
		}

		getWindowCallback(hWnd)->onEvent(event);
	}
	break;

	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		BYTE allKeys[256];

		gltut::Event event;
		event.type = gltut::Event::Type::KEYBOARD;
		event.keyboard.key = (gltut::KeyCode)wParam;
		event.keyboard.pressedDown = (message == WM_KEYDOWN || message == WM_SYSKEYDOWN);

		const UINT MY_MAPVK_VSC_TO_VK_EX = 3; // MAPVK_VSC_TO_VK_EX should be in SDK according to MSDN, but isn't in mine.
		if (event.keyboard.key == gltut::KeyCode::SHIFT)
		{
			// this will fail on systems before windows NT/2000/XP, not sure _what_ will return there instead.
			event.keyboard.key = (gltut::KeyCode)MapVirtualKey(((lParam >> 16) & 255), MY_MAPVK_VSC_TO_VK_EX);
		}
		if (event.keyboard.key == gltut::KeyCode::CONTROL)
		{
			event.keyboard.key = (gltut::KeyCode)MapVirtualKey(((lParam >> 16) & 255), MY_MAPVK_VSC_TO_VK_EX);
			// some keyboards will just return LEFT for both - left and right keys. So also check extend bit.
			if (lParam & 0x1000000)
				event.keyboard.key = gltut::KeyCode::RCONTROL;
		}
		if (event.keyboard.key == gltut::KeyCode::MENU)
		{
			event.keyboard.key = (gltut::KeyCode)MapVirtualKey(((lParam >> 16) & 255), MY_MAPVK_VSC_TO_VK_EX);
			if (lParam & 0x1000000)
				event.keyboard.key = gltut::KeyCode::RMENU;
		}

		const bool getKeyboardResult = GetKeyboardState(allKeys);
		GLTUT_ASSERT(getKeyboardResult);

		event.keyboard.shift = ((allKeys[VK_SHIFT] & 0x80) != 0);
		event.keyboard.control = ((allKeys[VK_CONTROL] & 0x80) != 0);

		// allow composing characters like '@' with Alt Gr on non-US keyboards
		if ((allKeys[VK_MENU] & 0x80) != 0)
		{
			event.keyboard.control = false;
		}

		getWindowCallback(hWnd)->onEvent(event);
	}
	break;

	case WM_SIZE:
	{
		Event event;
		event.type = Event::Type::WINDOW_RESIZE;
		event.windowResize.size = { LOWORD(lParam), HIWORD(lParam) };
		auto* callback = getWindowCallback(hWnd);
		callback->onEvent(event);
		callback->swapBuffers();
	}
	break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Global classes
WindowC::WindowC(
	u32 width,
	u32 height) :

	mSize(width, height),
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

const Point2u& WindowC::getSize() const noexcept
{
	return mSize;
}

void WindowC::addEventHandler(EventHandler* handler) noexcept
{
	GLTUT_ASSERT(handler != nullptr);
	GLTUT_ASSERT(std::find(
		mEventHandlers.begin(),
		mEventHandlers.end(),
		handler) == mEventHandlers.end());

	GLTUT_CATCH_ALL_BEGIN
		mEventHandlers.push_back(handler);
	GLTUT_CATCH_ALL_END("Failed to add an event handler")
}

void WindowC::removeEventHandler(EventHandler* handler) noexcept
{
	auto findResult = std::find(
		mEventHandlers.begin(),
		mEventHandlers.end(),
		handler);

	if (findResult != mEventHandlers.end())
	{
		mEventHandlers.erase(findResult);
	}
}

Point2i WindowC::getCursorPosition() const noexcept
{
	POINT point;
	CALL_WINAPI_WITH_ASSERT(GetCursorPos(&point));
	CALL_WINAPI_WITH_ASSERT(ScreenToClient((HWND)mWindow, &point));
	return { point.x, point.y };
}

void WindowC::setCursorPosition(const Point2i& position) noexcept
{
	POINT point = { position.x, position.y };
	CALL_WINAPI_WITH_ASSERT(ClientToScreen((HWND)mWindow, &point));
	CALL_WINAPI_WITH_ASSERT(SetCursorPos(point.x, point.y));
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

	CALL_WINAPI_WITH_ASSERT(SwapBuffers((HDC)mDeviceContext));

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

void WindowC::updateSize() noexcept
{
	RECT rect = {};
	const bool result = GetClientRect((HWND)mWindow, &rect);
	GLTUT_ASSERT(result);

	int intWidth = rect.right - rect.left;
	int intHeight = rect.bottom - rect.top;

	GLTUT_ASSERT(intWidth > 0);
	GLTUT_ASSERT(intHeight > 0);
	mSize = { static_cast<u32>(intWidth), static_cast<u32>(intHeight) };
}

// End of the namespace gltut
}
