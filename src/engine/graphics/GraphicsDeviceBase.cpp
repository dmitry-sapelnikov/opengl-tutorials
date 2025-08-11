// Includes
#include "GraphicsDeviceBase.h"

#include <iostream>
#include "../core/File.h"

namespace gltut
{

// Local functions
namespace
{

template <typename T>
void removeElement(
	std::vector<std::unique_ptr<T>>&container,
	T * element,
	const char* elementName) noexcept
{
	if (element == nullptr)
	{
		return;
	}

	auto findResult = std::find_if(
		container.begin(),
		container.end(),
		[&element](const auto& e)
		{
			return e.get() == element;
		});

	if (findResult != container.end())
	{
		container.erase(findResult);
	}
	else
	{
		std::cerr << "Failed to remove the element: " << elementName << std::endl;
	}
}

}

GraphicsDeviceBase::GraphicsDeviceBase(Window& window) noexcept :
	mWindow(window),
	mGeometries(*this),
	mShaders(*this),
	mTextures(*this)
{
}

TextureFramebuffer* GraphicsDeviceBase::createTextureFramebuffer(
	Texture* color,
	Texture* depth) noexcept
{
	TextureFramebuffer* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = mFramebuffers.emplace_back(createBackendTextureFramebuffer(
			color,
			depth)).get();
	GLTUT_CATCH_ALL_END("Failed to create framebuffer")
	return result;
}

void GraphicsDeviceBase::removeTextureFramebuffer(TextureFramebuffer* frameBuffer) noexcept
{
	removeElement(mFramebuffers, frameBuffer, "Framebuffer");
}

void GraphicsDeviceBase::bindFramebuffer(
	Framebuffer* framebuffer,
	Rectangle2u* viewport) noexcept
{
	if (framebuffer == nullptr)
	{
		return;
	}

	framebuffer->bind();
	if (viewport != nullptr)
	{
		setViewport(*viewport);
	}
	else
	{
		// If no viewport is provided, use the framebuffer size
		setViewport({ { 0, 0 }, framebuffer->getSize() });
	}
}

// End of the namespace gltut
}
