#ifndef OPENGL_TUTORIALS_FRAMEWORK_H
#define OPENGL_TUTORIALS_FRAMEWORK_H

// Forward declarations
struct GLFWwindow;

namespace gltut
{

/// Initialize and configure GLFW
bool initGLFW();

/// Creates a GLFW window
GLFWwindow* createWindow(
	unsigned width,
	unsigned height,
	const char* title);

/// Initializes GLAD
bool initGLAD();

/// Process user input
void processInput(GLFWwindow* window);

/// Shows FPS in the window title
void showFPS(
	GLFWwindow* window,
	const char* windowTitle,
	double& time,
	unsigned& frames);

// End of the namespace gltut
}

#endif
