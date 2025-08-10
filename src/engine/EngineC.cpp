// Includes
#include "EngineC.h"

#include <stdexcept>
#include <iostream>

#include "graphics/backends/opengl/OpenGLDevice.h"
#include "scene/SceneC.h"
#include "window/WindowC.h"
#include "factory/FactoryC.h"

namespace gltut
{
// Global classes
EngineC::EngineC(u32 windowWidth, u32 windowHeight)
{
	mWindow = std::make_unique<WindowC>(
		windowWidth,
		windowHeight);
	GLTUT_CHECK(mWindow != nullptr, "Failed to create the window");

	auto device = std::make_unique<OpenGLDevice>(*mWindow);
	GLTUT_CHECK(device != nullptr, "Failed to create the device");

	mWindow->addEventHandler(this);

	mRenderPipeline = std::make_unique<RenderPipelineC>(*device);
	mScene = std::make_unique<SceneC>(*mWindow, *mRenderPipeline);
	mRenderer = std::move(device);

	// Create the default render pass
	// It uses:
	// - the 0th material layer
	// - the current active scene camera
	// - the window frame buffer
	const Color clearColor(0.1f, 0.3f, 0.3f);
	RenderPass* defaultPass = mRenderPipeline->createPass(
		mScene->getActiveCameraViewpoint(),
		mScene->getRenderObject(),
		mRenderer->getWindowFramebuffer(),
		0,
		&clearColor,
		true,
		nullptr);
	GLTUT_CHECK(defaultPass != nullptr, "Cannot create the default render pass");

	mFactory = std::make_unique<FactoryC>(*mRenderPipeline, *mScene);
}

bool EngineC::update() noexcept
{
	mScene->update();
	mFactory->update();
	mRenderPipeline->execute();
	return mWindow->update();
}

bool EngineC::onEvent(const Event& event) noexcept
{
	if (event.type == Event::Type::WINDOW_RESIZE)
	{
		mRenderPipeline->execute();
	}
	// Don't stop event propagation
	return false;
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
