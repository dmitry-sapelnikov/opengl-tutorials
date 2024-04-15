// Includes
#include <framework/framework.h>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gltut
{

// Global functions
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

GLFWwindow* createWindow(
	unsigned width,
	unsigned height,
	const char* title)
{
	GLFWwindow* window = glfwCreateWindow(
		width,
		height,
		title,
		nullptr,
		nullptr);

	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	//	Disable VSync
	glfwSwapInterval(0);
	return window;
}

bool initGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	return true;
}

void processInput(GLFWwindow* window)
{
	glfwPollEvents();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

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

// End of the namespace gltut
}
