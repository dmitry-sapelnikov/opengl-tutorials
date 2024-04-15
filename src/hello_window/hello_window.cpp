// Includes
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <framework/framework.h>

namespace
{

// Local constants
// Window settings
const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;
const char* WINDOW_TITLE = "Hello Window";

// Local functions
/// Renders the scene
void render(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}

/// Callback for the framebuffer size change
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	render(window);
}

// End of anonymous namespace
}

///	The program entry point
int main()
{
	if (!gltut::initGLFW())
	{
		return -1;
	}

	// glfw window creation
	GLFWwindow* window = gltut::createWindow(
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		WINDOW_TITLE);

	if (window == nullptr)
	{
		return -1;
	}

	if (!gltut::initGLAD())
	{
		return -1;
	}

	// Set the background color
	glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

	// Set the resize callback
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	unsigned frames = 0;
	double time = glfwGetTime();
	// The render loop
	while (!glfwWindowShouldClose(window))
	{
		gltut::processInput(window);
		render(window);
		gltut::showFPS(window, WINDOW_TITLE, time, frames);
	}

	// glfw: terminate, clearing all previously allocated GLFW resources
	glfwTerminate();
	return 0;
}
