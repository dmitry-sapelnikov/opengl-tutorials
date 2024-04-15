// Includes
#include <string>
#include <functional>
#include "engine/IWindow.h"

struct GLFWwindow;

namespace gltut
{
class Window final : public IWindow
{
public:
	///	Resize callback
	using ResizeCallback = std::function<void(u32, u32)>;

	Window(
		u32 width,
		u32 height,
		const char* title,
		ResizeCallback resizeCallback);

	/// Virtual destructor
	~Window() noexcept final;

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
