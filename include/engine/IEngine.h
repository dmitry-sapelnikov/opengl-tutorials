#ifndef OPENGL_TUTORIALS_FRAMEWORK_H
#define OPENGL_TUTORIALS_FRAMEWORK_H

// Includes
#include "IWindow.h"
#include "IScene.h"

namespace gltut
{

class IEngine
{
public:
	/// Virtual destructor
	virtual ~IEngine() noexcept = default;

	/// Creates a window
	virtual IWindow* createWindow(
		u32 width,
		u32 height,
		const char* title) noexcept = 0;

	/**
		\brief Performs a single step of the engine
		\return true if the step was successful, false otherwise
	*/
	virtual bool doStep() noexcept = 0;

	/// Returns the scene
	virtual IScene* getScene() noexcept = 0;
};

//	Global functions
/**
	Creates an engine
	\return The engine if it was created successfully, nullptr otherwise
	\note The caller is responsible for deleting the engine
*/
IEngine* createEngine() noexcept;

// End of the namespace gltut
}

#endif
