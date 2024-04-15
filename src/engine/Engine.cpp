// Includes
#include "Engine.h"
#include <stdexcept>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gltut
{

Engine::Engine()
{
	if (glfwInit() != GLFW_TRUE)
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Engine::~Engine() noexcept
{
	glfwTerminate();
}

IWindow* Engine::createWindow(
	u32 width,
	u32 height,
	const char* title) noexcept
{
	if (mWindow.get() != nullptr)
	{
		std::cerr << "Window already created" << std::endl;
		return nullptr;
	}

	try
	{
		mWindow = std::make_unique<Window>(
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

		mScene = std::make_unique<Scene>();
		return mWindow.get();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

bool Engine::doStep() noexcept
{
	if (mWindow.get() == nullptr)
	{
		std::cerr << "Window not created" << std::endl;
		return false;
	}

	mScene->render();
	mWindow->update();
	return !mWindow->shouldClose();
}

IScene* Engine::getScene() noexcept
{
	return mScene.get();
}

// Global functions
IEngine* createEngine() noexcept
{
	try
	{
		return new Engine();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

// End of the namespace gltut
}
