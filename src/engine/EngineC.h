// Includes
#include <memory>
#include "engine/Engine.h"
#include "WindowC.h"
#include "SceneC.h"

namespace gltut
{

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
	bool doStep() noexcept final;

	/// Returns the scene
	virtual Scene* getScene() noexcept final;

private:
	std::unique_ptr<WindowC> mWindow;

	std::unique_ptr<SceneC> mScene;
};

// End of the namespace gltut
}
