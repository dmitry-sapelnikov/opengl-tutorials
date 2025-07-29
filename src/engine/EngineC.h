#pragma once

// Includes
#include <memory>
#include "engine/core/NonCopyable.h"
#include "engine/Engine.h"
#include "scene/SceneC.h"
#include "engine/window/Window.h"
#include "engine/factory/Factory.h"


namespace gltut
{
/// Implementation of the Engine class
class EngineC final : public Engine, public EventHandler, public NonCopyable
{
public:
	/// Constructor
	EngineC(u32 windowWidth, u32 windowHeight);

	/// Destructor
	~EngineC() noexcept final;

	/// Runs the engine
	bool update() noexcept final;

	///	Returns the window
	Window* getWindow() noexcept final;

	/// Returns the renderer
	Renderer* getRenderer() noexcept final;

	/// Returns the scene
	Scene* getScene() noexcept final;

	/// Returns the geometry factory
	Factory* getFactory() noexcept final;

	/// Called when the window is resized
	void onEvent(const Event& event) noexcept final;

private:
	/// The window
	std::unique_ptr<Window> mWindow;

	///	The renderer
	std::unique_ptr<Renderer> mRenderer;

	/// The scene
	std::unique_ptr<Scene> mScene;

	/// The geometry factory
	std::unique_ptr<Factory> mFactory;
};

// End of the namespace gltut
}
