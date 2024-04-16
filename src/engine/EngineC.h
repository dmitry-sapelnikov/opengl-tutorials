#ifndef OPENGL_TUTORIALS_ENGINE_C_H
#define OPENGL_TUTORIALS_ENGINE_C_H

// Includes
#include <memory>
#include "engine/Engine.h"
#include "engine/Renderer.h"

namespace gltut
{
// Global classes
class WindowC;
class SceneC;

/// Implementation of the Engine class
class EngineC final : public Engine
{
public:
	/// Constructor
	EngineC(u32 windowWidth, u32 windowHeight);

	/// Destructor
	~EngineC() noexcept final;

	/// Runs the engine
	bool update() noexcept final;

	///	Returns the window
	virtual Window* getWindow() noexcept final;

	/// Returns the renderer
	virtual Renderer* getRenderer() noexcept final;

	/// Returns the scene
	virtual Scene* getScene() noexcept final;

private:
	/// The window
	std::unique_ptr<WindowC> mWindow;

	///	The renderer
	std::unique_ptr<Renderer> mRenderer;

	/// The scene
	std::unique_ptr<Scene> mScene;
};

// End of the namespace gltut
}

#endif
