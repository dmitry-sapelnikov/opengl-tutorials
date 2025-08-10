#pragma once

// Includes
#include <memory>
#include "engine/core/NonCopyable.h"
#include "engine/Engine.h"
#include "engine/factory/Factory.h"

#include "./graphics/GraphicsDeviceBase.h"
#include "./scene/SceneC.h"
#include "./window/WindowC.h"
#include "./render_pipeline/RenderPipelineC.h"

namespace gltut
{
/// Implementation of the Engine class
class EngineC final : public Engine, public EventHandler, public NonCopyable
{
public:
	/// Constructor
	EngineC(u32 windowWidth, u32 windowHeight);

	/// Runs the engine
	bool update() noexcept final;

	///	Returns the window
	Window* getWindow() noexcept final
	{
		return mWindow.get();
	}

	/// Returns the device
	GraphicsDevice* getDevice() noexcept final
	{
		return mRenderer.get();
	}

	/// Returns the render pipeline
	RenderPipeline* getRenderPipeline() noexcept final
	{
		return mRenderPipeline.get();
	}

	/// Returns the scene
	Scene* getScene() noexcept final
	{
		return mScene.get();
	}

	/// Returns the geometry factory
	Factory* getFactory() noexcept final
	{
		return mFactory.get();
	}

	/// Called when the window is resized
	bool onEvent(const Event& event) noexcept final;

private:
	/// The window
	std::unique_ptr<WindowC> mWindow;

	///	The device
	std::unique_ptr<GraphicsDeviceBase> mRenderer;

	/// The scene
	std::unique_ptr<SceneC> mScene;

	/// The render pipeline
	std::unique_ptr<RenderPipelineC> mRenderPipeline;

	/// The geometry factory
	std::unique_ptr<Factory> mFactory;
};

// End of the namespace gltut
}
