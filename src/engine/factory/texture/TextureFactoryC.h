#pragma once

// Includes
#include <unordered_set>
#include "engine/core/NonCopyable.h"
#include "engine/window/Window.h"
#include "engine/factory/texture/TextureFactory.h"

namespace gltut
{

class TextureFactoryC final : public TextureFactory, public EventHandler, public NonCopyable
{
public:
	/// Constructor
	explicit TextureFactoryC(Window& window) noexcept :
		mWindow(window)
	{
		mWindow.addEventHandler(this);
	}

	/// Destructor
	~TextureFactoryC() noexcept
	{
		mWindow.removeEventHandler(this);
	}

	/// Creates a binding between a texture and the window size
	void createWindowSizeTextureBinding(Texture* texture) noexcept final;

	/// Removes the window-size texture binding for a texture
	void removeWindowSizeTextureBinding(Texture* texture) noexcept final;

	/**
		\brief Called when an event occurs
		\return True if the event was handled, false to continue processing
	*/
	bool onEvent(const Event& event) noexcept final;

private:
	Window& mWindow;

	std::unordered_set<Texture*> mWindowSizeTextures;
};

// End of the namespace gltut
}
