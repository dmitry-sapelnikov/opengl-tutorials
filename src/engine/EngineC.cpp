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
EngineC::EngineC()
{
	if (glfwInit() != GLFW_TRUE)
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

EngineC::~EngineC() noexcept
{
	glfwTerminate();
}

Window* EngineC::createWindow(
	u32 width,
	u32 height,
	const char* title) noexcept
{
	if (mWindow.get() != nullptr)
	{
		std::cerr << "WindowC already created" << std::endl;
		return nullptr;
	}

	try
	{
		mWindow = std::make_unique<WindowC>(
			width,
			height,
			title,
			[this](u32 width, u32 height)
			{
				glViewport(0, 0, width, height);
				mScene->render();
			});

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "Failed to initialize GLAD" << std::endl;
			return nullptr;
		}

		mScene = std::make_unique<SceneC>();
		return mWindow.get();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

bool EngineC::update() noexcept
{
	if (mWindow.get() == nullptr)
	{
		std::cerr << "The window not created yet." << std::endl;
		return false;
	}

	mScene->render();
	mWindow->update();
	return !mWindow->shouldClose();
}

Scene* EngineC::getScene() noexcept
{
	return mScene.get();
}

// Global functions
Engine* createEngine() noexcept
{
	try
	{
		return new EngineC();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

// End of the namespace gltut
}
