#ifndef OPENGL_TUTORIALS_ENGINE_C_H
#define OPENGL_TUTORIALS_ENGINE_C_H

// Includes
#include <memory>
#include "engine/Engine.h"

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
	EngineC();

	/// Destructor
	~EngineC() noexcept final;

	/// Creates a window
	Window* createWindow(
		u32 width,
		u32 height,
		const char* title) noexcept final;

	/// Runs the engine
	bool update() noexcept final;

	/// Returns the scene
	virtual Scene* getScene() noexcept final;

private:
	/// The window
	std::unique_ptr<WindowC> mWindow;

	/// The scene
	std::unique_ptr<SceneC> mScene;
};

// End of the namespace gltut
}

#endif
