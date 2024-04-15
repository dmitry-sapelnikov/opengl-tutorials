// Includes
#include <memory>
#include "engine/IEngine.h"
#include "Window.h"
#include "Scene.h"

namespace gltut
{

class Engine final : public IEngine
{
public:
	/// Constructor
	Engine();

	/// Destructor
	~Engine() noexcept final;

	/// Creates a window
	IWindow* createWindow(
		u32 width,
		u32 height,
		const char* title) noexcept final;

	/// Runs the engine
	bool doStep() noexcept final;

	/// Returns the scene
	virtual IScene* getScene() noexcept final;

private:
	std::unique_ptr<Window> mWindow;

	std::unique_ptr<Scene> mScene;
};

// End of the namespace gltut
}
