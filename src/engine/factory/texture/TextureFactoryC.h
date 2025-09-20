// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/factory/texture/TextureFactory.h"
#include "engine/window/Window.h"
#include <unordered_set>

namespace gltut
{
// Global classes
/// Implementation of the TextureFactory interface
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
	void createWindowSizeTextureBinding(Texture2* texture) noexcept final;

	/// Removes the window-size texture binding for a texture
	void removeWindowSizeTextureBinding(Texture2* texture) noexcept final;

	/**
		\brief Called when an event occurs
		\return True if the event was handled, false to continue processing
	*/
	bool onEvent(const Event& event) noexcept final;

private:
	/// Reference to the window
	Window& mWindow;

	/// Set of textures bound to the window size
	std::unordered_set<Texture2*> mWindowSizeTextures;
};

// End of the namespace gltut
}
