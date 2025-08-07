#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/renderer/framebuffer/Framebuffer.h"
#include "engine/window/Window.h"

namespace gltut
{

/// Base class for window framebuffers
class WindowFramebufferBase : public Framebuffer, public NonCopyable
{
public:
	/// Constructor
	explicit WindowFramebufferBase(const Window& window) :
		mWindow(window)
	{
		GLTUT_CHECK(mWindow.getDeviceContext() != nullptr, "Device context is null");
	}

	/// Returns the size of the framebuffer
	Point2u getSize() const noexcept final
	{
		return mWindow.getSize();
	}

private:
	const Window& mWindow;
};

// End of the namespace gltut
}
