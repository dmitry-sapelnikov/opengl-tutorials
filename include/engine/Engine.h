#ifndef OPENGL_TUTORIALS_ENGINE_H
#define OPENGL_TUTORIALS_ENGINE_H

// Includes
#include "Window.h"
#include "Scene.h"

namespace gltut
{
//	Global classes
class Engine
{
public:
	/// Virtual destructor
	virtual ~Engine() noexcept = default;

	/// Creates a window
	virtual Window* createWindow(
		u32 width,
		u32 height,
		const char* title) noexcept = 0;

	/**
		\brief Performs a single step of the engine
		\return true if the step was successful, false otherwise
	*/
	virtual bool doStep() noexcept = 0;

	/// Returns the scene
	virtual Scene* getScene() noexcept = 0;
};

//	Global functions
/**
	\brief Creates an engine
	\return The engine if it was created successfully, nullptr otherwise
	\note The caller is responsible for deleting the engine
*/
Engine* createEngine() noexcept;

// End of the namespace gltut
}

#endif
