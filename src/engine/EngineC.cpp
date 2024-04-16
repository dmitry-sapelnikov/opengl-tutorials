// Includes
#include "EngineC.h"

#include "WindowC.h"
#include "SceneC.h"
#include <stdexcept>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gltut
{
// Global classes
EngineC::EngineC(u32 windowWidth, u32 windowHeight)
{
	if (glfwInit() != GLFW_TRUE)
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = std::make_unique<WindowC>(
		windowWidth,
		windowHeight,
		[this](u32 width, u32 height)
		{
			glViewport(0, 0, width, height);
			mScene->render();
		});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}

	mScene = std::make_unique<SceneC>();
}

EngineC::~EngineC() noexcept
{
	mScene.reset();
	mWindow.reset();
	glfwTerminate();
}

bool EngineC::update() noexcept
{
	mScene->render();
	mWindow->update();
	return !mWindow->shouldClose();
}

Window* EngineC::getWindow() noexcept
{
	return mWindow.get();
}

Scene* EngineC::getScene() noexcept
{
	return mScene.get();
}

// Global functions
Engine* createEngine(u32 windowWidth, u32 windowHeight) noexcept
{
	try
	{
		return new EngineC(windowWidth, windowHeight);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

// End of the namespace gltut
}
