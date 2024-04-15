// Includes
#include <iostream>
#include <string>
#include <framework/framework.h>
#include <framework/shaders.h>

namespace
{

// Local constants
// Window settings
const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;
const char* WINDOW_TITLE = "Hello Triangle";

// Vertex shader source code
const char* VERTEX_SHADER_SOURCE_CODE =
	"#version 330 core\n"
	"layout(location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos, 1.0);\n"
	"}";

// Fragment shader source code
const char* FRAGMENT_SHADER_SOURCE_CODE =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}";

// Local functions
/// Renders the scene
void render(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

	unsigned shaderProgram = gltut::createShaderProgram(
		VERTEX_SHADER_SOURCE_CODE,
		FRAGMENT_SHADER_SOURCE_CODE);

	if (!shaderProgram)
	{
		return -1;
	}

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	//	Create the vertex buffer object
	unsigned VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//	Create the vertex array object
	unsigned VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//	Define the vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	// Unbind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//	Create the element buffer object
	unsigned EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// The render loop initialization
	// Bind the shader program
	glUseProgram(shaderProgram);

	// Bind the vertex array object
	glBindVertexArray(VAO);

	// Set the background color
	glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

	// Set the resize callback
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Initialize the frame counter
	unsigned frames = 0;
	double time = glfwGetTime();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.0f);

	// The render loop
	while (!glfwWindowShouldClose(window))
	{
		gltut::processInput(window);
		render(window);
		gltut::showFPS(window, WINDOW_TITLE, time, frames);
	}

	// Clean up
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();

	return 0;
}
