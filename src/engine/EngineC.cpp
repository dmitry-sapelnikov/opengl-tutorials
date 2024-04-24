// Includes
#include "EngineC.h"

#include "WindowC.h"
#include "SceneC.h"
#include "RendererOpenGL.h"
#include <stdexcept>
#include <iostream>

namespace gltut
{
// Global classes
EngineC::EngineC(u32 windowWidth, u32 windowHeight)
{
	mWindow = std::make_unique<WindowC>(
		windowWidth,
		windowHeight);

	auto renderer = std::make_unique<RendererOpenGL>(
		mWindow->getDeviceContext());

	//	First add the renderer as a handler, then the engine
	mWindow->addEventHandler(renderer.get());
	mWindow->addEventHandler(this);

	mScene = std::make_unique<SceneC>(*mWindow , *renderer);
	mRenderer = std::move(renderer);
}

EngineC::~EngineC() noexcept
{
}

bool EngineC::update() noexcept
{
	if (!mWindow->update())
	{
		return false;
	}
	mRenderer->clear();
	mScene->render();
	return true;
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

void EngineC::onEvent(const Event& event) noexcept
{
	if (event.type == Event::Type::WINDOW_RESIZE)
	{
		mScene->render();
	}
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
