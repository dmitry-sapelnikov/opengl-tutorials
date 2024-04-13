#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{

// Local constants
// Window settings
const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;
const char* WINDOW_TITLE = "Hello Window";

// Local functions
/// Renders the scene
void render(GLFWwindow* window)
{
	glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}

/// Callback for the framebuffer size change
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	render(window);
}

/// Process user input
void processInput(GLFWwindow* window)
{
	glfwPollEvents();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

/// Prints FPS in the window title
void showFPS(
	GLFWwindow* window,
	const char* windowTitle,
	double& time,
	unsigned& frames)
{
	++frames;
	const double current_time = glfwGetTime();
	if (current_time - time >= 1.0)
	{
		glfwSetWindowTitle(
			window,
			(std::string(windowTitle) + " [FPS: " + std::to_string(frames) + "]").c_str());
		frames = 0;
		time = current_time;
	}
}

/// Initialize and configure GLFW
bool initGLFW()
{
	if (glfwInit() != GLFW_TRUE)
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return true;
}

/// Creates a GLFW window
GLFWwindow* createWindow()
{
	GLFWwindow* window = glfwCreateWindow(
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		WINDOW_TITLE,
		nullptr,
		nullptr);

	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	return window;
}

// End of anonymous namespace
}

///	The program entry point
int main()
{
	if (!initGLFW())
	{
		return -1;
	}

	// glfw window creation
	GLFWwindow* window = createWindow();
	if (window == nullptr)
	{
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned frames = 0;
	double time = glfwGetTime();

	// The render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		render(window);
		showFPS(window, WINDOW_TITLE, time, frames);
	}

	// glfw: terminate, clearing all previously allocated GLFW resources
	glfwTerminate();
	return 0;
}
