// Includes
#include "EngineC.h"

#include "WindowC.h"
#include "SceneC.h"
#include "RendererOpenGL.h"
#include <stdexcept>
#include <iostream>
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
		windowHeight);

	auto renderer = std::make_unique<RendererOpenGL>();

	//	First add the renderer as a resize callback, then add the engine
	mWindow->addResizeCallback(renderer.get());
	mWindow->addResizeCallback(this);

	mScene = std::make_unique<SceneC>(*mWindow , *renderer);
	mRenderer = std::move(renderer);
}

EngineC::~EngineC() noexcept
{
	mScene.reset();
	mRenderer.reset();
	mWindow.reset();
	glfwTerminate();
}

bool EngineC::update() noexcept
{
	mWindow->update();
	mRenderer->clear();
	mScene->render();
	return !mWindow->shouldClose();
}

Window* EngineC::getWindow() noexcept
{
	return mWindow.get();
}

Renderer* EngineC::getRenderer() noexcept
{
	return mRenderer.get();
}

Scene* EngineC::getScene() noexcept
{
	return mScene.get();
}

void EngineC::onResize(u32 width, u32 height) noexcept
{
	mScene->render();
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
