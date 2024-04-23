#ifndef OPENGL_TUTORIALS_ENGINE_C_H
#define OPENGL_TUTORIALS_ENGINE_C_H

// Includes
#include <memory>
#include "engine/core/NonCopyable.h"
#include "engine/Engine.h"
#include "engine/Renderer.h"
#include "WindowC.h"

namespace gltut
{
/// Implementation of the Engine class
class EngineC final : public Engine, public WindowResizeCallback, public NonCopyable
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

	/// Called when the window is resized
	void onResize(u32 width, u32 height) noexcept final;

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
