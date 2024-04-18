#include <chrono>
#include <iostream>
#include <Windows.h>
#include <Gl/GL.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
		break;
	// Close on ESC key
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

// Define the function pointer type
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);

int main()
{
	// Register window class
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = L"OpenGLWindow";
	RegisterClass(&wc);

	// Create full-screen window
	HWND hwnd = CreateWindow(
		L"OpenGLWindow", L"OpenGL Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		nullptr, nullptr, GetModuleHandle(nullptr), nullptr);

	if (!hwnd)
		return 1;

	// Create OpenGL context
	HDC hdc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);
	HGLRC hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hglrc);

	// Call wglSwapIntervalEXT(0) to disable vertical synchronization
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
		(PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

	if (!wglSwapIntervalEXT) {
		// Function not supported
		std::cerr << "wglSwapIntervalEXT not supported" << std::endl;
		return -1;
	}

	wglSwapIntervalEXT(0);

	// Show the window
	ShowWindow(hwnd, SW_SHOW);

	glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

	// Main loop
	auto start = std::chrono::high_resolution_clock::now();
	unsigned long long frames = 0;

	while (true)
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;

		// Render your OpenGL content here
		glClear(GL_COLOR_BUFFER_BIT);

		SwapBuffers(hdc);
		++frames;
	}
	auto totalTime = (std::chrono::high_resolution_clock::now() - start).count();
	double totalFps = (frames * 1e9) / totalTime;

	// Cleanup
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(hglrc);
	ReleaseDC(hwnd, hdc);
	DestroyWindow(hwnd);

	std::cout << "Average FPS: " << totalFps << std::endl;
	std::cin.get();

	return 0;
}
