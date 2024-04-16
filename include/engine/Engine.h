#ifndef OPENGL_TUTORIALS_ENGINE_H
#define OPENGL_TUTORIALS_ENGINE_H

// Includes
#include "Window.h"
#include "Scene.h"
#include "Renderer.h"

namespace gltut
{
//	Global classes
///	The engine
class Engine
{
public:
	/// Virtual destructor
	virtual ~Engine() noexcept = default;

	/**
		\brief Performs a single update of the engine
		\return true if the update was successful, false otherwise
	*/
	virtual bool update() noexcept = 0;

	/// Returns the window
	virtual Window* getWindow() noexcept = 0;

	/// Returns the renderer
	virtual Renderer* getRenderer() noexcept = 0;

	/// Returns the scene
	virtual Scene* getScene() noexcept = 0;
};

//	Global functions
/**
	\brief Creates an engine instance
	\return The engine if it was created successfully, nullptr otherwise
	\note The caller is responsible for deleting the instance
*/
Engine* createEngine(u32 windowWidth, u32 windowHeight) noexcept;

// End of the namespace gltut
}

#endif
